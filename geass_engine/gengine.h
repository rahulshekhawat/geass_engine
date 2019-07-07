#pragma once

// #define _SHADER30

/*
#include "RTimer.h"
#include "RConfiguration.h"
#include "RProfileInfo.h"
#include "RSystemInfo.h"
#include "RBackgroundWorker.h"
#include "RListener.h"
*/

#include "pch.h"
#include "ge_lib.h"
#include "gtimer.h"
#include "gprofileinfo.h"
#include "gconfiguration.h"
#include "glistener.h"
#include "gsysteminfo.h"
#include "gbackgroundworker.h"

#include <set>
#include <string>
#include <vector>
#include <assert.h>

/*
#define INIT_TCHECK( msg )	\
RTimeChecker100us tc; bool bCheckTime = false;		\
if (false == REngine::m_strDebugFlags.empty()){		\
	if (REngine::m_strDebugFlags.find(msg) != std::string::npos) bCheckTime = true;}

#define BEGIN_TCHECK	if(bCheckTime)	tc.Start();
#define END_TCHECK( msg )	\
if (bCheckTime){			\
	REngine::m_uintDebugInfo.push_back(tc.Check());	\
	REngine::m_strDebugInfo.push_back(msg);}
*/

namespace Geass
{
	class GDevice;
	class GSceneManager;

	class GEASSENGINE_API GEngine
	{
		GEngine() {}
		virtual ~GEngine() {}

	public:

		inline static GBackgroundWorker& GetBackgroundWorker() { return BackgroundWorker; }
		inline static GTimer& GetTimer() { return Timer; }
		inline static GConfiguration& GetConfig() { return Config; }
		inline static GResourceProfiler& GetResourceProfiler() { return ResourceProfiler; }
		inline static GSystemInfo& GetSystemInfo() { return SystemInfo; }

		inline static GDevice& GetDevice() { assert(Device); return *Device; }
		inline static GDevice* GetDevicePtr() { return Device; }

		inline static GSceneManager& GetSceneManager() { assert(SceneManager); return *SceneManager; }
		inline static GSceneManager* GetSceneManagerPtr() { return SceneManager; }

		static void RegisterDevice(GDevice* pDevice) { Device = pDevice; }
		static void RegisterSceneManager(GSceneManager* pSceneManager) { SceneManager = pSceneManager; }

		static bool InitSharedResource();
		static void DestroySharedResource();

		static bool IsDevelopVersion() { return false; }

		static bool							bUseSkinning;
		static std::string					strDebugFlags;
		static std::vector<unsigned int>	uintDebugInfo;
		static std::vector<std::string>		strDebugInfo;

	private:

		static GDevice*						Device;
		static GSceneManager*				SceneManager;

		static GBackgroundWorker			BackgroundWorker;
		static GTimer						Timer;
		static GConfiguration				Config;
		static GResourceProfiler			ResourceProfiler;
		static GSystemInfo					SystemInfo;
		static GEventBroadcaster			EventBroadcasters[(UINT) EEngineEvent::EE_END];	// event broadcaster
		static bool							bInitialized;


		/*


		// event
		inline static REventBroadcaster* GetEventBroadcaster(REVENT eEvent)
		{
			if (eEvent < RE_NONE || eEvent >= RE_END) return NULL;
			return &m_eventBroadcasters[eEvent];
		}

		inline static bool BroadcastEvent(REVENT eEvent)
		{
			REventBroadcaster* pEventBroadcaster = GetEventBroadcaster(eEvent);
			if (!pEventBroadcaster) return false;

			pEventBroadcaster->Notify();

			return true;
		}

		*/
	};

}
