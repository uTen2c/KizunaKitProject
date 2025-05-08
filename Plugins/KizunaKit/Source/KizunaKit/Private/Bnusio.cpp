// Fill out your copyright notice in the Description page of Project Settings.


#include "Bnusio.h"

extern "C" {
typedef int (*BnusioOpenPtr)();

typedef int (*BnusioClosePtr)();

typedef bool (*BnusioIsConnectedPtr)();

typedef int (*BnusioCommunicationPtr)(int DelayMillis);

typedef unsigned short (*BnusioGetAnalogInPtr)(char Channel);

typedef unsigned int (*BnusioGetSwInPtr)();
}

namespace
{
	const FString DllName = "bnusio.dll";
	const FString OpenFnName = "bnusio_Open";
	const FString CloseFnName = "bnusio_Close";
	const FString CommunicationFnName = "bnusio_Communication";
	const FString IsConnectedFnName = "bnusio_IsConnected";
	const FString GetAnalogInFnName = "bnusio_GetAnalogIn";
	const FString GetSwInFnName = "bnusio_GetSwIn";
	void* DllPtr = nullptr;

	void* GetHandle()
	{
		if (DllPtr != nullptr)
		{
			return DllPtr;
		}
		DllPtr = FPlatformProcess::GetDllHandle(*DllName);
		return DllPtr;
	}
}

FBnusio::FBnusio()
{
}

FBnusio::~FBnusio()
{
}

int FBnusio::Open()
{
	const auto Func = static_cast<BnusioOpenPtr>(FPlatformProcess::GetDllExport(GetHandle(), *OpenFnName));
	return (*Func)();
}

int FBnusio::Close()
{
	const auto Func = static_cast<BnusioClosePtr>(FPlatformProcess::GetDllExport(GetHandle(), *CloseFnName));
	return (*Func)();
}

int FBnusio::Communication(const int DelayMs)
{
	const auto Func = static_cast<BnusioCommunicationPtr>(FPlatformProcess::GetDllExport(
		GetHandle(), *CommunicationFnName));
	return (*Func)(DelayMs);
}

bool FBnusio::IsConnected()
{
	const auto Func = static_cast<BnusioIsConnectedPtr>(
		FPlatformProcess::GetDllExport(GetHandle(), *IsConnectedFnName));
	return (*Func)();
}

unsigned short FBnusio::GetAnalogIn(const char Channel)
{
	const auto Func = static_cast<BnusioGetAnalogInPtr>(
		FPlatformProcess::GetDllExport(GetHandle(), *GetAnalogInFnName));
	return (*Func)(Channel);
}

unsigned int FBnusio::GetSwIn()
{
	const auto Func = static_cast<BnusioGetSwInPtr>(
		FPlatformProcess::GetDllExport(GetHandle(), *GetSwInFnName));
	return (*Func)();
}

bool FBnusio::GetSwIn(const unsigned int Switch)
{
	if (!IsConnected())
	{
		return false;
	}
	// 何故かGetSwInで取得されるビットセットが一部反転しているので、補正する
	const auto Corrected = GetSwIn() ^ 0x0F0F0000;
	return (Corrected & Switch) != 0;
}
