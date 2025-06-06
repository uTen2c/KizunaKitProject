// Fill out your copyright notice in the Description page of Project Settings.


#include "Command/MonitorLayoutCommand.h"

#include "KizunaKitGameInstanceSubsystem.h"
#include "Materials/MaterialParameterCollection.h"
#include "Materials/MaterialParameterCollectionInstance.h"

// ReSharper disable once CppParameterMayBeConstPtrOrRef
void FMonitorLayoutCommand::OnRun(const TArray<FString>& Args, UWorld* World)
{
	if (Args.Num() != 3)
	{
		PrintErrorMessage(TEXT("不正な引数。 使い方: kizuna.MonitorLayout <monitor 1> <monitor 2> <monitor 3>"));
		return;
	}

	const auto& Monitor0Result = ParseInt(Args[0], 0, 2);
	const auto& Monitor1Result = ParseInt(Args[1], 0, 2);
	const auto& Monitor2Result = ParseInt(Args[2], 0, 2);

	if (PrintErrorIfHasError(Monitor0Result)
		|| PrintErrorIfHasError(Monitor1Result)
		|| PrintErrorIfHasError(Monitor2Result)
	)
	{
		return;
	}

	const auto Mpc = LoadObject<UMaterialParameterCollection>(nullptr, MpcPath);
	if (!Mpc)
	{
		PrintErrorMessage(FString::Printf(TEXT("オブジェクトを読み込めませんでした: %s"), MpcPath));
		return;
	}

	const auto Instance = World->GetParameterCollectionInstance(Mpc);
	if (!Instance)
	{
		PrintErrorMessage(TEXT("インスタンスの取得に失敗しました"));
		return;
	}

	const auto SubSystem = World->GetGameInstance()->GetSubsystem<UKizunaKitGameInstanceSubsystem>();
	SubSystem->WindowData->VirtualMonitors = Monitor0Result.Value
		| Monitor1Result.Value << 2
		| Monitor2Result.Value << 4;
	SubSystem->Save();

	Instance->SetScalarParameterValue(TEXT("Monitor0"), Monitor0Result.Value);
	Instance->SetScalarParameterValue(TEXT("Monitor1"), Monitor1Result.Value);
	Instance->SetScalarParameterValue(TEXT("Monitor2"), Monitor2Result.Value);

	PrintSuccessMessage(FString::Printf(
			TEXT("モニターレイアウトを更新しました: (%d, %d, %d)"),
			Monitor0Result.Value, Monitor1Result.Value, Monitor2Result.Value)
	);
}
