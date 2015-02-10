//NETEC_DVC.h
#ifndef __NETEC_DVC_H__
#define __NETEC_DVC_H__

#include <NETEC/NETEC_Export.h>

class NETEC_DVCCallback
{
public:
	virtual void OnNETEC_DVCCallbackVideoFrameData(unsigned char*pFrameData,int nFrameLen)=0;
};

class NETEC_API NETEC_DVC
{
public:
	NETEC_DVC(void){};
	virtual~NETEC_DVC(void){};
public:
	virtual int Open(const char*cszIP,unsigned short nPort,const char*cszPassword)=0;
	virtual void Close(void)=0;
	virtual int GetConnected(void)=0;
	virtual int GetErrorCode(void)=0;
	virtual void SetVideoParams(unsigned short usVideoCodec,unsigned short usBitrate,unsigned short usBitCtrlType,unsigned short usResolution,unsigned short usFps,unsigned short usVideoSource)=0;
	virtual void RequestKeyFrame(void)=0;
	virtual int SendData(const char*pData,int nLen)=0;

	static NETEC_DVC*Create(NETEC_DVCCallback&rCallback);
};

#endif
