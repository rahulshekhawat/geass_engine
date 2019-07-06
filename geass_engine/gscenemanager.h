#pragma once

#include "glib.h"

namespace Geass
{
	class GDevice;

	class GEASS_API GSceneManager
	{
	public:
		GSceneManager();
		virtual ~GSceneManager();

		virtual bool Create(GDevice* Device);

	};
}

