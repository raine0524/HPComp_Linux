//VIDEC_DVC.h
#ifndef __VIDEC_DVC_H__
#define __VIDEC_DVC_H__

#include "VIDEC.h"


class VIDEC_DVCCallback
{
public:
	VIDEC_DVCCallback(void){};
	virtual~VIDEC_DVCCallback(void){};
public:
	virtual void OnVIDEC_DVCCallbackImage(VIDEC_Image*pImage)=0;
	virtual void OnVIDEC_DVCCallbackVideoStreamData(unsigned char*pData,int nLen,int nKeyFrame,int nWidth,int nHeight)=0;
};

class VIDEC_DVC
{
public:
	VIDEC_DVC(void){};
	virtual~VIDEC_DVC(void){};
public:
	virtual int Open(int nDevID,int nFrameRate,int nBitrate,int nBitrateControlType,int nResolution)=0;
	virtual void Close(void)=0;
	virtual int RequestKeyFrame(void)=0;
	virtual int SetParams(int nFrameRate,int nBitrate,int nBitrateControlType,int nResolution)=0;

	static int Init(void);
	static void Terminate(void);

	static int GetDevCount(void);
	static int GetDevName(int nDevID,char*szName,int nMaxCount);
	static int GetDevType(int nDevID,VIDEC_DEV_TYPE&nDevType);//SD HD VGA
	static bool HasAudioInput(int nDevID);
	static bool SupportHardwareEncoding(int nDevID);

	static VIDEC_DVC*Create(VIDEC_DVCCallback&rCallback);

	virtual int SendData(const char*pData,int nLen)=0;
};


#endif