// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "WindowData.generated.h"

USTRUCT()
struct KIZUNAKIT_API FStickSettings
{
	GENERATED_BODY()

	float Idle;
	float Min;
	float Max;
};

USTRUCT()
struct KIZUNAKIT_API FPedalSettings
{
	GENERATED_BODY()

	float Min;
	float Max;
};

/**
 * 
 */
UCLASS()
class KIZUNAKIT_API UWindowData : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY()
	int32 PosX;

	UPROPERTY()
	int32 PosY;

	UPROPERTY()
	int32 Width = 1280;

	UPROPERTY()
	int32 Height = 720;

	UPROPERTY()
	int32 VirtualMonitors = 0b100100; // monitor2 | monitor1 | monitor0

	UPROPERTY()
	FStickSettings LeftStickX = {32767, 65535, 0};
	
	UPROPERTY()
	FStickSettings LeftStickY = {32767, 65535, 0};

	UPROPERTY()
	FStickSettings RightStickX = {32767, 65535, 0};

	UPROPERTY()
	FStickSettings RightStickY = {32767, 65535, 0};

	UPROPERTY()
	FPedalSettings LeftPedal = {0, 65535};

	UPROPERTY()
	FPedalSettings RightPedal = {0, 65535};
};
