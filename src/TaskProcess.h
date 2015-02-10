#ifndef TASKPROCESS_H_
#define TASKPROCESS_H_

#include "stdafx.h"
#include "AUDEC/AUDEC_Header.h"
#include "AUDEC/AUDEC_CodecID.h"
#include "VIDEC/VIDEC_Header.h"
#include "VIDEC/VIDEC_CodecDef.h"
#include "MSDKVideo/CompEngine.h"
#include "ChanSender.h"
#include "HPCompositeDefine.h"
#include "H264FrameParser.h"
#include "HPATC_Mixer.h"
#include "TMInfo.h"

typedef struct {
    int streamIndex;
    unsigned long ulWndIndex;
} StreamInfo;

class TaskProcessNotify
{
public:
    virtual void OnReceiveStream(const TASK_STREAM& stTaskStream, const std::string& strTaskID) = 0;
    virtual void OnReleaseStream(const std::string& strStreamID, const std::string& strTaskID) = 0;
};

class TaskProcess
:public KThread
,public ChanSenderNotify
,public HPATC_MixerCallback
,public MSDKCodecNotify
{
public:
    TaskProcess(TaskProcessNotify& rNotify);
    ~TaskProcess() {}

public:
    bool StartTask(const COMP_TASKINFO& stTaskInfo, const VEC_STREAM& vTaskStream);
    void ModifyTask(const COMP_TASKINFO& stTaskInfo, const VEC_STREAM& vTaskStream);
    void StopTask();
    void InputAudioPacket(const std::string& strStreamID, unsigned char* pData, int nLen);
    void InputVideoPacket(const std::string& strStreamID, unsigned char* pData, int nLen);
    void OnResolutionChanged(const std::string& strStreamID, unsigned int width, unsigned int height);

private:
    void ThreadProcMain();
    bool SetDestRect(int uTmid);
    void ReceiveStream(const VEC_STREAM& vTaskStream);
    void AdjustPlayerRect(unsigned int width, unsigned int height, unsigned int& wnd_x, unsigned int& wnd_y, unsigned int& wnd_w, unsigned int& wnd_h);
    void OnGetMSDKCodecData(unsigned char* pData, int nLen, bool bKeyFrame, int nIndex);
    void OnHPATC_MixerCallbackPacketData(HPATC_Mixer* pMixer, void* pPacketData, int nPacketLen, unsigned long ulTimestamp);
    void OnRequestRealPlay(int nStatus, unsigned int nLogicIndex);
    void OnRequestKeyFrame(unsigned int nLogicIndex);

private:
    COMP_TASKINFO m_taskInfo;
    std::vector<RECT> m_vPosArray;
    std::map<std::string, StreamInfo> m_mapStream;
    bool m_bWantToStop;
    bool m_bWantToRecvAudio[MAX_OUTPUT_NUM];
    bool m_bWantToRecvVideo[MAX_OUTPUT_NUM];
    unsigned int m_width[MAX_OUTPUT_NUM], m_height[MAX_OUTPUT_NUM];
    ChanSender m_StreamSender[MAX_OUTPUT_NUM];
    HPATC_Mixer* m_pAudioMixer;
    CompEngine* m_pCompEngine;
    char* m_pStubBuf[MAX_OUTPUT_NUM];
    unsigned char* m_pAudioPacket;
    unsigned char* m_pVideoPacket[MAX_OUTPUT_NUM];
    int m_nAudioFrameBufferLength;
    int m_nVideoFrameBufferLength[MAX_OUTPUT_NUM];
    unsigned short m_usAudioSequence;
    unsigned short m_usVideoSequence[MAX_OUTPUT_NUM];
    TaskProcessNotify& m_rNotify;

    FILE* m_pFile;
};

#endif  //TASKPROCESS_H_
