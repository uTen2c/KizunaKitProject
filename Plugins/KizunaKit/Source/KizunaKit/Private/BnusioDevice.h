// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IInputDevice.h"

/**
 * 
 */
class KIZUNAKIT_API FBnusioDevice final : public IInputDevice
{
public:
	explicit FBnusioDevice(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler);
	virtual ~FBnusioDevice() override;
	
	virtual void Tick(float DeltaTime) override;
	virtual void SendControllerEvents() override;
	virtual void SetMessageHandler(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler) override;
	virtual bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;
	virtual void SetChannelValue(int32 ControllerId, FForceFeedbackChannelType ChannelType, float Value) override;
	virtual void SetChannelValues(int32 ControllerId, const FForceFeedbackValues& values) override;
	
private:
	TSharedRef<FGenericApplicationMessageHandler> MessageHandler;
};
