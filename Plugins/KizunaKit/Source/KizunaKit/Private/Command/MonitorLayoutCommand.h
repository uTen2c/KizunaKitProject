// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KizunaCommandBase.h"

/**
 * 
 */
class FMonitorLayoutCommand final : public FKizunaCommandBase
{
	inline static const TCHAR* MpcPath = TEXT("/KizunaKit/Material/MPC_VirtualMonitorLayout.MPC_VirtualMonitorLayout");

public:
	static void OnRun(const TArray<FString>& Args, UWorld* World);
};
