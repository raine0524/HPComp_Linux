#include "TaskProcess.h"

TaskProcess::TaskProcess(TaskProcessNotify& rNotify)
:m_bWantToStop(false)
,m_pAudioMixer(NULL)
,m_pCompEngine(NULL)
,m_pAudioPacket(NULL)
,m_nAudioFrameBufferLength(0)
,m_rNotify(rNotify)
{
    memset(m_bWantToRecvAudio, 0, MAX_OUTPUT_NUM*sizeof(bool));
    memset(m_bWantToRecvVideo, 0, MAX_OUTPUT_NUM*sizeof(bool));
    memset(m_width, 0, MAX_OUTPUT_NUM*sizeof(unsigned int));
    memset(m_height, 0, MAX_OUTPUT_NUM*sizeof(unsigned int));
    memset(m_pStubBuf, 0, MAX_OUTPUT_NUM*sizeof(char*));
    memset(m_pVideoPacket, 0, MAX_OUTPUT_NUM*sizeof(unsigned char*));
    memset(m_nVideoFrameBufferLength, 0, MAX_OUTPUT_NUM*sizeof(int));

    m_pFile = fopen("test.h264", "wb");
}

bool TaskProcess::StartTask(const COMP_TASKINFO& stTaskInfo, const VEC_STREAM& vTaskStream)
{
    bool bRet = true;
    m_taskInfo = stTaskInfo;
    unsigned long ulMixBaseID = GenerateSSRC();

    m_pAudioMixer = HPATC_Mixer::Create(this);
    m_pAudioMixer->Open(vTaskStream.size());
    m_pCompEngine = new CompEngine(this);

    int nCount = 0, bitrate[MAX_OUTPUT_NUM], ulAudioID[MAX_OUTPUT_NUM], ulVideoID[MAX_OUTPUT_NUM];
    //Use high resolution & bitrate
    if (stTaskInfo.bUseHigh)
    {
        m_width[nCount]     = stTaskInfo.uHighWidth;
        m_height[nCount]    = stTaskInfo.uHighHeight;
        bitrate[nCount]     = stTaskInfo.uHighBitrate;
        ulAudioID[nCount]   = ulMixBaseID+0;
        ulVideoID[nCount]   = ulMixBaseID+1;
        nCount++;
    }
    //Use middle resolution & bitrate
    if (stTaskInfo.bUseMid)
    {
        m_width[nCount]     = stTaskInfo.uMidWidth;
        m_height[nCount]    = stTaskInfo.uMidHeight;
        bitrate[nCount]     = stTaskInfo.uMidBitrate;
        ulAudioID[nCount]   = ulMixBaseID+2;
        ulVideoID[nCount]   = ulMixBaseID+3;
        nCount++;
    }
    //Use low resolution & bitrate
    if (stTaskInfo.bUseLow)
    {
        m_width[nCount]     = stTaskInfo.uLowWidth;
        m_height[nCount]    = stTaskInfo.uLowHeight;
        bitrate[nCount]     = stTaskInfo.uLowBitrate;
        ulAudioID[nCount]   = ulMixBaseID+4;
        ulVideoID[nCount]   = ulMixBaseID+5;
        nCount++;
    }

    bRet &= m_pCompEngine->Init(vTaskStream.size(), m_width[0], m_height[0], bitrate[0], 0, true);
    m_StreamSender[0].StartSend(0, ulAudioID[0], ulVideoID[0], this);
    m_pStubBuf[0] = new char[1920*1080*2];
    for (int i = 1; i < nCount; i++)
    {
        m_pStubBuf[i] = new char[1920*1080*2];
        bRet &= m_pCompEngine->AttachVppEncoder(m_width[i], m_height[i], bitrate[i], i);
        m_StreamSender[i].StartSend(i, ulAudioID[i], ulVideoID[i], this);
    }

    bRet &= SetDestRect(stTaskInfo.uTMID);
    if (!bRet)
    {
        printf("[%s]CompEngine %p init failed, stop task\n", __FUNCTION__, m_pCompEngine);
        return false;
    }
    ReceiveStream(vTaskStream);
    m_pCompEngine->Start();
    StartThread();

    KCmdPacket out("VIDEOCOMP", REC_COMINFO, g_config.local_serverid);
    out.SetAttrib("MCUID", NETEC_Node::GetMCUID());
    out.SetAttrib("MCUADDR", NETEC_Node::GetMCUIP());
    out.SetAttribUS("MCUPORT", NETEC_Node::GetServerPort());
    out.SetAttrib("NATADDR", NETEC_Node::GetNATIP());
    out.SetAttrib("LOCALADDR", NETEC_Node::GetLocalIP());
    out.SetAttribUS("LOCALPORT", NETEC_Node::GetLocalPort());
    out.SetAttrib("NODEID", NETEC_Node::GetNodeID());
    out.SetAttrib("TASKID", m_taskInfo.strTaskID);
    out.SetAttrib("TASKNAME", m_taskInfo.strTaskName);
    if (stTaskInfo.bUseLow) {
        out.SetAttribUS("BLOWSTREAM", 1);
        out.SetAttribUL("AUDIOCID_L", ulAudioID[--nCount]);
        out.SetAttribUL("VIDEOCID_L", ulVideoID[nCount]);
    } else {
        out.SetAttribUS("BLOWSTREAM", 0);
    }
    if (stTaskInfo.bUseMid) {
        out.SetAttribUS("BMIDSTREAM", 1);
        out.SetAttribUL("AUDIOCID_M", ulAudioID[--nCount]);
        out.SetAttribUL("VIDEOCID_M", ulVideoID[nCount]);
    } else {
        out.SetAttribUS("BMIDSTREAM", 0);
    }
    if (stTaskInfo.bUseHigh) {
        out.SetAttribUS("BHIGHSTREAM", 1);
        out.SetAttribUL("AUDIOCID_H", ulAudioID[--nCount]);
        out.SetAttribUL("VIDEOCID_H", ulVideoID[nCount]);
    } else {
        out.SetAttribUS("BHIGHSTREAM", 0);
    }
    SendToDevAgent(out, REC_AGENT_ID);
    return true;
}

