#pragma once

namespace Geass
{
	enum class EEngineEvent
	{
		EE_NONE = 0,
		EE_SHADOW_CHANGE,
		EE_RENDERING_CHANGE,
		EE_ENVIRONMENT_CHANGE,
		EE_ENVIRONMENT_BLENDING,
		EE_DEVICE_LOST,
		EE_DEVICE_RESTORE,

		EE_END
	};


	class GEASSENGINE_API GEventBroadcaster
	{
	public:
		GEventBroadcaster() { ; }
		~GEventBroadcaster() { ; }
	};

}
