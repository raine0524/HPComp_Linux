#include <signal.h>
#include <unistd.h>
#include "CompManager.h"

bool g_bWantToStop = false;
bool ParseConfigFile(const std::string& strConfigFile);

void sig_callback(int signo)
{
    if (2 == signo)
    {
        printf("Get a signal -- SIGINT");
        g_bWantToStop = true;
    }
}

int main(int argc, char* argv[])
{
    signal(SIGINT, sig_callback);
    KCmdLine CmdLine(argc, argv);
    //Parse arguments and XML config file
    std::string strConfigFile = CmdLine.GetOptionParamValue("-c");
    if (strConfigFile.empty())
    {
        printf("[HPCOMP]Cannot find config file.\n");
        return 1;
    }
    if (!ParseConfigFile(strConfigFile))
    {
        printf("[HPCOMP]Config error: <avcond-comp>.\n");
        return 2;
    }

    //Setup log level
    if (!LOG::START((LOG_LEVEL)g_config.local_loglevel))
    {
        LOG::STOP();
        printf("[HPCOMP]Logger start failed.\n");
        return 3;
    }

    //Startup composite service
    CompManager compMgr;
    if (!compMgr.Start())
    {
        compMgr.Stop();
        printf("[HPCOMP]Local server start failed.\n");
        return 4;
    }

    while (!g_bWantToStop)
    {
        //TODO:
        Pause(100);
    }
    compMgr.Stop();
    LOG::STOP();
    return EXIT_SUCCESS;
}

//--------------------------------------------------------
//Parse XML config file
bool ParseConfigFile(const std::string& strConfigFile)
{
    //config
    XMLNode xConfigNode = XMLNode::OpenFile(strConfigFile.c_str(), "config");
    if (xConfigNode.IsEmpty())
    {
        printf("[HPCOMP]Config error <config>.\n");
        return false;
    }

    //config/local
    XMLNode xLocalNode = xConfigNode.GetChildNode("local");
    if (xLocalNode.IsEmpty())
    {
        printf("[HPCOMP]Config error <config/local>.\n");
        return false;
    }
    g_config.local_serverid = NONULLSTR(xLocalNode.GetAttribute("id"));
    g_config.local_ability  = STR2USHORT(NONULLSTR(xLocalNode.GetAttribute("ability")));
    g_config.local_fill     = STR2USHORT(NONULLSTR(xLocalNode.GetAttribute("fill")));

    //config/local/log
    XMLNode xLocalLogNode = xLocalNode.GetChildNode("log");
    if (xLocalLogNode.IsEmpty())
    {
        printf("[HPCOMP]Config error <config/local/log>.\n");
        return false;
    }
    g_config.local_loglevel = STR2USHORT(NONULLSTR(xLocalLogNode.GetAttribute("level")));

    //config/server
    XMLNode xServerNode = xConfigNode.GetChildNode("server");
    if (xServerNode.IsEmpty())
    {
        printf("[HPCOMP]Config error <config/server>.\n");
        return false;
    }
    g_config.server_host = NONULLSTR(xServerNode.GetAttribute("host"));
    g_config.server_port = STR2USHORT(NONULLSTR(xServerNode.GetAttribute("port")));

    return true;
}
