//NETEC_TCPServer.h
#ifndef __NETEC_TCPSERVER__
#define __NETEC_TCPSERVER__

#include <NETEC/XSocket.h>

class NETEC_TCPServerNotify
{
public:
	NETEC_TCPServerNotify(void){};
	virtual~NETEC_TCPServerNotify(void){};
public:
	virtual bool OnNETEC_TCPServerNotifyConnected(SOCKET hSocket,const char*cszLocalIP,const char*cszPeerIP)=0;
};

class NETEC_TCPServer
{
public:
	NETEC_TCPServer(void){};
	virtual~NETEC_TCPServer(void){};
public:
	virtual void ReleaseConnections(void)=0;
};

NETEC_API NETEC_TCPServer*NETEC_TCPServerCreate(NETEC_TCPServerNotify&rNETEC_TCPServerNotify,unsigned short usTCPPort);

class NETEC_TCPServerStreamCallback
{
public:
	NETEC_TCPServerStreamCallback(void){};
	virtual~NETEC_TCPServerStreamCallback(void){};
public:
	virtual void OnNETEC_TCPServerStreamCallbackRecvdData(const char*pData,int nLen)=0;
	virtual void OnNETEC_TCPServerStreamCallbackDisconnected(void)=0;
};

class NETEC_API NETEC_TCPServerStream
{
public:
	NETEC_TCPServerStream(void){};
	virtual~NETEC_TCPServerStream(void){};
public:
	virtual void Close(void)=0;
	virtual int SendData(const char*pData,int nLen)=0;

	static NETEC_TCPServerStream*Create(NETEC_TCPServerStreamCallback&rCallback,SOCKET hSocket,const char*cszLocalIP,const char*cszPeerIP);
};

#endif
