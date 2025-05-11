// Fill out your copyright notice in the Description page of Project Settings.


#include "CalibrationCommand.h"

#include "BnusioDevice.h"
#include "KizunaKitGameInstanceSubsystem.h"
#include "Command/WindowSizeCommand.h"

#include "Utils/KizunaWindowUtils.h"

void FCalibrationCommand::OnRun(const TArray<FString>& Args, UWorld* World)
{
	if (Args.Num() != 1)
	{
		PrintErrorMessage(TEXT("不正な引数。 使い方: kizuna.Calibration <mode: 0|1>"));
		return;
	}

	const auto& ModeResult = ParseInt(Args[0], 0, 1);

	if (PrintErrorIfHasError(ModeResult))
	{
		return;
	}

	switch (ModeResult.Value)
	{
	case 0:
		{
			FBnusioDevice::CalibrationMode = ECalibrationMode::Idle;
			break;
		}
	case 1:
		{
			if (FBnusioDevice::CalibrationMode == ECalibrationMode::Active)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("アクティブ状態のキャリブレーションを終了しました"));
				const auto SubSystem = GEngine->GameViewport->GetGameInstance()->GetSubsystem<
					UKizunaKitGameInstanceSubsystem>();
				SubSystem->Save();
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("アクティブ状態のキャリブレーション中..."));
				FBnusioDevice::CalibrationMode = ECalibrationMode::Active;
			}
			break;
		}
	default:
		break;
	}
}
