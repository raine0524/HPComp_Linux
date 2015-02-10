// stdafx.h : 标准系统包含文件的包含文件，
// 或是常用但不常更改的项目特定的包含文件
//

#pragma once

#ifdef _WIN32

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// 从 Windows 头中排除极少使用的资料
#endif

// 如果您必须使用下列所指定的平台之前的平台，则修改下面的定义。
// 有关不同平台的相应值的最新信息，请参考 MSDN。
#ifndef WINVER				// 允许使用特定于 Windows 95 和 Windows NT 4 或更高版本的功能。
#define WINVER 0x0400		// 将此更改为针对于 Windows 98 和 Windows 2000 或更高版本的合适的值。
#endif

#ifndef _WIN32_WINNT		// 允许使用特定于 Windows NT 4 或更高版本的功能。
#define _WIN32_WINNT 0x0400	// 将此更改为针对于 Windows 2000 或更高版本的合适的值。
#endif

#ifndef _WIN32_WINDOWS		// 允许使用特定于 Windows 98 或更高版本的功能。
#define _WIN32_WINDOWS 0x0410 // 将此更改为针对于 Windows Me 或更高版本的合适的值。
#endif

#ifndef _WIN32_IE			// 允许使用特定于 IE 4.0 或更高版本的功能。
#define _WIN32_IE 0x0400	// 将此更改为针对于 IE 5.0 或更高版本的合适的值。
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// 某些 CString 构造函数将为显式的

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE 类
#include <afxodlgs.h>       // MFC OLE 对话框类
#include <afxdisp.h>        // MFC 自动化类
#endif // _AFX_NO_OLE_SUPPORT

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>			// MFC ODBC 数据库类
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>			// MFC DAO 数据库类
#endif // _AFX_NO_DAO_SUPPORT

#include <afxdtctl.h>		// MFC 对 Internet Explorer 4 公共控件的支持
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <string>
#include <direct.h>
#include <io.h>
#include "KBASE.h"
#include "KRECDefine.h"

#ifdef _DEBUG
#pragma comment(lib,"../../lib/Debug/KBASE.lib")
#pragma comment(lib,"../../lib/Debug/KDBAPI.lib")
#pragma comment(lib,"../../lib/Debug/NETEC.lib")
#pragma comment(lib,"../../lib/Debug/HPATC.lib")
#pragma comment(lib,"../../lib/Debug/libRtmpStream.lib")
#pragma comment(lib,"../../lib/Debug/libAVWriter.lib")
#pragma comment(lib,"../../lib/Debug/HPRecordFactory.lib")
#else
#pragma comment(lib,"../../lib/Release/KBASE.lib")
#pragma comment(lib,"../../lib/Release/KRTL32.lib")
#pragma comment(lib,"../../lib/Release/KDBAPI.lib")
#pragma comment(lib,"../../lib/Release/NETEC.lib")
#endif

#else
/*linux系统头文件*/
#include <errno.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/resource.h>
#include <netinet/in.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <sys/un.h>
#include <semaphore.h>
#include <iconv.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/times.h>
#include <stdarg.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/vfs.h>

/*定义FIFO路径*/
#define FIFOPATH "/tmp/myfifo"

#ifdef AFX_EXT_CLASS
#undef AFX_EXT_CLASS
#endif
#define AFX_EXT_CLASS

#ifdef AFX_EXT_API
#undef AFX_EXT_API
#endif
#define AFX_EXT_API

#ifdef AVCON_API
#undef AVCON_API
#endif
#define AVCON_API

#ifdef CALLBACK
#undef CALLBACK
#endif
#define CALLBACK

typedef  unsigned char	BYTE ;
typedef  int			BOOL;
typedef  unsigned int	UINT;
typedef  void* 			LPVOID;
typedef  void* 			HANDLE;
typedef unsigned long   DWORD;
typedef unsigned short  WORD;
typedef long			LONG;
typedef char			CHAR;
typedef long long		__int64;


#define TRACE printf
#ifndef		TRUE
#define 	TRUE	1
#endif

#ifndef		FALSE
#define		FALSE	0
#endif

#define __stdcall
#define CALLBACK
#ifndef __HWND_defined
#define __HWND_defined
#endif
typedef long HWND;


#include "KBASE.h"
#endif

#define MAXBUF 4096
#define MAXLEN(a) (sizeof(a)-1)
#define MINLEN(a,b) (((a)>(b)) ? (b) : (a))

#include <time.h>
#include <iostream>
#include <string>
#include <map>
#include <list>
#include <vector>
using namespace std;
/*熊库*/
#include "NETEC/XThreadBase.h"
#include <NETEC/NETEC.h>
#include <NETEC/NETEC_Client.h>
#include <NETEC/NETEC_Core.h>
#include <NETEC/NETEC_Node.h>
#include <NETEC/NETEC_Setting.h>
#include <NETEC/NETEC.h>
#include <NETEC/XCritSec.h>
#include <NETEC/XAutoLock.h>

////周库
#ifdef AFX_EXT_CLASS
#undef AFX_EXT_CLASS
#endif
#define AFX_EXT_CLASS

#ifdef AFX_EXT_API
#undef AFX_EXT_API
#endif
#define AFX_EXT_API

#include "KXNCP.h"

#include "AllCmdDefine.h"


#define REQ_STREAM_NONE     0x00

#define REQ_STREAM_AUDIO    0x01

#define REQ_STREAM_VIDEO    0x02

#define REQ_STREAM_VSUB1    0x04

#define REQ_STREAM_VSUB2    0x08



typedef struct tagCONFIG

{

	std::string local_serverid;

	unsigned short local_ability;

	unsigned short local_fill;

	unsigned short local_loglevel;


	
	std::string server_host;

	unsigned short server_port;
} CONFIG;


extern CONFIG g_config;


#define MAX_PATH 260
#define Gsize (1024.00*1024.00*1024.00)
#define Msize (1024.00*1024.00)

bool			mkmdir(const char*lpszFolder);
unsigned long	get_file_len(const char *filename);
unsigned long	GetFileLen(const char* lpszFileName, int nMode=0);
unsigned long   get_disk_free(const string& strPath);
void GetDiskSpaceInfoM(const string& strPath, unsigned long& ulFree, unsigned long& ulTotal);


unsigned long GenerateSSRC();

unsigned long GetTimestamp();

void SendToDevAgent(KCmdPacket& t, unsigned int nAgentID);
