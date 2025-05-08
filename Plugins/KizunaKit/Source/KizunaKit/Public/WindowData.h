// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "WindowData.generated.h"

/**
 * 
 */
UCLASS()
class NOVA_API UWindowData : public USaveGame
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
};
