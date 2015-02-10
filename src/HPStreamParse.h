#ifndef HPSTREAMPARSE_H_
#define HPSTREAMPARSE_H_

#include "stdafx.h"
#include "NETEC/NETEC_MediaReceiver.h"
#include "NETEC/XCritSec.h"
#include "NETEC/XAutoLock.h"
#include "HPCompositeDefine.h"
#include "TaskProcess.h"

class HPStreamParse
:public NETEC_MediaReceiverCallback
{
public:
    HPStreamParse();
    virtual ~HPStreamParse() {}

public:
    bool Connect(const TASK_STREAM& stTaskStream);
    void Release();
    void AddTask(TaskProcess* pTask);
    int RemoveTask(TaskProcess* pTask);

public:
    virtual void OnNETEC_MediaReceiverCallbackAudioPacket(unsigned char* pData, int nLen);
    virtual void OnNETEC_MediaReceiverCallbackVideoPacket(unsigned char* pData, int nLen);

private:
    NETEC_MediaReceiver* m_pIAVReceiver;
    std::string m_strStreamID;
    unsigned int m_nWidth, m_nHeight;
    std::set<TaskProcess*> m_setTask;
    KCritSec m_secTask;
};

#endif  //HPSTREAMPARSE_H_
