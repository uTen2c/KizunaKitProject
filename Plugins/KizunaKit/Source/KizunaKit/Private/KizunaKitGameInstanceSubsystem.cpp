// Fill out your copyright notice in the Description page of Project Settings.


#include "KizunaKitGameInstanceSubsystem.h"

#include "Bnusio.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialParameterCollection.h"
#include "Materials/MaterialParameterCollectionInstance.h"
#include "Utils/KizunaWindowUtils.h"
#include "Framework/Application/SlateApplication.h"

namespace
{
	FString WindowDataSlotName = "WindowData";
	const TCHAR* MpcPath = TEXT("/KizunaKit/Material/MPC_VirtualMonitorLayout.MPC_VirtualMonitorLayout");
}

void UKizunaKitGameInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	if (!WindowData)
	{
		WindowData = Cast<UWindowData>(UGameplayStatics::CreateSaveGameObject(UWindowData::StaticClass()));
	}

	FBnusio::Open();

	Load();

	FSlateApplication::Get().OnPostTick().AddUObject(
		this, &UKizunaKitGameInstanceSubsystem::OnPostTick);
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

void UKizunaKitGameInstanceSubsystem::OnPostTick([[maybe_unused]] const float InDeltaTime)
{
	if (bWindowInitialized || FKizunaWindowUtils::GetHwnd() == nullptr)
	{
		return;
	}

	// 仮想マルチモニターを初期化する
	if (const auto Mpc = LoadObject<UMaterialParameterCollection>(nullptr, MpcPath))
	{
		if (const auto Instance = GetWorld()->
			GetParameterCollectionInstance(Mpc))
		{
			const auto Monitors = WindowData->VirtualMonitors;

			const auto M0 = Monitors & 0b11;
			const auto M1 = (Monitors & 0b1100) >> 2;
			const auto M2 = (Monitors & 0b110000) >> 4;

			Instance->SetScalarParameterValue(TEXT("Monitor0"), M0);
			Instance->SetScalarParameterValue(TEXT("Monitor1"), M1);
			Instance->SetScalarParameterValue(TEXT("Monitor2"), M2);
		}
	}

	// 独立したウィンドウで動かしている場合のみウィンドウをいじる
	if (GetWorld()->WorldType == EWorldType::Game)
	{
		FKizunaWindowUtils::InitGameWindow();
		FKizunaWindowUtils::SetPosAndSize(WindowData->PosX, WindowData->PosY, WindowData->Width,
		                                  WindowData->Height);
	}

	bWindowInitialized = true;
}
