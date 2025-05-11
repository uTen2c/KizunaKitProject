// Fill out your copyright notice in the Description page of Project Settings.


#include "KizunaKitGameInstanceSubsystem.h"

#include "Bnusio.h"
#include "Kismet/GameplayStatics.h"

namespace
{
	FString WindowDataSlotName = "WindowData";
}

void UKizunaKitGameInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	if (!WindowData)
	{
		WindowData = Cast<UWindowData>(UGameplayStatics::CreateSaveGameObject(UWindowData::StaticClass()));
	}

	FBnusio::Open();
}

void UKizunaKitGameInstanceSubsystem::Deinitialize()
{
	Super::Deinitialize();

	if (FBnusio::IsConnected())
	{
		FBnusio::Close();
	}
}

bool UKizunaKitGameInstanceSubsystem::Load()
{
	if (!WindowData)
	{
		return false;
	}

	if (!UGameplayStatics::DoesSaveGameExist(WindowDataSlotName, 0))
	{
		return false;
	}

	const auto Data = Cast<UWindowData>(UGameplayStatics::LoadGameFromSlot(WindowDataSlotName, 0));
	WindowData = Data;
	return true;
}

// ReSharper disable once CppMemberFunctionMayBeConst
bool UKizunaKitGameInstanceSubsystem::Save()
{
	if (!WindowData)
	{
		return false;
	}

	return UGameplayStatics::SaveGameToSlot(WindowData, WindowDataSlotName, 0);
}
