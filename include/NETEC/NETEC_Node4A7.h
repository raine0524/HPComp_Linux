//NETEC_Node4A7.h
#ifndef __NETEC_NODE4A7__
#define __NETEC_NODE4A7__

#include <NETEC/NETEC_Export.h>

class NETEC_Node4A7Callback
{
public:
	virtual void OnNETEC_Node4A7CallbackConnecting(void)=0;
	virtual void OnNETEC_Node4A7CallbackConnected(void)=0;
	virtual void OnNETEC_Node4A7CallbackReconnecting(void)=0;
	virtual void OnNETEC_Node4A7CallbackReconnected(void)=0;
	virtual void OnNETEC_Node4A7CallbackDisconnected(void)=0;
	virtual void OnNETEC_Node4A7CallbackRcvdDataFromMC(const char*cszDomain,const char*cszData)=0;
	virtual void OnNETEC_Node4A7CallbackMCUnreachable(const char*cszDomain,const char*cszData)=0;
	virtual void OnNETEC_Node4A7CallbackRcvdDataFromNode(const char*cszNodeID,const char*cszData)=0;
	virtual void OnNETEC_Node4A7CallbackNodeUnreachable(const char*cszNodeID,const char*cszData)=0;
};

class NETEC_API NETEC_Node4A7
{
public:
	NETEC_Node4A7(void){};
	virtual~NETEC_Node4A7(void){};
public:
	virtual int Open(const char*cszMCUIP,unsigned short nMCUPort)=0;
	virtual void Close(void)=0;
	virtual const char*GetDomain(void)=0;
	virtual const char*GetMCUID(void)=0;
	virtual const char*GetMCUIP(void)=0;
	virtual unsigned short GetMCUPort(void)=0;
	virtual int SendDataToMC(const char*cszDomain,const char*cszData)=0;
	virtual int SendDataToNode(const char*cszNodeID,const char*cszData)=0;

	static NETEC_Node4A7*Create(NETEC_Node4A7Callback&rCallback);
};

#endif
