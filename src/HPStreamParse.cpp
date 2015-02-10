#include "HPStreamParse.h"
#include "AUDEC/AUDEC_Header.h"
#include "AUDEC/AUDEC_CodecID.h"
#include "VIDEC/VIDEC_Header.h"

HPStreamParse::HPStreamParse()
:m_pIAVReceiver(NULL)
,m_nWidth(0)
,m_nHeight(0)
{
}

bool HPStreamParse::Connect(const TASK_STREAM& stTaskStream)
{
    m_strStreamID = stTaskStream.strDevID+stTaskStream.strCHLID;
    if (NULL == m_pIAVReceiver)
        m_pIAVReceiver = NETEC_MediaReceiver::Create(*this);
    if (0 != m_pIAVReceiver->Open(stTaskStream.strNodeID.c_str(),
                                  stTaskStream.strNATAddr.c_str(),
                                  stTaskStream.usLocalPort,
                                  stTaskStream.strLocalAddr.c_str(),
                                  stTaskStream.usLocalPort,
                                  stTaskStream.strMCUID.c_str(),
                                  stTaskStream.strMCUAddr.c_str(),
                                  stTaskStream.usMCUPort))
    {
        printf("[HPCOMP]m_pIAVReceiver->Open failed.\n");
        return false;
    }
    m_pIAVReceiver->SetAudioID(stTaskStream.ulAudioID);
    m_pIAVReceiver->SetVideoID(stTaskStream.ulVideoID);
    m_pIAVReceiver->StartAudio();
    m_pIAVReceiver->StartVideo();
    return true;
}

void HPStreamParse::Release()
{
    if (m_pIAVReceiver)
    {
        m_pIAVReceiver->EnableAudio(0);
        m_pIAVReceiver->EnableVideo(0);
        m_pIAVReceiver->StopAudio();
        m_pIAVReceiver->StopVideo();
        m_pIAVReceiver->Close();
        delete m_pIAVReceiver;
        m_pIAVReceiver = NULL;
    }
}

void HPStreamParse::AddTask(TaskProcess* pTask)
{
    {
        KAutoLock l(m_secTask);
        m_setTask.insert(pTask);
    }
    if (m_nWidth && m_nHeight)
        pTask->OnResolutionChanged(m_strStreamID, m_nWidth, m_nHeight);
    m_pIAVReceiver->RequestKeyFrame();
}

int HPStreamParse::RemoveTask(TaskProcess* pTask)
{
    KAutoLock l(m_secTask);
    m_setTask.erase(pTask);
    return m_setTask.size();
}

void HPStreamParse::OnNETEC_MediaReceiverCallbackAudioPacket(unsigned char* pData, int nLen)
{
    if (AUDEC_HEADER_IS_VALID(pData))
    {
        KAutoLock l(m_secTask);
        for (std::set<TaskProcess*>::iterator it = m_setTask.begin(); it != m_setTask.end(); ++it)
            (*it)->InputAudioPacket(m_strStreamID, pData, nLen);
    }
}

void HPStreamParse::OnNETEC_MediaReceiverCallbackVideoPacket(unsigned char* pData, int nLen)
{
    //static int nTotal = 1;
    //printf("[%p]-----Input video packet %d\n", this, nTotal++);

    if (VIDEC_HEADER_EXT_IS_VALID(pData))
    {
        bool bResolutionChange = false;
        if (VIDEC_HEADER_EXT_GET_KEYFRAME(pData))
        {
            int width = VIDEC_HEADER_EXT_GET_VIRTUAL_WIDTH(pData);
            int height = VIDEC_HEADER_EXT_GET_VIRTUAL_HEIGHT(pData);
            if (width != m_nWidth || height != m_nHeight)
            {
                m_nWidth = width;
                m_nHeight = height;
                bResolutionChange = true;
            }
        }
        int nHeaderLen = VIDEC_HEADER_EXT_GET_LEN(pData);    //discard the header of private protocol

        KAutoLock l(m_secTask);
        for (std::set<TaskProcess*>::iterator it = m_setTask.begin(); it != m_setTask.end(); it++)
        {
            if (bResolutionChange)
                (*it)->OnResolutionChanged(m_strStreamID, m_nWidth, m_nHeight);
            (*it)->InputVideoPacket(m_strStreamID, pData+nHeaderLen, nLen-nHeaderLen);
        }
    }
}
