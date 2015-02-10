#ifndef MSDKDECODE_H_
#define MSDKDECODE_H_
#include "MSDKDecodeVpp.h"

//#define CONFIG_WRITE_RAW_BUFFER

class MSDKDecode : public MSDKDecodeVpp
{
public:
#ifdef CONFIG_WRITE_RAW_BUFFER
    MSDKDecode(MSDKCodecNotify& rNotify)
#else
    MSDKDecode();
#endif
	virtual ~MSDKDecode();

public:
    bool SetDecodeParam(VADisplay* pVaDpy, MemPool* pMem, Measurement* pMeasuremnt, bool bUseMeasure);
    void RequestLastSurface();

private:
#ifndef CONFIG_USE_MFXALLOCATOR
    mfxStatus AllocFrames(mfxFrameAllocRequest* pRequest);
#endif
    mfxStatus InitDecoder();
    void UpdateBitStream();
    void UpdateMemPool() { m_pInputMem->UpdateReadPtr(m_inputBs.DataOffset); }
    void WriteOutSurface(mfxFrameSurface1* pmfxOutSurface);
    virtual int HandleProcess();
#ifdef CONFIG_WRITE_RAW_BUFFER
    mfxU32 WriteRawFrameToBuffer(mfxFrameSurface1* pSurface);
#endif

private:
	MFXVideoDECODE* m_pDecode;
	MemPool* m_pInputMem;
	mfxBitstream m_inputBs;
	mfxFrameSurface1* m_pLastSurface;
#ifdef CONFIG_WRITE_RAW_BUFFER
	mfxU8* m_pRawBuffer;
	MSDKCodecNotify& m_rNotify
#endif
};
#endif	//MSDKDECODE_H_
