#ifndef CHANSENDER_H_
#define CHANSENDER_H_

#include "stdafx.h"
#include "NETEC/NETEC_MediaSender.h"
#include "NETEC/XSocket.h"
#include "NETEC/XUtil.h"
#include "VIDEC/VIDEC_Header.h"
#include "MSDKVideo/CompEngine.h"

class ChanSenderNotify
{
public:
    virtual void OnRequestRealPlay(int nStatus, unsigned int nLogicIndex) = 0;
    virtual void OnRequestKeyFrame(unsigned int nLogicIndex) = 0;
};

class ChanSender
:public NETEC_MediaSenderCallback
{
public:
    ChanSender();
    virtual ~ChanSender() {}

public:
    bool IsValid() { return (m_pIAVSender != NULL?true:false); }
    bool StartSend(unsigned int nLogicIndex, unsigned long ulAudioID, unsigned long ulVideoID, ChanSenderNotify* pSendNotify);
    void StopSend();
    void OnCheckConnection();
    int SendAudioPacket(unsigned char* pData, int nLen);
    int SendVideoPacket(unsigned char* pData, int nLen);

private:
    NETEC_MediaSender* m_pIAVSender;
    ChanSenderNotify* m_pNotify;
    unsigned long m_ulAudioID;
    unsigned long m_ulVideoID;
    unsigned int m_nLogicIndex;
    int m_nReqStream;
};

#endif  //CHANSENDER_H_
