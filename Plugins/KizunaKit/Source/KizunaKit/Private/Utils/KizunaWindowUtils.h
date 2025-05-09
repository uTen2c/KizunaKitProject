// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Windows.h>

/**
 * 
 */
class KIZUNAKIT_API FKizunaWindowUtils
{
	FKizunaWindowUtils() = default;

public:
	~FKizunaWindowUtils() = default;

	static HWND GetHwnd();
	static bool InitGameWindow();
	static bool SetPos(const int X, const int Y);
	static bool SetSize(const int Width, const int Height);
	static bool SetPosAndSize(const int X, const int Y, const int Width, const int Height);
};