void TaskProcess::ModifyTask(const COMP_TASKINFO& stTaskInfo, const VEC_STREAM& vTaskStream)
{
    if (stTaskInfo.uTMID != m_taskInfo.uTMID)
    {
        m_taskInfo.uTMID = stTaskInfo.uTMID;
        SetDestRect(stTaskInfo.uTMID);
    }
    size_t nStreamCnt = m_mapStream.size();
    for (std::map<std::string, StreamInfo>::const_iterator it = m_mapStream.begin();
         it != m_mapStream.end(); it++)
        m_rNotify.OnReleaseStream(it->first, m_taskInfo.strTaskID);
    m_mapStream.clear();

    if (vTaskStream.size() > nStreamCnt)
        m_pCompEngine->AttachDecoder(vTaskStream.size()-nStreamCnt);
    if (vTaskStream.size() < nStreamCnt)
        m_pCompEngine->DetachDecoder(nStreamCnt-vTaskStream.size());
    ReceiveStream(vTaskStream);
}

void TaskProcess::StopTask()
{
    m_bWantToStop = true;
    WaitForStop();
    for (std::map<std::string, StreamInfo>::const_iterator it = m_mapStream.begin();
         it != m_mapStream.end(); it++)
        m_rNotify.OnReleaseStream(it->first, m_taskInfo.strTaskID);

    if (m_pAudioMixer)
    {
        m_pAudioMixer->Close();
        delete m_pAudioMixer;
        m_pAudioMixer = NULL;
    }

    if (m_pCompEngine)
    {
        m_pCompEngine->Stop(STOP_ATONCE, false);
        delete m_pCompEngine;
        m_pCompEngine = NULL;
    }

    for (int i = 0; i < MAX_OUTPUT_NUM; i++)
    {
        if (m_StreamSender[i].IsValid())
            m_StreamSender[i].StopSend();
    }

    if (m_pAudioPacket)
    {
        free(m_pAudioPacket);
        m_pAudioPacket = NULL;
        m_nAudioFrameBufferLength = 0;
    }
    for (int i = 0; i < MAX_OUTPUT_NUM; i++)
    {
        if (m_pStubBuf[i])
        {
            delete[] m_pStubBuf[i];
            m_pStubBuf[i] = NULL;
        }
        if (m_pVideoPacket[i])
        {
            free(m_pVideoPacket[i]);
            m_pVideoPacket[i] = NULL;
            m_nVideoFrameBufferLength[i] = 0;
        }
    }

    fclose(m_pFile);
}

void TaskProcess::ReceiveStream(const VEC_STREAM& vTaskStream)
{
    StreamInfo info;
    for (int i = 0; i < vTaskStream.size(); i++)
    {
        info.streamIndex = i;
        info.ulWndIndex = vTaskStream[i].ulWndIndex;
        std::string strStreamID = vTaskStream[i].strDevID+vTaskStream[i].strCHLID;
        m_mapStream[strStreamID] = info;
        m_pCompEngine->SetMemPoolName(i, strStreamID.c_str());
        LOG::INF("[HPCOMP]On StartTask: strStreamID = %s\tstreamIndex = %d\twindowIndex = %d\n",
                 strStreamID.c_str(), m_mapStream[strStreamID].streamIndex, m_mapStream[strStreamID].ulWndIndex);
        m_rNotify.OnReceiveStream(vTaskStream[i], m_taskInfo.strTaskID);
    }
}

