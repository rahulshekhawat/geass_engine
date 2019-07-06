#pragma once

#include "ge_lib.h"

namespace Geass
{
	class GDevice;

	class GEASSENGINE_API GSceneManager
	{
	public:
		GSceneManager();
		virtual ~GSceneManager();

		virtual bool Create(GDevice* Device);

	};
}

