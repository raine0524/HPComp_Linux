// stdafx.cpp : 只包括标准包含文件的源文件
// librecord.pch 将成为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"

bool mkmdir(const char*lpszFolder)
{
	char szDir[2048];
	strcpy(szDir, lpszFolder);

	int nLen = (int)strlen(szDir);
	if (szDir[nLen-1] == '\\' || szDir[nLen-1] == '/')
	{
		szDir[nLen-1] = '\0';
	}

	if (chdir(szDir) == -1)
	{
		char* p = NULL;
#ifdef WIN32
		while (mkdir(szDir) == -1)
#else
		while (mkdir(szDir, 0777) == -1)
#endif
		{
			p = strrchr(szDir, '\\');
			if (p == 0 || p == "")
			{
				p = strrchr(szDir, '/');
				if (p == 0 || p == "")
				{
					return false;
				}
			}
			*(p) = 0;
			if (mkmdir(szDir))
			{
				strcpy(szDir, lpszFolder);
			}
		}
	}
	return true;
}


unsigned long get_file_len(const char *filename)
{
	//如果文件不存在，返回0;
	if (!access(filename, 0) == 0)
	{
		return 0;
	}

	struct stat buf;
	if(stat(filename, &buf)<0)
	{
		return 0;
	}
	return (unsigned long)(buf.st_size/1024.0);
}

unsigned long GetFileLen(const char* lpszFileName, int nMode)
{

#ifdef WIN32
	__int64 iLength = 0;

	HANDLE hFile  = INVALID_HANDLE_VALUE;

	hFile = CreateFileA(lpszFileName,
		GENERIC_READ| GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL, OPEN_EXISTING, FILE_FLAG_RANDOM_ACCESS, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
		return (unsigned long)(iLength/1024.0);


	LARGE_INTEGER   li;
	if (GetFileSizeEx(hFile, &li))
		iLength = li.QuadPart;

	CloseHandle(hFile);
	if (nMode==0)
		return (unsigned long)(iLength/1024.0);
	else
		return (unsigned long)(iLength);
#else
	return get_file_len(lpszFileName);
#endif

}

#ifdef WIN32
unsigned long get_disk_free( const string& strPath)
{
	USES_CONVERSION;
	unsigned _int64 i64Free = 0;

	unsigned _int64 i64FreeBytesToCaller;
	unsigned _int64 i64TotalBytes;
	unsigned _int64 i64FreeBytes;

	string strDisk = strPath.substr( 0, 3);
	BOOL fResult = GetDiskFreeSpaceEx (
		A2W(strDisk.c_str()),
		(PULARGE_INTEGER)&i64FreeBytesToCaller,
		(PULARGE_INTEGER)&i64TotalBytes,
		(PULARGE_INTEGER)&i64FreeBytes);

	if ( fResult )
	{
		i64Free = (unsigned _int64)(i64FreeBytesToCaller / Msize);
	}
	return (unsigned long)i64Free;
}
#else
unsigned long get_disk_free( const string& strPath)
{
	long long llFreeM = 0;

	long long llFreeSize = 0;

	struct statfs fs;
	if (statfs( strPath.c_str(), &fs)<0)
	{
		printf("statfs( strPath = %s.\n",strPath.c_str());
		return 0;
	}

	// 应该统一为可用空间才行！
	llFreeSize = (long long)fs.f_bavail * fs.f_bsize;
	llFreeM = llFreeSize / Msize;
	//printf("llFreeM = %d\n",llFreeM);
	return llFreeM;
}
#endif

void GetDiskSpaceInfoM( const string& strPath, unsigned long& ulFree, unsigned long& ulTotal )
{
#ifdef WIN32	//----------------------------------------------------
	USES_CONVERSION;
	unsigned _int64 i64Free = 0, i64Total = 0;

	unsigned _int64 i64FreeBytesToCaller;
	unsigned _int64 i64TotalBytes;
	unsigned _int64 i64FreeBytes;

	string strDisk = strPath.substr( 0, 3);
	BOOL fResult = GetDiskFreeSpaceEx (
		A2W(strDisk.c_str()),
		(PULARGE_INTEGER)&i64FreeBytesToCaller,
		(PULARGE_INTEGER)&i64TotalBytes,
		(PULARGE_INTEGER)&i64FreeBytes);

	if ( fResult )
	{
		i64Free = i64FreeBytesToCaller / Msize;
		i64Total = i64TotalBytes / Msize;
	}

	ulFree = i64Free;
	ulTotal = i64Total;
#else

	long long llFreeM = 0, llTotalM = 0;

	long long llFreeSize = 0, llTotalSize = 0;

	struct statfs fs;
	if ( statfs( strPath.c_str(), &fs)<0)
	{
		LOG::ERR("statfs error!");
		return;
	}


	llFreeSize = (long long)fs.f_bavail * fs.f_bsize;
	llTotalSize = (long long)fs.f_blocks * fs.f_bsize;
	llFreeM = llFreeSize / Msize;
	llTotalM = llTotalSize / Msize;

	ulFree = llFreeM;
	ulTotal = llTotalM;
#endif          //----------------------------------------------------
}


unsigned long GenerateSSRC()

{

#ifdef WIN32
	LARGE_INTEGER frequence, privious;
	if(!QueryPerformanceFrequency( &frequence))//取高精度运行计数器的频率
	{
		return timeGetTime();
	}

	if (!QueryPerformanceCounter( &privious ))
	{
		return timeGetTime();
	}

	DWORD dwRet = (DWORD)(1000000 * privious.QuadPart / frequence.QuadPart ); //换算到微秒数

	return dwRet;//微秒
#else
	struct timeval now;
	gettimeofday(&now,NULL);
	return now.tv_sec*1000+now.tv_usec;
#endif

}



unsigned long GetTimestamp()

{

#ifdef WIN32

	return ::timeGetTime();     //millisec

#else
	struct timeval now;

	gettimeofday(&now, NULL);

	return now.tv_sec*1000+now.tv_usec/1000;

#endif

}


void SendToDevAgent(KCmdPacket& t, unsigned int nAgentID)

{

	std::string data = t.GetString();

	NETEC_Node::SendDataToAgent("", nAgentID, data.c_str(), (int)data.length()+1);

	LOG::INF("[HPCOMP]send dev-agent: %s", data.c_str());

}
