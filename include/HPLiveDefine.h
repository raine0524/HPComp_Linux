#pragma once

#define RECOVER_TIME 5   //任务开始时间早于5分钟则不恢复
#define ENDTIME      1   //任务结束时间小于1分钟则不执行
#define MAX_VIDEO_W	 1920
#define MAX_VIDEO_H	 1080
#define MIN_VIDEO_W  320
#define MIN_VIDEO_H	 240

typedef enum tm_type
{
	TM_2_PIC_IN_PIC		= 1,
	TM_3_L1_R2			= 2,
	TM_4_2X2			= 3,
	TM_4_L1_R3			= 4,
};

typedef enum protocol_type
{
	protocol_type_error = -1,
	protocol_type_ebox  = 0, //华平编码器
	protocol_type_h323	= 1, //H323协议设备
	protocol_type_rtsp	= 2, //RTSP协议设备
	protocol_type_rtmp	= 3, //RTMP协议设备
	//protocol_type_sip	= 4, 
};

typedef enum call_type
{
	call_type_in		= 0, //被动
	call_type_out		= 1, //主动
};

typedef enum link_status
{
	link_status_nolink			= 0,	//未连接         或者断开成功
	link_status_linkprocess		= 1,	//连接处理中     HPLIVE选择好服务发送连接
	link_status_linking			= 2,    //连接中		 处理服务反馈给HPLIVE连接状态 call out
	link_status_linked			= 3,	//已连接		 处理服务连接成功


	//link_status_unlinkprocess	= 5,	//断开处理中     HPLIVE选择好服务发送断开连接
	//link_status_unlinking		= 6,	//断开中         处理服务断开中HPLIVE发出断开连接
	//link_status_deleting		= 7,	//删除中
	//link_status_failed		= 8,	//连接失败处理服务连接失败
	//link_status_deletefail	= 9,	//删除失败
	//link_status_hangupfail	= 10,	//挂断失败
	//link_status_relink		= 11,	//重新连接
};

typedef enum play_status
{
	play_status_normal			= 0,  //没有回放
	play_status_process			= 1,  //处理中   HPLIVE发送给REC
	play_status_playing			= 2,  //回放中
	play_status_finish			= 3,  //回放结束
	play_status_failed			= 4,  //回放失败
};

typedef enum rec_status
{
	rec_status_normal			= 0, //未录像
	rec_status_recing			= 1, //录像中
	rec_status_pause			= 2,//录像暂停
};


typedef enum EnDeviceType
{
    DEV_ENCODER		= 0,	   // 编码器
    DEV_H323		= 1,	   //H323终端
	DEV_RTSP		= 2,	   //RTSP终端
	DEV_RTMP		= 3,	   //RTMP终端

	SERVER_REC		= 100, //录播服务器
    SERVER_COM		= 101, //合成服务器
	SERVER_HPH323   = 102, //HPH323
	SERVER_MP		= 103, //MP服务器
	SERVER_HPRTSP	= 104, //HPRTSP
	SERVER_HPRTMP	= 105, //HPRTMP

	SERVER_NGINX	= 200, //媒体服务器
	DEV_UNKNOWN		= 999, //未定义
};

struct PlayBack_File
{
	std::string fileid;
	std::string name;
	std::string filePath;	//全路径包含名称
	std::string callid;		//所属call

	PlayBack_File()
	{
		fileid		= "";
		name		= "";
		filePath	= "";
		callid		= "";
	};

	PlayBack_File(const PlayBack_File& other)
	{
		fileid		= other.fileid ;
		name		= other.name;
		filePath	= other.filePath;
		callid		= other.callid;
	};
};


struct DeviceBaseInfo
{
    std::string strDevID;
    unsigned short usDevType;
    std::string strNodeID;

    DeviceBaseInfo()
    {
        usDevType	= DEV_UNKNOWN;
		strDevID	= "";
		strNodeID	= "";
    };

    DeviceBaseInfo(const DeviceBaseInfo& other)
    {
        usDevType = other.usDevType ;
        strDevID = other.strDevID;
        strNodeID = other.strNodeID;
    };
};

