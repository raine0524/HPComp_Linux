#pragma once

#define AVCON_SERVER_VERSION		"6.3.5985"

//////////////////////////////////////////////////////////////////////////////////////
//									SYS												//
//////////////////////////////////////////////////////////////////////////////////////

#define IO_CONNECT_TYPE_CLIENT_SVC			100
#define IO_CONNECT_TYPE_CLIENT_NFS			103		//兼容老版本
#define IO_CONNECT_TYPE_CLIENT_MGW			104
#define IO_CONNECT_TYPE_CLIENT_VRS			105		//监控录像上传
#define IO_CONNECT_TYPE_CLIENT_PLT			106		//监控平台
#define IO_CONNECT_TYPE_CLIENT_NDU          107
#define IO_CONNECT_TYPE_CLIENT_NDD          108
#define IO_CONNECT_TYPE_CLIENT_NDI          109

#define IO_CONNECT_TYPE_MCU_ROUTER			200
#define IO_CONNECT_TYPE_NFS_ROUTER			201

#define SERVER_TYPE_MCU						300
#define SERVER_TYPE_MTS						301
#define SERVER_TYPE_MCU_MTS					302
#define SERVER_TYPE_GW						303
#define SERVER_TYPE_3GC						304
#define SERVER_TYPE_3GM						305
#define SERVER_TYPE_MP						306

#define DEV_AGENT_ID                        402
#define WEB_AGENT_ID                        403
#define REC_AGENT_ID                        404


//---------------------------------------------------------
// 文件传输常量
#define MAX_FILE_PACKET			65536 + 64
#define MAX_FILE_DATA_PACKET	65536
#define MAX_CMD_PACKET			32768 * 3

//=======================================================================================
// 错误代码
//=======================================================================================
#define	ERR_NO							00000		//正确

//---------------------------------------------------------------------------------------
// 系统类或网络类错误代码
//---------------------------------------------------------------------------------------
#define	ERR_SYS_PROTOCOL				10000		//通讯协议版本不匹配
#define	ERR_SYS_UNKNOWN					10001		//未知错误
#define	ERR_SYS_COMMAND					10002		//协议命令错误
#define	ERR_SYS_DATABASE				10003		//数据库错误
#define	ERR_SYS_NETWORK					10004		//网络断开(网络通路断开)
#define	ERR_SYS_SERVERTYPE				10005		//服务器类型错误,登录到错误类型的服务器
#define	ERR_SYS_LICEXPIRED              10006       //服务器授权到期
//---------------------------------------------------------------------------------------
// 即时通讯类错误代码
//---------------------------------------------------------------------------------------
#define	ERR_IMS_PROTOCOL				20000		//通讯协议版本不匹配
#define	ERR_IMS_INVALIDACCOUNT			20001		//无效的账户(系统没有该账户ID)
#define	ERR_IMS_INVALIDPASSWORD			20002		//无效的密码
#define	ERR_IMS_DUPLICATELOGIN			20003		//该账户已经登录,不得重复登录


//----------------------------------------------------------------------------------------
// 录像服务器错误代码
//----------------------------------------------------------------------------------------
#define ERR_REC_NOSERVER				70000		//没有可用的录像服务器
#define ERR_REC_SVRRES_BUSY				70001		//录播服务器忙
#define ERR_REC_SVR_EXCEPTION			70002		//录播服务器异常
#define ERR_REC_SERVER_INVALIDTYPE		70003		//无效的账户类型
#define ERR_REC_SERVER_CANNOT_STOP		70004		//无法停止录像
#define ERR_REC_STOP					70005		//异常停止录像
#define ERR_REC_CUT						70006		//切割视频
#define ERR_REC_NO_CONF					70007		//会议没在录像
#define ERR_REC_CONF_CUT				70008		//会议录像分割
#define ERR_REC_SEVER_UNKNOWN			70099		//未知错误(保留)


//呼叫错误代码
#define  ERR_INVALID_DEVTYPE          80000     //设备类型错误
#define  ERR_INVALID_DEVID            80001     //没有指定的Dev账号
#define  ERR_DUPLICATE_REG            80002     //账号重复登录
#define  ERR_DUPLICATE_DEVID          80003     //错误的设备账号
#define  ERR_INVALID_CHANNELID        80004     //错误的通道id
#define  ERR_NO_RECORD_AVAILABLE      80005     //没有合适的录播服务器
#define  ERR_COM_UNAVAILABLE          80006     //没有合适的合成服务器
#define  ERR_HPH323_NO_MP			  80007		//没有合适的MP
#define  ERR_CALL_IS_PROCESS		  80008		//连接已存在，在处理中
