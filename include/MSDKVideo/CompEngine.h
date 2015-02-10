#ifndef COMPENGINE_H_
#define COMPENGINE_H_
#include "MSDKDecode.h"
#include "MSDKVpp.h"
#include "MSDKEncode.h"

typedef enum {
    STOP_ATONCE = 0,
    STOP_DELAY
} STOP_MODE;

/**
 * \brief CompEngine class.
 * \details Manages decoder, vpp and encoder objects.
 */
class CompEngine
{
public:
    CompEngine(MSDKCodecNotify* pNotify);
    ~CompEngine();

public:
    bool Init(mfxU8 uCompNum, mfxU16 width, mfxU16 height, mfxU16 bitrate, int nLogicIndex, bool bUseMeasure = true);
    //Modify task interfaces
    bool AttachDecoder(mfxU16 nAddCnt);
    bool DetachDecoder(mfxU16 nReduCnt);
    bool AttachVppEncoder(mfxU16 width, mfxU16 height, mfxU16 bitrate, int nLogicIndex);
    void SetSingleRect(int streamIndex, VppRect* rect) { m_mainVpp.SetVPPCompRect(streamIndex, rect); }

    bool Start();
    void FeedData(unsigned char* pData, int nLen, int streamIndex);
    unsigned long Stop(STOP_MODE mode, bool bShowVppInfo = false);
    void SetDataEos(int streamIndex);
    void ForceKeyFrame(unsigned int nLogicIndex);

private:
    static VADisplay CreateVAEnvDRM();
    static void DestroyVAEnvDRM();

    static VADisplay m_vaDpy;
    static int m_fdDri;
    static int m_nEngineCnt;

    MSDKCodecNotify* m_pNotify;
    bool m_bRunning, m_bUseMeasure;
    MFXVideoSession* m_pMainSession;
    MSDKVpp m_mainVpp;
    MSDKEncode m_mainEncoder;
    std::vector<MemPool*> m_vMemPool;
    std::list<MSDKDecode*> m_listDecoder;
    std::list<MSDKVpp*> m_listVpp;
    std::list<MSDKEncode*> m_listEncoder;
    Measurement m_measuremnt;

private:
    CompEngine(const CompEngine&);
    CompEngine& operator=(const CompEngine&);
};

#endif  //COMPENGINE_H_
