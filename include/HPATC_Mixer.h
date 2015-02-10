#ifndef __HPATC_MIXER_H__
#define __HPATC_MIXER_H__

#include "HPATC_Export.h"


class HPATC_API HPATC_Mixer;
class HPATC_MixerCallback
{
public:
	virtual void OnHPATC_MixerCallbackPacketData(HPATC_Mixer*pMixer,void*pPacketData,int nPacketLen,unsigned long ulTimestamp/*原音频编码时间*/)=0;
};

//输出为AAC编码裸数据，输入为带AUDEC音频包头的音频数据
class HPATC_API HPATC_Mixer 
{
public:
	HPATC_Mixer(void){};
	virtual~HPATC_Mixer(void){};
public:
	virtual int Open(int nMixCount,int nSampleRate=44100,int nSamplesPerFrame=1024)=0;
	virtual void Close()=0;

	/*输入：pPacketData，带AUDEC音频包头的音频数据；nPacketLen音频数据数据长度；
	 *输出：0：成功；非0：失败；
	 *回调：合成后的AAC编码裸数据 */
	virtual int InputPacket(void*pPacketData,int nPacketLen,int nInputIndex)=0;

	static HPATC_Mixer*Create(HPATC_MixerCallback* pCallback);
};

#endif