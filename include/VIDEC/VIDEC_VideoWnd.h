//VIDEC_VideoWnd.h
#ifndef __VIDEC_VIDEOWND_H__
#define __VIDEC_VIDEOWND_H__

#include <winsock2.h>
#include <windows.h>

#include <VIDEC/VIDEC_Export.h>

class VIDEC_API VIDEC_VideoWnd
{
public:
	VIDEC_VideoWnd(void){};
	virtual~VIDEC_VideoWnd(void){};
public:
	//取视频宽度
	virtual int GetVideoWidth(void)=0;
	//取视频高度
	virtual int GetVideoHeight(void)=0;

	//取视频窗口
	virtual HWND GetWnd(void)=0;
	//same as CWnd::IsWindowVisible
	virtual bool IsWindowVisible(void)=0;
	//same as CWnd::SetWindowPos
	virtual bool SetWindowPos(HWND hWndInsertAfter,int x,int y,int cx,int cy,UINT nFlags)=0; 

	//保持当前图象到BMP文件
	virtual bool CaptureToBMPFile(const char*cszFile)=0;

	virtual double GetAverageFPS(void)=0;

	//设置视频属性
	virtual int SetVideoParam(int nBrightness=128/*亮度值0-255*/, int nContrast=64/*对比度0-127*/, int nSaturation=64/*饱和度0-127*/, int nHue=0/*色调0-255*/,int nGamma=100/*伽马1-400*/,int nSharpen=0/*锐化0-127*/)=0;
	//int nGammaR[1-400 100]
	//int nGammaG[1-400 100]
	//int nGammaB[1-400 100]
	virtual int SetVideoGammaRGB(int nGammaR,int nGammaG,int nGammaB)=0;
	//设置图像显示模式

	/******************************************************************************
	* SetScreenWnd
	*描述：设置所在屏幕窗口位置
	*输入：	nScreenIndex	-屏幕号
			nWndIndex		-窗口号
			nFullScreen		-是否全屏显示【0：普通显示，非0：全屏显示】
	*输出：无
	*返回值：无
	*****************************************************************************/
	virtual void SetScreenWnd(int nScreenIndex,int nWndIndex,int nFullScreen)=0;

	virtual void EnablePreview(int nPreview)=0;
};

#endif