//NETEC_RouterAgent.h
#ifndef __NETEC_ROUTERAGENT_H__
#define __NETEC_ROUTERAGENT_H__

#include <NETEC/NETEC_Export.h>

//网络应用服务
class NETEC_RouterAgentCallback
{
public:
	NETEC_RouterAgentCallback(void){};
	virtual~NETEC_RouterAgentCallback(void){};
public:
	//网络节点与本网络应用断开连接的回调
	virtual void OnNETEC_RouterAgentNodeDisconnected(const char*cszDomain,const char*cszNodeID,const char*pData,int nLen){};

	//从其它网络应用收到的数据包回调
	virtual void OnNETEC_RouterAgentReceivedFromAgent(const char*cszDomain,unsigned int nAgentID,const char* pData,int nLen){};
	
	//从网络节点收到的数据包回调
	virtual void OnNETEC_RouterAgentReceivedFromNode(const char*cszDomain,const char*cszNodeID,const char* pData,int nLen){};

	//指定的Agent不存在
	virtual void OnNETEC_RouterAgentAgentDisconnected(const char*cszDomain,unsigned int nAgentID,const char* pData,int nLen){};

	//指定的Router不存在
	virtual void OnNETEC_RouterAgentRouterDisconnected(const char*cszDomain){};

	//从网络节点收到的数据包回调
	virtual void OnNETEC_RouterAgentReceivedFromRouter(const char* pData,int nLen){};

	//指定的MCU不存在
	virtual void OnNETEC_RouterAgentMCUDisconnected(const char*cszMCUID){};

	//从其它网络应用收到的数据包回调
	virtual void OnNETEC_RouterAgentCastFromAgent(const char*cszDomain,unsigned int nAgentID,const char* pData,int nLen){};
};

class NETEC_API NETEC_RouterAgent
{
public:
	NETEC_RouterAgent(void){};
	virtual~NETEC_RouterAgent(void){};
public:
	/******************************************************************************
	* Close
	*描述：关闭
	*输入：	无
	*输出： 无
	*返回值：无
	*****************************************************************************/
	virtual void Close(void)=0;

	/******************************************************************************
	* SendDataToAgent
	*描述：发送数据给指定的网络应用
	*输入：	cszDomain			-网络应用所在的域
			nAgentID			-网络应用标识
			pData				-要送的数据
			nLen				-要送的数据的长度
	*输出： 无
	*返回值：成功返回0；失败返回-1，表示网络未连通
	*****************************************************************************/
	virtual int SendDataToAgent(const char*cszDomain,unsigned int nAgentID,const char* pData,int nLen)=0;

	/******************************************************************************
	* CastDataToAgent
	*描述：广播数据给指定的网络应用
	*输入：	nAgentID			-网络应用标识
			pData				-要送的数据
			nLen				-要送的数据的长度
	*输出： 无
	*返回值：成功返回0；失败返回-1，表示网络未连通
	*****************************************************************************/
	virtual int CastDataToAgent(const char*cszToDomain,unsigned int nAgentID,const char* pData,int nLen)=0;

	/******************************************************************************
	* SendDataToNode
	*描述：发送数据给指定的网络节点
	*输入：	cszNodeID			-网络节点标识
			pData				-要送的数据
			nLen				-要送的数据的长度
	*输出： 无
	*返回值：成功返回0；失败返回-1，表示网络未连通
	*****************************************************************************/
	virtual int SendDataToNode(const char*cszNodeID,const char*pData,int nLen)=0;

	/******************************************************************************
	* GetDomain
	*描述：获取所在的域
	*输入：	无
	*输出： 无
	*返回值：所在的域
	*****************************************************************************/
	virtual const char*GetDomain(void)=0;

	/******************************************************************************
	* GetAgentID
	*描述：获取网络应用标识
	*输入：	无
	*输出： 无
	*返回值：网络应用标识
	*****************************************************************************/
	virtual unsigned int GetAgentID(void)=0;

	static NETEC_RouterAgent*Create(NETEC_RouterAgentCallback&rCallback,unsigned int nAgentID);

	/******************************************************************************
	* SendDataToMCU
	*描述：发送数据给指定的MCU
	*输入：	cszMCUID			-MCU标识
			pData				-要送的数据
			nLen				-要送的数据的长度
	*输出： 无
	*返回值：成功返回0；失败返回-1，表示网络未连通
	*****************************************************************************/
	virtual int SendDataToMCU(const char*cszMCUID,const char*pData,int nLen)=0;

};

#endif