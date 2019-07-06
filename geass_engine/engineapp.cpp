#include "pch.h"
#include "engineapp.h"
#include "gdevice.h"
#include "gscenemanager.h"

Geass::GEngineApplication::GEngineApplication() :
	bActive(false),
	Device(nullptr),
	SceneManager(nullptr)
{
}

Geass::GEngineApplication::~GEngineApplication()
{
}

bool Geass::GEngineApplication::Create()
{
	/*
	Device = new GDevice();
	SceneManager = new GSceneManager();
	if (!SceneManager || !Device)
	{
		return false;
	}

	bool bSuccess = SceneManager->Create(Device);
	Activate(bSuccess);
	return bSuccess;
	*/
	return false;
}

void Geass::GEngineApplication::Destroy()
{
	SAFE_DELETE(Device);
	SAFE_DELETE(SceneManager);
}

void Geass::GEngineApplication::Update()
{
}

void Geass::GEngineApplication::Render()
{
}

std::string Geass::GEngineApplication::GetName()
{
	return std::string();
}

void Geass::GEngineApplication::Activate(bool bValue)
{
	bActive = bValue;
}
