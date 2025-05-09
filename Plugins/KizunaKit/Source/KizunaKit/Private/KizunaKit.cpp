// Copyright Epic Games, Inc. All Rights Reserved.

#include "KizunaKit.h"

#include "Bnusio.h"
#include "BnusioDevice.h"

#include "InputCoreTypes.h"
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
	UE_LOG(LogTemp, Display, TEXT("KizunaKit started"));

	IModularFeatures::Get().RegisterModularFeature(GetModularFeatureName(), this);

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
}

void FKizunaKitModule::ShutdownModule()
{
	UE_LOG(LogTemp, Display, TEXT("KizunaKit shutdown"));

	IModularFeatures::Get().UnregisterModularFeature(GetModularFeatureName(), this);
}
