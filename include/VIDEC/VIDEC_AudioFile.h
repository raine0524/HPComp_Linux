//VIDEC_AudioFile.h
#ifndef __VIDEC_AUDIOFILE_H__
#define __VIDEC_AUDIOFILE_H__

#include <VIDEC/VIDEC.h>

class VIDEC_API VIDEC_AudioFile;
class VIDEC_AudioFileCallback
{
public:
	VIDEC_AudioFileCallback(void){};
	virtual~VIDEC_AudioFileCallback(void){};
public:
	virtual void OnVIDEC_AudioFileCallbackPositionChanged(VIDEC_AudioFile*pAudioFile,unsigned long ulSeconds)=0;
	virtual void OnVIDEC_AudioFileCallbackEnd(VIDEC_AudioFile*pAudioFile)=0;
	virtual void OnVIDEC_AudioFileCallbackPCMData(VIDEC_AudioFile*pAudioFile,unsigned char*pPCMData,int nLen,int nSampleRate,unsigned long ulTimestamp)=0;
};

class VIDEC_API VIDEC_AudioFile
{
public:
	VIDEC_AudioFile(void){};
	virtual~VIDEC_AudioFile(void){};
public:
	virtual int Open(const char*cszFileName,bool bLoop)=0;
	virtual void Close(void)=0;

	virtual unsigned long GetDuration(void)=0;
	virtual unsigned long GetPosition(void)=0;
	virtual int Seek(unsigned long ulSeconds)=0;
	virtual int Pause(void)=0;
	virtual int Play(void)=0;
	virtual bool IsPlaying(void)=0;

	virtual int SetVolume(int nVolume)=0;
	virtual int SetMute(int nMute)=0;


	static VIDEC_AudioFile*Create(VIDEC_AudioFileCallback&rCallback);
};


#endif
