//VIDEC_RTPCall.h
#ifndef __VIDEC_RTPCALL_H__
#define __VIDEC_RTPCALL_H__

#include "VIDEC.h"


class VIDEC_API VIDEC_RTPCall
{
public:
	VIDEC_RTPCall(void){};
	virtual~VIDEC_RTPCall(void){};
public:
	virtual int Open(HWND hLocalWnd,int nDevID,int nLocalWidth,int nLocalHeight,int nFrameRate,int nBitrate,VIDEC_CODEC_TYPE nCodecType,int nPayloadType,const char*cszLocalIP,unsigned short nLocalPort,HWND hPeerWnd,const char*cszPeerIP,unsigned short nPeerPort)=0;
	virtual void Close(void)=0;

	virtual void SetLocalWndPos(int x,int y,int cx,int cy)=0;
	virtual int GetLocalWidth(void)=0;
	virtual int GetLocalHeight(void)=0;
	virtual HWND GetLocalWnd(void)=0;

	virtual void SetPeerWndPos(int x,int y,int cx,int cy)=0;
	virtual int GetPeerWidth(void)=0;
	virtual int GetPeerHeight(void)=0;
	virtual HWND GetPeerWnd(void)=0;

	static VIDEC_RTPCall*Create(void);
};


#endif
