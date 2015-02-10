#ifndef HPCOMPOSITE_H_
#define HPCOMPOSITE_H_

#include "stdafx.h"
#include "TaskProcess.h"
#include "HPStreamParse.h"

typedef std::map<std::string, TaskProcess*> MAP_TASKPROC;
typedef std::map<std::string, HPStreamParse*> MAP_STREAMPARSER;

/**
 * \brief HPComposite class.
 * \details Manages TaskProcess and HPStreamParse objects.
 * \Note that since all of the task-related methods in the same thread,
 * \so there's no need to create critical section, the sole difference of them
 * \is in time sequence, moreover that the operation of receive or release stream
 * \just only happen in the routine of start or stop task.
 */
class HPComposite
:public TaskProcessNotify
{
public:
    HPComposite() { m_mapTask.clear(); m_mapStream.clear(); }
    virtual ~HPComposite() {}

public:
    bool StartTask(const COMP_TASKINFO& stTaskInfo, const VEC_STREAM& vTaskStream);
    bool ModifyTask(const COMP_TASKINFO& stTaskInfo, const VEC_STREAM& vTaskStream);
    void StopTask(const std::string& strTaskID);
    void StopAllTask();
    bool OnCHLChanged(const TASK_STREAM& stTaskStream);

    //Callback function
    virtual void OnReceiveStream(const TASK_STREAM& stTaskStream, const std::string& strTaskID);
    virtual void OnReleaseStream(const std::string& strStreamID, const std::string& strTaskID);

private:
    HPStreamParse* FindStreamParse(const std::string& strStreamID);
    HPStreamParse* CreateStream(const TASK_STREAM& stTaskStream);

private:
    MAP_TASKPROC m_mapTask;
    MAP_STREAMPARSER m_mapStream;
};

#endif  //HPCOMPOSITE_H_
