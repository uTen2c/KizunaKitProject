// Fill out your copyright notice in the Description page of Project Settings.


#include "Command/WindowPosCommand.h"

#include "KizunaKitGameInstanceSubsystem.h"
#include "Utils/KizunaWindowUtils.h"

void FWindowPosCommand::OnRun(const TArray<FString>& Args, UWorld* World)
{
	if (Args.Num() != 2)
	{
		PrintErrorMessage(TEXT("不正な引数。 使い方: kizuna.WindowPos <x pos> <y pos>"));
		return;
	}

	const auto& [X, XError, XErrorMessage] = ParseInt(Args[0]);
	const auto& [Y, YError, YErrorMessage] = ParseInt(Args[1]);

	if (XError)
	{
		PrintErrorMessage(XErrorMessage);
		return;
	}

	if (YError)
	{
		PrintErrorMessage(YErrorMessage);
		return;
	}

	const auto SubSystem = World->GetGameInstance()->GetSubsystem<UKizunaKitGameInstanceSubsystem>();
	SubSystem->WindowData->PosX = X;
	SubSystem->WindowData->PosY = Y;
	SubSystem->Save();

	if (FKizunaWindowUtils::SetPos(X, Y))
	{
		PrintSuccessMessage(FString::Printf(TEXT("ウィンドウ位置を更新しました: (%d, %d)"), X, Y));
	}
	else
	{
		PrintErrorMessage(TEXT("ウィンドウ位置の更新に失敗しました"));
	}
}
