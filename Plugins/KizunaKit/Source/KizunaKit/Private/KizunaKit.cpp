// Copyright Epic Games, Inc. All Rights Reserved.

#include "KizunaKit.h"

#include "Bnusio.h"
#include "BnusioDevice.h"

#include "InputCoreTypes.h"

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

	FBnusio::Open();

	IModularFeatures::Get().RegisterModularFeature(GetModularFeatureName(), this);
}

void FKizunaKitModule::ShutdownModule()
{
	UE_LOG(LogTemp, Display, TEXT("KizunaKit shutdown"));

	if (FBnusio::IsConnected())
	{
		FBnusio::Close();
	}

	IModularFeatures::Get().UnregisterModularFeature(GetModularFeatureName(), this);
}
