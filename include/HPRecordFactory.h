
#ifndef __HPRECORD_FACTORY_H__
#define __HPRECORD_FACTORY_H__

#ifdef HPRF_EXPORT
#define HPRF_API _declspec(dllexport)
#elif HPRF_DLL
#define HPRF_API _declspec(dllimport)
#else
#define HPRF_API
#endif

typedef enum
{
	HPRF_FILE_MP4=0,
	HPRF_FILE_MKV=1,
	HPRF_FILE_FLV=2,
	HPRF_FILE_AVI=3,
	HPRF_FILE_AVMS=4,
	HPRF_FILE_MP3=5,
}HPRF_FILE_TYPE;


typedef void (*HPRF_CALLBACK_NEW_FILE)(void*pUserData,void*pHandle,char*cszNewFilePathName,char*cszLastFilePathName,unsigned long ulLastFileTime,unsigned long ulLastFileSize);

typedef void (*HPRF_CALLBACK_AAC_DATA)(void*pUserData,void*pHandle,void *pData,int nLen,unsigned long ulTimestamp);

/*设置产生新文件回调，三种情况会触发生此回调
 *1.当文件大小或长度达到设置的最大值时，自动分割成新的文件
 *2.当视频编码无法录制为设置的文件类型时，将自动生成新的*.avms类型文件 
 *3.当视频分辨率改变时，如果不是录制的avms文件，则自动分割成新的文件*/
HPRF_API void  HPRF_SetNewFileCallback(void*pUserData,void*pHandle,HPRF_CALLBACK_NEW_FILE cb_new_file);

/*设置获取AAC音频编码数据包回调，仅在录制MP4与MKV时有效,AAC编码格式串信息{0x12,0x08}*/
HPRF_API void  HPRF_SetAACDataCallback(void*pUserData,void*pHandle,HPRF_CALLBACK_AAC_DATA cb_aac_data);

/*MaxTime：秒为单位，系统可接受的最大值7200，默认值3600；
 *ulMaxSize：系统可接受的最大值2*1024*1024*1024，默认值1024*1024*1024，
 *MaxTime或者MaxSize 其中一个达到最大值，将自动切割文件*/
HPRF_API void  HPRF_SetMaxTimeSize(unsigned long ulMaxTime,unsigned long ulMaxSize);

/*获取当前文件的录制大小及长度，在调用HPRF_Close前有效，如果已经被自动切割，则返回的是切割后，当前正在录制的新文件长度及大小*/
HPRF_API void  HPRF_GetCurFileTimeSize(void*pHandle,unsigned long& ulFileTime,unsigned long& ulFileSize);

/*初始化录像工厂*/
HPRF_API void  HPRF_Init(void);

/*释放录像工厂*/
HPRF_API void  HPRF_UnInit(void);

/*开始录像*/
HPRF_API void* HPRF_Open(char*cszPathName,HPRF_FILE_TYPE type=HPRF_FILE_MP4);

/*结束录像*/
HPRF_API void  HPRF_Close(void*pHandle);

/*写入Videc原始数据,包含头信息，返回0为写入成功，非0为写入失败*/
HPRF_API int   HPRF_WriteVideo(void*pHandle,void *pData,int nLen);

/*写入Audec原始数据,包含头信息，返回0为写入成功，非0为写入失败*/
HPRF_API int   HPRF_WriteAudio(void*pHandle,void *pData,int nLen);

/*写入音频PCM数据，仅仅在录制非avms视频时有效，返回0为写入成功，非0为写入失败*/
HPRF_API int   HPRF_WriteAudioPCMData(void*pHandle,short*pSamples,int nSamples,int nSampleRate,unsigned long ulTimestamp);


#endif