//-------------------------------------
// 基本设备信息
typedef struct DeviceInfo : public DeviceBaseInfo
{
    DeviceInfo()
    {
        usChannelNum    = 0;
        usMcuPort       = 0;
        usLocalPort     = 0;
        usStatus		= 0;
        nNginxPort      = 0;
    }

    DeviceInfo(const DeviceInfo& other)
        :DeviceBaseInfo(other)
    {
        usChannelNum = other.usChannelNum;
        usStatus = other.usStatus;
        usLocalPort = other.usLocalPort;
        usMcuPort = other.usMcuPort;
        strDevName = other.strDevName;
        strMcuID = other.strMcuID;
        strMcuAddr = other.strMcuAddr;
        strNatAddr = other.strNatAddr;
        strNatType = other.strNatType;
        strLocalAddr = other.strLocalAddr;
        strMacAddr = other.strMacAddr;
        strURL = other.strURL;
		strVersion = other.strVersion;
		strAbility = other.strAbility;
        strServerID = other.strServerID;
        strServerIP = other.strServerIP;
        strAppName = other.strAppName;
        nNginxPort = other.nNginxPort;
    }

    unsigned short  usChannelNum;
	unsigned short  usStatus;
    unsigned short	usLocalPort;
    unsigned short	usMcuPort;

    // 设备的基本信息
    std::string     strDevName;

    // 实时数据信息
    std::string		strMcuID;
    std::string		strMcuAddr;
    std::string		strNatAddr;
    std::string     strNatType;
    std::string		strLocalAddr;
    std::string     strMacAddr;
    std::string     strURL;
	std::string     strVersion;
	std::string     strAbility;

    // RTMP
    std::string     strServerID;
    std::string     strServerIP;
    std::string     strAppName;
    unsigned int    nNginxPort;
} *PDeviceInfo;

//-------------------------------------
// 监控通道信息
typedef struct ChannelInfo
{
    ChannelInfo()
    {
        usChannelNo = 0;
        ulVideoCID = 0;
        ulAudioCID = 0;
    }
    std::string     strChannelID;
    std::string     strChannelName;
    std::string     strDevID;
    std::string     strNodeID;
    unsigned short  usChannelNo;
    unsigned long	ulVideoCID;
    unsigned long	ulAudioCID;
}*PChannelInfo;

template<typename T>
inline void CMDPacket( T& t, DeviceInfo& devInfo)
{
    t.SetAttrib( "USERID" , devInfo.strDevID);
    t.SetAttrib( "NAME", devInfo.strDevName);
    t.SetAttribUS( "CHANNELNUM" , devInfo.usChannelNum);
    t.SetAttribUS( "DEVIDTYPE" , devInfo.usDevType);

    t.SetAttrib( "MCUID:", devInfo.strMcuID);
    t.SetAttrib( "MCUADDR:", devInfo.strMcuAddr);
    t.SetAttribUS( "MCUPORT:", devInfo.usMcuPort);
    t.SetAttrib( "NODEID", devInfo.strNodeID);
    t.SetAttrib( "NATADDR:", devInfo.strNatAddr);
    t.SetAttrib( "NATTYPE", devInfo.strNatType);
    t.SetAttrib( "LOCALADDR:", devInfo.strLocalAddr);
    t.SetAttribUL( "LOCALPORT:", devInfo.usLocalPort);
    t.SetAttrib( "MACADDR", devInfo.strMacAddr);
    t.SetAttribUS( "STATUS", devInfo.usStatus);
    t.SetAttrib( "URL", devInfo.strURL);
    t.SetAttrib( "SERVERID",devInfo.strServerID);
    t.SetAttrib( "SERVERIP",devInfo.strServerIP);
    t.SetAttrib( "APP",devInfo.strAppName);
    t.SetAttribUN( "NGINXPORT",devInfo.nNginxPort);
}

