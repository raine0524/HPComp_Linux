//VIDEC_Device.h
#ifndef __VIDEC_DEVICE_H__
#define __VIDEC_DEVICE_H__

#include <winsock2.h>

#include "VIDEC_Export.h"

#define VIDEO_FRAME_TYPE_RGB24		0
#define VIDEO_FRAME_TYPE_YUV420		1


class VIDEC_DeviceCallback
{
public:
	virtual void OnVIDEC_DeviceCallbackFrameData(void*pFrameData,int nFrameLen,int nWidth,int nHeight,int nBitCount,int nFrameType){};
};

class VIDEC_API VIDEC_Device
{
public:
	VIDEC_Device(void){};
	virtual~VIDEC_Device(void){};
public:
	virtual int Open(int nDevID,int nWidth,int nHeight,int nFrameRate,int nFrameType)=0;
	virtual void Close(void)=0;
	virtual void ShowInputWnd(HWND hParentWnd)=0;
	virtual void ShowPropertyWnd(HWND hParentWnd)=0;

	static int Initialize(void);
	static void UnInitialize(void);
	static int GetDevCount(void);
	static int GetDevName(int nDevID,char*szName,int nMaxCount);

	static VIDEC_Device*Create(VIDEC_DeviceCallback&rCallback);
};

#endif