void TaskProcess::OnRequestRealPlay(int nStatus, unsigned int nLogicIndex)
{
    if (nStatus&REQ_STREAM_AUDIO)
        m_bWantToRecvAudio[nLogicIndex] = true;

    if (nStatus&REQ_STREAM_VIDEO)
        m_bWantToRecvVideo[nLogicIndex] = true;
}

void TaskProcess::OnRequestKeyFrame(unsigned int nLogicIndex)
{
    if (m_pCompEngine)
        m_pCompEngine->ForceKeyFrame(nLogicIndex);
}

void TaskProcess::ThreadProcMain()
{
    while (!m_bWantToStop)
    {
        for (int i = 0; i < MAX_OUTPUT_NUM; i++)
            if (m_StreamSender[i].IsValid())
                m_StreamSender[i].OnCheckConnection();
        Pause(10);
    }
}

//InputAudioPacket/InputVideoPacket/OnResolutionChanged these three functions are in the same thread,
//So once lock one of them, the whole thread is locked, as what happened in the callback of HPStreamParse class
//Here also choose to lock the InputVideoPacket function
void TaskProcess::InputAudioPacket(const std::string& strStreamID, unsigned char* pData, int nLen)
{
    if (m_pAudioMixer)
        m_pAudioMixer->InputPacket(pData, nLen, m_mapStream[strStreamID].streamIndex);
}

void TaskProcess::InputVideoPacket(const std::string& strStreamID, unsigned char* pData, int nLen)
{
    if (m_pCompEngine)
        m_pCompEngine->FeedData(pData, nLen, m_mapStream[strStreamID].streamIndex);
}

void TaskProcess::OnResolutionChanged(const std::string& strStreamID, unsigned int width, unsigned int height)
{
	RECT rect = m_vPosArray[m_mapStream[strStreamID].ulWndIndex];
    VppRect vppRect;
    vppRect.x = rect.left;
    vppRect.y = rect.top;
    vppRect.w = rect.right-rect.left;
    vppRect.h = rect.bottom-rect.top;
    if (!g_config.local_fill)
        AdjustPlayerRect(width, height, vppRect.x, vppRect.y, vppRect.w, vppRect.h);
    m_pCompEngine->SetSingleRect(m_mapStream[strStreamID].streamIndex, &vppRect);
}

bool TaskProcess::SetDestRect(int uTmid)
{
	HPTM_TM_SUBTYPE type;
	switch(uTmid)
	{
	case 1: type = TM_SUBTYPE_2_PIC_IN_PIC;	break;
	case 2: type = TM_SUBTYPE_3_L1_R2;		break;
	case 3: type = TM_SUBTYPE_4_2X2;		break;
	case 4: type = TM_SUBTYPE_4_L1_R3;		break;
	default:
		{
			printf("uTmid is undefined, get type failed.\n");
			return false;
		}
	}
	if (!m_width[0] || !m_height[0])
	{
	    printf("The resolution is not valid\n");
	    return false;
	}
	if (!(TMInfo::GetTMWndPos(m_width[0], m_height[0], TM_TYPE_16X9, type, m_vPosArray)))
	{
		printf("TMInfo::GetTMWndPos to set dest position failed.\n");
		return false;
	}
	return true;
}

void TaskProcess::AdjustPlayerRect(unsigned int width, unsigned int height, unsigned int& wnd_x, unsigned int& wnd_y, unsigned int& wnd_w, unsigned int& wnd_h)
{
    if (!width || !height || !wnd_w || !wnd_h)
        return;

    if (1.0f*width/height > 1.0f*wnd_w/wnd_h)
    {
        //reduce height
        int realHeight = static_cast<int>(1.0f*wnd_w*height/width);
        int diff = (wnd_h-realHeight)/2;
        wnd_y += diff;
        wnd_h = realHeight;
    }
    else
    {
        //reduce width
        int realWidth = static_cast<int>(1.0f*wnd_h*width/height);
        int diff = (wnd_w-realWidth)/2;
        wnd_x += diff;
        wnd_w = realWidth;
    }
    LOG::INF("[HPCOMP]Adjust player rect as %f while the real ratio is %f\n", 1.0f*wnd_w/wnd_h, 1.0f*width/height);
}

