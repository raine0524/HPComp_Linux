#ifndef MSDKVPP_H_
#define MSDKVPP_H_
#include <map>
#include <list>
#include <vector>
#include "MSDKDecode.h"

#define MAX_INPUTSTREAM_NUM 4
#define MAX_OUTPUT_NUM		3
#define MAGIC_NUMBER        40*1000 //40ms

typedef struct {
    unsigned x;
    unsigned y;
    unsigned w;
    unsigned h;
} VppRect;

typedef struct {
    mfxU8 comp_num;
    mfxU16 out_width;
    mfxU16 out_height;
} VppConfig;

typedef struct {
    RING_BUFFER* pRingBuf;
    unsigned int nDropFrameNums;
} MediaBuf;

typedef enum {
    VPP_COMP = 0,
    VPP_RESIZE
} VPP_MODE;

class MSDKVpp : public MSDKDecodeVpp
{
public:
    MSDKVpp(VPP_MODE mode);
    virtual ~MSDKVpp();

public:
    bool SetVppParam(VADisplay* pVaDpy, VppConfig* pVppCfg, Measurement* pMeasuremnt, bool bUseMeasure);
    void LinkPrevElement(MSDKDecodeVpp* pCodec);
    void UnlinkPrevElement(MSDKDecodeVpp* pCodec) { m_mapMediaBuf.erase(pCodec); }
    void SetVPPCompRect(int streamIndex, const VppRect* rect);
    void SetVPPCompNum(mfxU8 num) { m_vppCfg.comp_num = num; }

    void AddNextElement(MSDKBase* pCodec) { m_listNextElem.push_front(pCodec); }
    void ReleaseSurface();

private:
    void SetVppCompParam(mfxExtVPPComposite* pVppComp);
#ifndef CONFIG_USE_MFXALLOCATOR
    mfxStatus AllocFrames(mfxFrameAllocRequest* pRequest);
#endif
    mfxStatus InitVpp(mfxFrameSurface1* pFrameSurface);
    mfxStatus DoingVpp(mfxFrameSurface1* pInSurf, mfxFrameSurface1* pOutSurf);
    int PrepareVppCompFrames();
    virtual int HandleProcess();

private:
    VPP_MODE m_mode;
    MFXVideoVPP* m_pVpp;
    mfxExtBuffer* m_pExtBuf[1];
    unsigned int m_tCompStc, m_frameRate;
    bool m_bReinit;
    VppConfig m_vppCfg;
    std::vector<VppRect> m_vRect;
    std::map<MSDKDecodeVpp*, MediaBuf> m_mapMediaBuf;
    std::list<MSDKBase*> m_listNextElem;
    Mutex m_xMsdkInit, m_xMsdkReinit;
};
#endif  //MSDKVPP_H_
