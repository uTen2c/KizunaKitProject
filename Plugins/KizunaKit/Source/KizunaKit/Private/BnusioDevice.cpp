// Fill out your copyright notice in the Description page of Project Settings.


#include "BnusioDevice.h"
#include <Windows.h>

#include "Bnusio.h"

FBnusioDevice::FBnusioDevice(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler)
	: MessageHandler(InMessageHandler)
{
}

FBnusioDevice::~FBnusioDevice()
{
}

void FBnusioDevice::Tick(float DeltaTime)
{
}

void FBnusioDevice::SendControllerEvents()
{
	FBnusio::Communication(0);

	FPlatformUserId UserId = FGenericPlatformMisc::GetPlatformUserForUserIndex(0);
	FInputDeviceId DeviceId = INPUTDEVICEID_NONE;
	IPlatformInputDeviceMapper::Get().RemapControllerIdToPlatformUserAndDevice(0, UserId, DeviceId);
}

void FBnusioDevice::SetMessageHandler(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler)
{
	MessageHandler = InMessageHandler;
}

bool FBnusioDevice::Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar)
{
	return false;
}

void FBnusioDevice::SetChannelValue(int32 ControllerId, FForceFeedbackChannelType ChannelType, float Value)
{
}

void FBnusioDevice::SetChannelValues(int32 ControllerId, const FForceFeedbackValues& values)
{
}