void TaskProcess::OnHPATC_MixerCallbackPacketData(HPATC_Mixer* pMixer, void* pPacketData, int nPacketLen, unsigned long ulTimestamp)
{
    bool bWantToRecvAudio = false;
    for (int i = 0; i < MAX_OUTPUT_NUM; i++)
    {
        if (m_bWantToRecvAudio[i])
        {
            bWantToRecvAudio = true;
            break;
        }
    }
    if (!bWantToRecvAudio)
        return;

    if (m_nAudioFrameBufferLength < nPacketLen+1024)
    {
        m_nAudioFrameBufferLength = nPacketLen+2048;
        if (m_pAudioPacket)
        {
            free(m_pAudioPacket);
            m_pAudioPacket = NULL;
        }
        m_pAudioPacket = (unsigned char*)malloc(m_nAudioFrameBufferLength);
        if (NULL == m_pAudioPacket)
        {
            m_nAudioFrameBufferLength = 0;
            return;
        }
    }

    if (m_pAudioPacket)
    {
        AUDEC_HEADER_RESET(m_pAudioPacket);
        AUDEC_HEADER_SET_SEQUENCE(m_pAudioPacket, m_usAudioSequence++);
        AUDEC_HEADER_SET_TIMESTAMP(m_pAudioPacket, GetTimestamp());
        AUDEC_HEADER_SET_CODEC_ID(m_pAudioPacket, X_AUDIO_CODEC_AAC);
        int nHeaderLen = AUDEC_HEADER_GET_LEN(m_pAudioPacket);
        memcpy(m_pAudioPacket+nHeaderLen, pPacketData, nPacketLen);
        for (int i = 0; i < MAX_OUTPUT_NUM; i++)
            if (m_bWantToRecvAudio[i] && m_StreamSender[i].IsValid())
                m_StreamSender[i].SendAudioPacket(m_pAudioPacket, nHeaderLen+nPacketLen);
    }
}

void TaskProcess::OnGetMSDKCodecData(unsigned char* pData, int nLen, bool bKeyFrame, int nIndex)
{
    //printf("[%s]-----Get msdk codec data %d %d\n", __FUNCTION__, nLen, nIndex);
    //if (nIndex == 0)
    fwrite(pData, 1, nLen, m_pFile);

    if (!m_bWantToRecvVideo[nIndex])
        return;

    int outLen = 1920*1080*2, spsSize = 0, ppsSize = 0;
    bool isKeyframe = false;
    int width = 0, height = 0;

    ParseH264Frame((const char*)pData, nLen, m_pStubBuf[nIndex], outLen, NULL,
                   spsSize, NULL, ppsSize, isKeyframe, width, height);

    if (m_nVideoFrameBufferLength[nIndex] < nLen+1024)
    {
        m_nVideoFrameBufferLength[nIndex] = nLen+2048;
        if (m_pVideoPacket[nIndex])
        {
            free(m_pVideoPacket[nIndex]);
            m_pVideoPacket[nIndex] = NULL;
        }
        m_pVideoPacket[nIndex] = (unsigned char*)malloc(m_nVideoFrameBufferLength[nIndex]);
        if (NULL == m_pVideoPacket[nIndex])
        {
            m_nVideoFrameBufferLength[nIndex] = 0;
            return;
        }
    }

    if (m_pVideoPacket[nIndex])
    {
        VIDEC_HEADER_EXT_RESET(m_pVideoPacket[nIndex]);
        VIDEC_HEADER_EXT_SET_CODEC_ID(m_pVideoPacket[nIndex], VIDEC_CODEC_H264);
        VIDEC_HEADER_EXT_SET_DOUBLE_FIELD(m_pVideoPacket[nIndex], 0);
        VIDEC_HEADER_EXT_SET_KEYFRAME(m_pVideoPacket[nIndex], (isKeyframe?1:0));
        VIDEC_HEADER_EXT_SET_SEQUENCE(m_pVideoPacket[nIndex], m_usVideoSequence[nIndex]++);
        VIDEC_HEADER_EXT_SET_TIMESTAMP(m_pVideoPacket[nIndex], GetTimestamp());
        if (isKeyframe)
        {
            VIDEC_HEADER_EXT_SET_ACTUAL_WIDTH(m_pVideoPacket[nIndex], m_width[nIndex]);
            VIDEC_HEADER_EXT_SET_ACTUAL_HEIGHT(m_pVideoPacket[nIndex], m_height[nIndex]);
            VIDEC_HEADER_EXT_SET_VIRTUAL_WIDTH(m_pVideoPacket[nIndex], m_width[nIndex]);
            VIDEC_HEADER_EXT_SET_VIRTUAL_HEIGHT(m_pVideoPacket[nIndex], m_height[nIndex]);
        }
        int nHeaderLen = VIDEC_HEADER_EXT_GET_LEN(m_pVideoPacket[nIndex]);
        memcpy(m_pVideoPacket[nIndex]+nHeaderLen, pData, nLen);
        if (m_StreamSender[nIndex].IsValid())
            m_StreamSender[nIndex].SendVideoPacket(m_pVideoPacket[nIndex], nHeaderLen+nLen);
    }
}
