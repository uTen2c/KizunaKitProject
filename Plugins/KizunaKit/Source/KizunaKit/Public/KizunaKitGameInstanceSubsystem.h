// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WindowData.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "KizunaKitGameInstanceSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class KIZUNAKIT_API UKizunaKitGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	inline static const FString WindowDataSlotName = "WindowData";
	inline static const TCHAR* MpcPath = TEXT("/KizunaKit/Material/MPC_VirtualMonitorLayout.MPC_VirtualMonitorLayout");

public:
	UPROPERTY()
	UWindowData* WindowData = nullptr;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	bool Load();
	bool Save();

	void OnPostTick(float InDeltaTime);

private:
	bool bWindowInitialized = false;
};
