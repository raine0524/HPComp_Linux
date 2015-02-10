/*	KBASE.h	Kenny Base Classes Library */

#pragma once

//---------------------------------------------------------------------------------------
// 预包含STL常用库
//---------------------------------------------------------------------------------------
#include <set>
#include <map>
#include <vector>
#include <list>
#include <queue>
#include <string>

using namespace std;

#ifdef WIN32
#include <winsock2.h>
#endif

//---------------------------------------------------------------------------------------
// 包含头文件
//---------------------------------------------------------------------------------------

#include "KBASE/Utils.h"
#include "KBASE/CmdLine.h"
#include "KBASE/Guid.h"
#include "KBASE/KUID.h"
#include "KBASE/File.h"
#include "KBASE/IniFile.h"
#include "KBASE/DLLManager.h"

#include "KBASE/String.h"
#include "KBASE/CritSec.h"
#include "KBASE/Event.h"
#include "KBASE/AutoLock.h"
#include "KBASE/Thread.h"
#include "KBASE/Timer.h"
#include "KBASE/List.h"
#include "KBASE/Logger.h"
#include "KBASE/DateTime.h"
#include "KBASE/Buffer.h"
#include "KBASE/BufferPool.h"

#include "KBASE/XMLParser.h"
#include "KBASE/MD5.h"
#include "KBASE/Zip.h"
#include "KBASE/ZipEx.h"

#include "KBASE/CmdBuffer.h"
#include "KBASE/CmdPacket.h"

#include "KBASE/KXMLNode.h"
#include "KBASE/KXMLCData.h"
#include "KBASE/KXMLAccumulator.h"
#include "KBASE/KXMLElement.h"
#include "KBASE/KXMLElementStream.h"
#include "KBASE/KXMLPacket.h"

#include "KBASE/DataPacket.h"
#include "KBASE/INIReader.h"