// Copyright Epic Games, Inc. All Rights Reserved.

#include "KizunaKit.h"

#include "BnusioDevice.h"
#include "BnusioInputKeys.h"

#include "InputCoreTypes.h"
#include "Command/CalibrationCommand.h"
#include "Command/MonitorLayoutCommand.h"
#include "Command/WindowPosCommand.h"
#include "Command/WindowSizeCommand.h"

class FKizunaKitModule final : public IKizunaKitModule
{
public:
	virtual TSharedPtr<IInputDevice> CreateInputDevice(
		const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler) override;

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_MODULE(FKizunaKitModule, KizunaKit)

TSharedPtr<IInputDevice> FKizunaKitModule::CreateInputDevice(
	const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler
)
{
	return MakeShareable(new FBnusioDevice(InMessageHandler));
}

void FKizunaKitModule::StartupModule()
{
	IKizunaKitModule::StartupModule();

	IModularFeatures::Get().RegisterModularFeature(GetModularFeatureName(), this);

	FBnusioInputKeys::Init();

	IConsoleManager::Get().RegisterConsoleCommand(
		TEXT("kizuna.MonitorLayout"),
		TEXT("モニターレイアウトを設定する"),
		FConsoleCommandWithWorldAndArgsDelegate::CreateStatic(FMonitorLayoutCommand::OnRun)
	);

	IConsoleManager::Get().RegisterConsoleCommand(
		TEXT("kizuna.WindowPos"),
		TEXT("ウィンドウの位置を設定する"),
		FConsoleCommandWithWorldAndArgsDelegate::CreateStatic(FWindowPosCommand::OnRun)
	);

	IConsoleManager::Get().RegisterConsoleCommand(
		TEXT("kizuna.WindowSize"),
		TEXT("ウィンドウのサイズを設定する"),
		FConsoleCommandWithWorldAndArgsDelegate::CreateStatic(FWindowSizeCommand::OnRun)
	);

	IConsoleManager::Get().RegisterConsoleCommand(
		TEXT("kizuna.Calibration"),
		TEXT("コントローラーのキャリブレーションを行う"),
		FConsoleCommandWithWorldAndArgsDelegate::CreateStatic(FCalibrationCommand::OnRun)
	);

	UE_LOG(LogTemp, Display, TEXT("KizunaKit started"));
}

void FKizunaKitModule::ShutdownModule()
{
	UE_LOG(LogTemp, Display, TEXT("KizunaKit shutdown"));

	IModularFeatures::Get().UnregisterModularFeature(GetModularFeatureName(), this);
}
