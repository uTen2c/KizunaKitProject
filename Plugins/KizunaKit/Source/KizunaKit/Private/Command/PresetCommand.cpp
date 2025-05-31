#include "PresetCommand.h"

#include "KizunaKitGameInstanceSubsystem.h"
#include "Utils/KizunaWindowUtils.h"
#include "Materials/MaterialParameterCollection.h"
#include "Materials/MaterialParameterCollectionInstance.h"

static constexpr auto X = -2160;
static constexpr auto Y = 0;
static constexpr auto Width = 3240;
static constexpr auto Height = 1920;
static constexpr auto Monitor0 = 1;
static constexpr auto Monitor1 = 0;
static constexpr auto Monitor2 = 2;
static constexpr auto MpcPath = TEXT("/KizunaKit/Material/MPC_VirtualMonitorLayout.MPC_VirtualMonitorLayout");

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
