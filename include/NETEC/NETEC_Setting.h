//NETEC_Setting.h
#ifndef __NETEC_SETTING_H__
#define __NETEC_SETTING_H__

#include <NETEC/NETEC_Export.h>

//网络设置
class NETEC_API NETEC_Setting
{ 
public:
	NETEC_Setting(void);
	virtual~NETEC_Setting(void);
	
public:
	typedef enum{
		PT_NONE=0,		//无代理，直接连接
		PT_HTTP_PROXY,	//HTTP代理
		PT_SOCK5,		//SOCK5代理
		PT_HTTP_TUNNEL,	//HTTP隧道
		PT_HTTPS_TUNNEL	//HTTPS隧道
	}PROXY_TYPE;

	typedef enum{
		PT_TCP=0,		//TCP传输协议
		PT_UDP,			//UDP传输协议
		PT_RTP,			//RTP传输协议
		PT_AUDP,		//AUDP传输协议
	}PROTOCOL_TYPE;
	
	typedef enum{
		ST_NONE=0,
		ST_BIT,
		//ST_ZIP,
		ST_COUNT
	}SECURITY_TYPE;
public:
	//设置网络通讯协议类型
	static void SetSessionProtocolType(NETEC_Setting::PROTOCOL_TYPE type);
	static NETEC_Setting::PROTOCOL_TYPE GetSessionProtocolType(void);

	//设置音频传输协议类型
	static void SetAudioProtocolType(NETEC_Setting::PROTOCOL_TYPE type);
	static NETEC_Setting::PROTOCOL_TYPE GetAudioProtocolType(void);

	//设置视频传输协议类型
	static void SetVideoProtocolType(NETEC_Setting::PROTOCOL_TYPE type);
	static NETEC_Setting::PROTOCOL_TYPE GetVideoProtocolType(void);

	//设置数据传输协议类型
	static void SetDataProtocolType(NETEC_Setting::PROTOCOL_TYPE type);
	static NETEC_Setting::PROTOCOL_TYPE GetDataProtocolType(void);

	//设置是否只使用MCU
	static void SetMCUOnly(int nMCUOnly);
	static int GetMCUOnly(void);
	
	//设置代理类型
	static void SetProxyType(NETEC_Setting::PROXY_TYPE pt);
	static NETEC_Setting::PROXY_TYPE GetProxyType(void);
	
	//设置代理用户
	static void SetProxyUser(const char* cszUser);
	static const char*GetProxyUser(void);
	
	//设置代理密码
	static void SetProxyPassword(const char* cszPassword);
	static const char*GetProxyPassword(void);
	
	//设置代理服务器
	static void SetProxyHost(const char* cszHost);
	static const char*GetProxyHost(void);
	static void SetProxyPort(unsigned short usPort);
	static unsigned short GetProxyPort(void);

	//设置是否使用组播
	static void SetEnableMulticast(int nEnableMulticast);
	static int GetEnableMulticast(void);

	//设置是否使用多网络合并传输视频
	static void SetEnableMultiIF(int nEnableMultiIF);
	static int GetEnableMultiIF(void);

	//设置是否使用多线程传输视频
	static void SetEnableMultiPort(int nEnableMultiPort);
	static int GetEnableMultiPort(void);

	//设置优先使用的本地IP地址
	static void SetFirstLocalIP(const char*cszLocalIP);
	static const char*GetFirstLocalIP(void);

	static void SetSecurityType(NETEC_Setting::SECURITY_TYPE nType);
	static NETEC_Setting::SECURITY_TYPE GetSecurityType(void);

	static void SetRunningMGS(int nRunningMGS);
	static int GetRunningMGS(void);

	//设置是否启用IPV6
	static void SetEnableIPV6(int nEnableIPV6);
	static int GetEnableIPV6(void);

	static void SetEnableDynamicChannel(int nEnable);
	static int GetEnableDynamicChannel(void);
};

#endif