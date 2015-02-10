//NETEC_UDPServer.h
#ifndef __NETEC_UDPSERVER_H__
#define __NETEC_UDPSERVER_H__

#include <NETEC/XSocket.h>
#include <NETEC/UDPServerPacket.h>

class NETEC_UDPServerNotify
{
public:
	NETEC_UDPServerNotify(void){};
	virtual~NETEC_UDPServerNotify(void){};
public:
	virtual bool OnNETEC_UDPServerNotifyRecvdPacket(UDPServerPacket*pUDPServerPacket)=0;
};

class NETEC_UDPServer
{
public:
	NETEC_UDPServer(void){};
	virtual~NETEC_UDPServer(void){};
public:
	virtual void ReleaseConnections(void)=0;
	virtual SOCKET GetSocketHandle(const char*cszLocalIP)=0;
};

NETEC_API NETEC_UDPServer*NETEC_UDPServerCreate(NETEC_UDPServerNotify&rNETEC_UDPServerNotify,unsigned short usUDPPort,unsigned char nTos=160);
NETEC_API NETEC_UDPServer*NETEC_UDPServerCreate(NETEC_UDPServerNotify&rNETEC_UDPServerNotify,unsigned short usUDPPort,const char*cszFirstLocalIP,unsigned char nTos=160);


#endif