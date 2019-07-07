#include "pch.h"
#include "gengine.h"

namespace Geass
{
	GBackgroundWorker			GEngine::BackgroundWorker;
	GTimer						GEngine::Timer;
	GConfiguration				GEngine::Config;
	GResourceProfiler			GEngine::ResourceProfiler;
	GSystemInfo					GEngine::SystemInfo;
	GEventBroadcaster			GEngine::EventBroadcasters[(UINT)EEngineEvent::EE_END];
	bool						GEngine::bInitialized(false);

	GDevice*					GEngine::Device(nullptr);
	GSceneManager*				GEngine::SceneManager(nullptr);


	bool GEngine::InitSharedResource()
	{
		return false;
	}

	void GEngine::DestroySharedResource()
	{
	}

}
