#include "PresetCommand.h"

#include "KizunaKitGameInstanceSubsystem.h"
#include "Utils/KizunaWindowUtils.h"
#include "Materials/MaterialParameterCollection.h"
#include "Materials/MaterialParameterCollectionInstance.h"

void FPresetCommand::OnRun([[maybe_unused]] const TArray<FString>& Args, UWorld* World)
{
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
	SubSystem->WindowData->PosX = X;
	SubSystem->WindowData->PosY = Y;
	SubSystem->WindowData->Width = Width;
	SubSystem->WindowData->Height = Height;
	SubSystem->WindowData->VirtualMonitors = Monitor0 | Monitor1 << 2 | Monitor2 << 4;
	SubSystem->Save();

	FKizunaWindowUtils::SetPos(X, Y);
	FKizunaWindowUtils::SetSize(Width, Height);

	Instance->SetScalarParameterValue(TEXT("Monitor0"), Monitor0);
	Instance->SetScalarParameterValue(TEXT("Monitor1"), Monitor1);
	Instance->SetScalarParameterValue(TEXT("Monitor2"), Monitor2);
}
