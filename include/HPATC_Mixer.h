#ifndef __HPATC_MIXER_H__
#define __HPATC_MIXER_H__

#include "HPATC_Export.h"


class HPATC_API HPATC_Mixer;
class HPATC_MixerCallback
{
public:
	virtual void OnHPATC_MixerCallbackPacketData(HPATC_Mixer*pMixer,void*pPacketData,int nPacketLen,unsigned long ulTimestamp/*ԭ��Ƶ����ʱ��*/)=0;
};

//���ΪAAC���������ݣ�����Ϊ��AUDEC��Ƶ��ͷ����Ƶ����
class HPATC_API HPATC_Mixer 
{
public:
	HPATC_Mixer(void){};
	virtual~HPATC_Mixer(void){};
public:
	virtual int Open(int nMixCount,int nSampleRate=44100,int nSamplesPerFrame=1024)=0;
	virtual void Close()=0;

	/*���룺pPacketData����AUDEC��Ƶ��ͷ����Ƶ���ݣ�nPacketLen��Ƶ�������ݳ��ȣ�
	 *�����0���ɹ�����0��ʧ�ܣ�
	 *�ص����ϳɺ��AAC���������� */
	virtual int InputPacket(void*pPacketData,int nPacketLen,int nInputIndex)=0;

	static HPATC_Mixer*Create(HPATC_MixerCallback* pCallback);
};

#endif