#ifndef HPCOMPOSITEDEFINE_H_
#define HPCOMPOSITEDEFINE_H_

#include <vector>
#include <string>

typedef struct _tagTASKSTREAM
{
    std::string     strNodeID;
    std::string     strDevID;
    std::string     strCHLID;
    std::string     strMCUID;
    std::string     strMCUAddr;
    unsigned short  usMCUPort;
    std::string     strNATAddr;
    std::string     strLocalAddr;
    unsigned short  usLocalPort;
    unsigned long   ulAudioID;
    unsigned long   ulVideoID;
    unsigned long   ulWndIndex;

	_tagTASKSTREAM()
	{
	    strNodeID   = "";
	    strDevID    = "";
	    strCHLID    = "";
	    strMCUID    = "";
	    strMCUAddr  = "";
	    usMCUPort   = 0;
	    strNATAddr  = "";
	    strLocalAddr= "";
	    usLocalPort = 0;
	    ulAudioID   = 0;
	    ulVideoID   = 0;
	    ulWndIndex  = 0;
	}
}TASK_STREAM;

typedef std::vector<TASK_STREAM>		VEC_STREAM;

typedef struct _tagTASKINFO
{
    std::string     strTaskID;
	std::string     strTaskName;
	bool            bUseHigh;
	unsigned int uHighWidth;
	unsigned int uHighHeight;
	unsigned int uHighBitrate;
	bool            bUseMid;
	unsigned int uMidWidth;
	unsigned int uMidHeight;
	unsigned int uMidBitrate;
	bool            bUseLow;
	unsigned int uLowWidth;
	unsigned int uLowHeight;
	unsigned int uLowBitrate;
	unsigned int    uTMID;

	_tagTASKINFO()
	{
		strTaskID	= "";
		strTaskName	= "";
		bUseHigh	= false;
		bUseMid		= false;
		bUseLow     = false;
		uTMID		= 0;
	}

}COMP_TASKINFO;
#endif  //HPCOMPOSITEDEFINE_H_
