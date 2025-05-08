// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "IInputDeviceModule.h"
#include "Modules/ModuleManager.h"

class IKizunaKitModule : public IInputDeviceModule
{
public:
	static IKizunaKitModule& Get()
	{
		return FModuleManager::LoadModuleChecked<IKizunaKitModule>("KizunaKit");
	}

	static bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("KizunaKit");
	}
};
