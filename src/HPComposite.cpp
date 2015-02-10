#include "HPComposite.h"

bool HPComposite::StartTask(const COMP_TASKINFO& stTaskInfo, const VEC_STREAM& vTaskStream)
{
    MAP_TASKPROC::iterator it = m_mapTask.find(stTaskInfo.strTaskID);
    if (it != m_mapTask.end())
        return false;

    TaskProcess* pProcess = new TaskProcess(*this);
    if (pProcess)
    {
        //Note: The value of `m_mapTask[stTaskInfo.strTaskID]` will be used when receiving real
        //stream in the routine of `pProcess->StartTask`
        m_mapTask[stTaskInfo.strTaskID] = pProcess;
        if (!pProcess->StartTask(stTaskInfo, vTaskStream))
        {
            pProcess->StopTask();
            delete pProcess;
            m_mapTask.erase(stTaskInfo.strTaskID);
            return false;
        }
    }

    KCmdPacket out("DEVAGENT", MON_PORTINFO, g_config.local_serverid);
    out.SetAttribUN("USERPORT", m_mapTask.size());
    SendToDevAgent(out, DEV_AGENT_ID);
    return true;
}

bool HPComposite::ModifyTask(const COMP_TASKINFO& stTaskInfo, const VEC_STREAM& vTaskStream)
{
    MAP_TASKPROC::iterator it = m_mapTask.find(stTaskInfo.strTaskID);
    if (it != m_mapTask.end())
    {
        it->second->ModifyTask(stTaskInfo, vTaskStream);
        return true;
    }
    return false;
}

void HPComposite::StopTask(const std::string& strTaskID)
{
    TaskProcess* pProcess = NULL;
    MAP_TASKPROC::iterator it = m_mapTask.find(strTaskID);
    if (it != m_mapTask.end())
        pProcess = it->second;

    if (pProcess)
    {
        pProcess->StopTask();
        delete pProcess;
        m_mapTask.erase(it);
    }

    KCmdPacket out("DEVAGENT", MON_PORTINFO, g_config.local_serverid);
    out.SetAttribUN("USERPORT", m_mapTask.size());
    SendToDevAgent(out, DEV_AGENT_ID);
}

void HPComposite::StopAllTask()
{
    while (m_mapTask.size() > 0)
        StopTask(m_mapTask.begin()->first);

    while (m_mapStream.size() > 0)
    {
        MAP_STREAMPARSER::iterator it = m_mapStream.begin();
        HPStreamParse* pHPStreamParse = it->second;
        m_mapStream.erase(it);
        pHPStreamParse->Release();
        delete pHPStreamParse;
        pHPStreamParse = NULL;
    }
}

HPStreamParse* HPComposite::FindStreamParse(const std::string& strStreamID)
{
    HPStreamParse* pStream = NULL;
    MAP_STREAMPARSER::iterator it = m_mapStream.find(strStreamID);
    if (it != m_mapStream.end())
        pStream = it->second;
    return pStream;
}

HPStreamParse* HPComposite::CreateStream(const TASK_STREAM& stTaskStream)
{
    HPStreamParse* pStream = new HPStreamParse();
    if (!pStream->Connect(stTaskStream))
    {
        pStream->Release();
        delete pStream;
        pStream = NULL;
    }

    if (pStream)
    {
        std::string strStreamID = stTaskStream.strDevID+stTaskStream.strCHLID;
        m_mapStream[strStreamID] = pStream;
    }
    return pStream;
}

void HPComposite::OnReceiveStream(const TASK_STREAM& stTaskStream, const std::string& strTaskID)
{
    std::string strStreamID = stTaskStream.strDevID+stTaskStream.strCHLID;
    HPStreamParse* pStream = FindStreamParse(strStreamID);
    if (!pStream)
        pStream = CreateStream(stTaskStream);
    else
        LOG::INF("[HPCOMP]Stream has received... StreamID = %s.\n", strStreamID.c_str());

    if (pStream)
        pStream->AddTask(m_mapTask[strTaskID]);
}

void HPComposite::OnReleaseStream(const std::string& strStreamID, const std::string& strTaskID)
{
    HPStreamParse* pStream = FindStreamParse(strStreamID);
    if (pStream)
    {
        int nCnt = pStream->RemoveTask(m_mapTask[strTaskID]);
        if (0 == nCnt)
        {
            LOG::DBG("[HPCOMP]On destroying stream... StreamID = %s\n", strStreamID.c_str());
            m_mapStream.erase(strStreamID);
            pStream->Release();
            delete pStream;
        }
    }
}

bool HPComposite::OnCHLChanged(const TASK_STREAM& stTaskStream)
{
    std::string strStreamID = stTaskStream.strDevID+stTaskStream.strCHLID;
    LOG::INF("[HPCOMP]OnCHLChanged: strStreamID = %s\n", strStreamID.c_str());
    HPStreamParse* pStream = FindStreamParse(strStreamID);
    if (NULL == pStream)
    {
        LOG::ERR("[HPCOMP]In process of changing the channel that does not exist.\n");
        return false;
    }

    if (!pStream->Connect(stTaskStream))
    {
        LOG::ERR("[HPCOMP]Cannot connect to devices that is used to receive real stream\n");
        return false;
    }
    return true;
}
