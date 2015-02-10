#include "ChanSender.h"

ChanSender::ChanSender()
:m_pIAVSender(NULL)
,m_pNotify(NULL)
,m_ulAudioID(0)
,m_ulVideoID(0)
,m_nReqStream(REQ_STREAM_NONE)
{
}

bool ChanSender::StartSend(unsigned int nLogicIndex, unsigned long ulAudioID, unsigned long ulVideoID, ChanSenderNotify* pSenderNotify)
{
    if (nLogicIndex >= MAX_OUTPUT_NUM || !ulAudioID || !ulVideoID || !pSenderNotify)
        return false;
    m_nLogicIndex = nLogicIndex;
    m_ulAudioID = ulAudioID;
    m_ulVideoID = ulVideoID;
    m_pNotify = pSenderNotify;

    if (!m_pIAVSender)
        m_pIAVSender = NETEC_MediaSender::Create(*this);
    m_pIAVSender->Open();
    m_pIAVSender->StartAudio(m_ulAudioID);
    m_pIAVSender->StartVideo(m_ulVideoID);
    return true;
}

void ChanSender::StopSend()
{
    if (m_pIAVSender)
    {
        m_pIAVSender->StopAudio();
        m_pIAVSender->StopVideo();
        m_pIAVSender->Close();
        delete m_pIAVSender;
        m_pIAVSender = NULL;
    }
}

void ChanSender::OnCheckConnection()
{
    if (!m_pIAVSender->IsAudioStarted())
        m_pIAVSender->StartAudio(m_ulAudioID);
    if (!m_pIAVSender->IsVideoStarted())
        m_pIAVSender->StartVideo(m_ulVideoID);

    //Detect whether remote agent request the real composite stream or not
    int nReqStream = REQ_STREAM_NONE;
    if (m_pIAVSender->IsAudioEnable() > 0)  nReqStream |= REQ_STREAM_AUDIO;
    if (m_pIAVSender->IsVideoEnable() > 0)  nReqStream |= REQ_STREAM_VIDEO;
    if (m_nReqStream != nReqStream)
    {
        m_nReqStream = nReqStream;
        LOG::INF("ChanSender::OnCheckConnection m_nReqStream = %d.\n", m_nReqStream);
        m_pNotify->OnRequestRealPlay(m_nReqStream, m_nLogicIndex);
    }

    //Request key frame
    if (m_pIAVSender->IsVideoRequestKeyFrame(0) > 0 ||
        m_pIAVSender->IsVideoRequestKeyFrame(1) > 0 ||
        m_pIAVSender->IsVideoRequestKeyFrame(2) > 0)
    {
        LOG::INF("ChanSenderNotify::OnRequestKeyFrame.\n");
        m_pNotify->OnRequestKeyFrame(m_nLogicIndex);
    }
}

int ChanSender::SendAudioPacket(unsigned char* pData, int nLen)
{
    return 1;

    unsigned long ulTotalPackets, ulLostPackets;
    double dAvgPacketLossRate, dCurPacketLossRate = 100.0;

    if (m_pIAVSender && (m_nReqStream&REQ_STREAM_AUDIO))
    {
        m_pIAVSender->SendAudio(pData, nLen);
        m_pIAVSender->GetAudioPacketStatistics(ulTotalPackets, ulLostPackets, dAvgPacketLossRate, dCurPacketLossRate);
    }
    return (int)dCurPacketLossRate;
}

int ChanSender::SendVideoPacket(unsigned char* pData, int nLen)
{
    unsigned long ulTotalPackets, ulLostPackets;
    double dAvgPacketLossRate, dCurPacketLossRate = 100.0;

    if (m_pIAVSender)
    {
        if (m_nReqStream&(REQ_STREAM_VSUB1|REQ_STREAM_VSUB2|REQ_STREAM_VIDEO))
        {
            VIDEC_HEADER_EXT_SET_MAIN_FRAME(pData, 1);
            VIDEC_HEADER_EXT_SET_SUB_FRAME(pData, 1);
            VIDEC_HEADER_EXT_SET_QSUB_FRAME(pData, 1);
            m_pIAVSender->SendVideo(pData, nLen);
            m_pIAVSender->GetVideoPacketStatistics(ulTotalPackets, ulLostPackets, dAvgPacketLossRate, dCurPacketLossRate);
        }
    }
    return (int)dCurPacketLossRate;
}
