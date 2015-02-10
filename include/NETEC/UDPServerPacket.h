//UDPServerPacket.h

#ifndef __UDPSERVERPACKET_H__
#define __UDPSERVERPACKET_H__

#ifndef _WIN32
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <cstdio>
#include <cerrno>
#else
#include <winsock2.h>
#include <ws2tcpip.h>

#ifdef NETEC_ARM

#else
#include <wspiapi.h>
#endif

#ifndef IOVEC
#define IOVEC
struct iovec
{
	int		iov_len;
	char*	iov_base;
};
#endif

#endif

#include <NETEC/XSocket.h>

class NETEC_API UDPServerPacket
{
public:
	UDPServerPacket(SOCKET hSocket,struct sockaddr*addr,int addrlen,const char*pData,int nDataLen);
	UDPServerPacket(SOCKET hSocket,const int&af,int nBufLen);
	virtual~UDPServerPacket();
public:
	char*GetData(void);
	int GetDataLen(void);
	SOCKET GetSocketHandle(void);

	int getaf(void);
	struct sockaddr*getaddr(void);
	int getaddrlen(void);

	int Send(void);
	int Recv(void);
protected:
	iovec			m_PacketVector;
	char*			m_pData;
	int				m_nDataLen;
	int				m_nBufLen;

	SOCKET			m_hSocket;
	
	struct sockaddr*m_pAddr;
	int				m_nAddrLen;

	struct sockaddr_in m_saIPV4;
	struct sockaddr_in6 m_saIPV6;

	int					m_af;
};



#endif
