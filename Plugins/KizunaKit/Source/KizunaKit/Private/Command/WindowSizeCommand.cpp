// Fill out your copyright notice in the Description page of Project Settings.


#include "Command/WindowSizeCommand.h"

#include "KizunaKitGameInstanceSubsystem.h"
#include "Utils/KizunaWindowUtils.h"

void FWindowSizeCommand::OnRun(const TArray<FString>& Args, UWorld* World)
{
	if (Args.Num() != 2)
	{
		PrintErrorMessage(TEXT("不正な引数。 使い方: kizuna.WindowSize <width> <height>"));
		return;
	}

	const auto& [Width, WidthError, WidthErrorMessage] = ParseInt(Args[0]);
	const auto& [Height, HeightError, HeightErrorMessage] = ParseInt(Args[1]);

	if (WidthError)
	{
		PrintErrorMessage(WidthErrorMessage);
		return;
	}

	if (HeightError)
	{
		PrintErrorMessage(HeightErrorMessage);
		return;
	}

	const auto SubSystem = World->GetGameInstance()->GetSubsystem<UKizunaKitGameInstanceSubsystem>();
	SubSystem->WindowData->Width = Width;
	SubSystem->WindowData->Height = Height;
	SubSystem->Save();

	if (FKizunaWindowUtils::SetSize(Width, Height))
	{
		PrintSuccessMessage(FString::Printf(TEXT("ウィンドウサイズを更新しました: (%d, %d)"), Width, Height));
	}
	else
	{
		PrintErrorMessage(TEXT("ウィンドウサイズの更新に失敗しました"));
	}
}
