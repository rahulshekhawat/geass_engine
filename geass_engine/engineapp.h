#pragma once

#include "pch.h"
#include "glib.h"

namespace Geass
{
	class GDevice;
	class GSceneManager;

	class GEASS_API GEngineApplication
	{
	public:
		GEngineApplication();
		virtual ~GEngineApplication();

		virtual bool Create();
		virtual void Destroy();
		virtual void Update();
		virtual void Render();

		virtual std::string GetName();
		virtual void Activate(bool bValue);
		virtual GDevice* GetDevice() { return Device; }
		virtual GSceneManager* GetSceneManager() { return SceneManager; }

	protected:

		bool bActive;
		GDevice* Device;
		GSceneManager* SceneManager;

	};
}

