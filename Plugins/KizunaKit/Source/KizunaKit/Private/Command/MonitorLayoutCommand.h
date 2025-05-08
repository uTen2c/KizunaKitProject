// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KizunaCommandBase.h"

/**
 * 
 */
class FMonitorLayoutCommand final : public FKizunaCommandBase
{
public:
	static void OnRun(const TArray<FString>& Args, UWorld* World);
};