//------------------------------------------------------------------------
template<typename T>
inline void CMDUnPacket( T& t, DeviceInfo& devInfo)
{
    devInfo.strDevID = t.GetAttrib( "USERID" ).AsString();
    devInfo.strDevName = t.GetAttrib( "NAME" ).AsString();
    devInfo.usChannelNum = t.GetAttrib( "CHANNELNUM" ).AsUnsignedShort();
    devInfo.usDevType = t.GetAttrib( "DEVICETYPE" ).AsUnsignedShort();

    devInfo.strMcuID = t.GetAttrib( "MCUID:" ).AsString();
    devInfo.strMcuAddr = t.GetAttrib( "MCUADDR:" ).AsString();
    devInfo.usMcuPort = t.GetAttrib( "MCUPORT:" ).AsUnsignedShort();
    devInfo.strNodeID = t.GetAttrib( "NODEID" ).AsString();
    devInfo.strNatAddr = t.GetAttrib( "NATADDR:" ).AsString();
    devInfo.strNatType = t.GetAttrib( "NATTYPE" ).AsString();
    devInfo.strLocalAddr = t.GetAttrib( "LOCALADDR:" ).AsString();
    devInfo.usLocalPort = t.GetAttrib( "LOCALPORT:" ).AsUnsignedShort();
    devInfo.strMacAddr= t.GetAttrib("MACADDR").AsString();
	devInfo.usStatus = t.GetAttrib("STATUS").AsUnsignedShort();
    devInfo.strURL = t.GetAttrib("URL").AsString();

    devInfo.strServerID = t.GetAttrib("SERVERID").AsString();
    devInfo.strServerIP = t.GetAttrib("SERVERIP").AsString();
    devInfo.strAppName  = t.GetAttrib("APP").AsString();
    devInfo.nNginxPort  = t.GetAttrib("NGINXPORT").AsUnsignedInt();
	devInfo.strVersion  = t.GetAttrib("VERSION").AsString();
    devInfo.strAbility  = t.GetAttrib("SKILL").AsString();
}

/************************************************************************/
/* 打包，解包通道信息                                                   */
/************************************************************************/
template<typename T>
inline void CMDPacket( T& t, PChannelInfo pChannelInfo)
{
    t.SetAttrib( "CHANNELID", pChannelInfo->strChannelID);
    t.SetAttrib( "CHANNELNAME:", pChannelInfo->strChannelName);
    t.SetAttrib( "DEVID", pChannelInfo->strDevID);
    t.SetAttrib( "NODEID", pChannelInfo->strNodeID);
    t.SetAttribUS( "CHNUM", pChannelInfo->usChannelNo);
    t.SetAttribUL( "VIDEOCID:", pChannelInfo->ulVideoCID);
    t.SetAttribUL( "AUDIOCID:", pChannelInfo->ulAudioCID);
}

//------------------------------------------------------------------------
template<typename T>
inline void CMDUnPacket( T& t, PChannelInfo pChannelInfo)
{
    pChannelInfo->strChannelID = t.GetAttrib( "CHANNELID" ).AsString();
    pChannelInfo->strDevID = t.GetAttrib( "DEVID" ).AsString();
    pChannelInfo->strChannelName = t.GetAttrib( "CHANNELNAME:" ).AsString();
    pChannelInfo->strNodeID = t.GetAttrib( "NODEID" ).AsString();
    pChannelInfo->usChannelNo = t.GetAttrib( "CHNUM" ).AsUnsignedShort();
    pChannelInfo->ulVideoCID = t.GetAttrib( "VIDEOCID:" ).AsUnsignedLong();
    pChannelInfo->ulAudioCID = t.GetAttrib( "AUDIOCID:" ).AsUnsignedLong();
    if(pChannelInfo->strChannelID.empty())
    {
        if(pChannelInfo->usChannelNo<10)
        {
            pChannelInfo->strChannelID = pChannelInfo->strDevID + "_0" + USHORT2STR(pChannelInfo->usChannelNo);
        }
        else
        {
            pChannelInfo->strChannelID = pChannelInfo->strDevID + '_' + USHORT2STR(pChannelInfo->usChannelNo);
        }
    }
}

typedef std::map<std::string,DeviceInfo> DEV_MAP;

typedef std::map<const std::string,DeviceBaseInfo*>	MapDevInfo;

typedef std::list<DeviceBaseInfo*> ListDevInfo;

struct TaskInfo
{
    TaskInfo()
    {
        usIsRecord = 0;
        usIsLive   = 0;
        usIsPublic = 0;
		usIsMobile = 0;
    };

    std::string strTaskID;
    unsigned short usIsRecord;
    unsigned short usIsLive;
    unsigned short usIsPublic;
	unsigned short usIsMobile;
};

typedef std::map<const std::string,TaskInfo> MapTaskInfo;

#define MAXVIEWERNUM 50
#define BALLANCEVIEWERNUM 5
#define URLITEM 5
#define IPADDR_POS 2
#define APP_POS 3
#define STREAMID_POS 4
#define RTMPHEADER "rtmp://"

#define ERR_RTMPAVAILABLE 1    //找到可用的RTMP服务器
#define ERR_NORTMPAVAILABLE 2  //没有可用的RTMP服务器
