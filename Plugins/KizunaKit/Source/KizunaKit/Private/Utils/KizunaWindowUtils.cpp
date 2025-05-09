// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/KizunaWindowUtils.h"

#include <Windows.h>

HWND FKizunaWindowUtils::GetHwnd()
{
	if (const auto Handle = GEngine->GameViewport->GetWindow()->GetNativeWindow()->GetOSWindowHandle(); Handle !=
		nullptr)
	{
		return static_cast<HWND>(Handle);
	}
	return nullptr;
}

bool FKizunaWindowUtils::InitGameWindow()
{
	if (const auto Hwnd = GetHwnd())
	{
		auto Style = GetWindowLongA(Hwnd, GWL_STYLE);
		Style &= ~WS_OVERLAPPEDWINDOW;
		SetWindowLongA(Hwnd, GWL_STYLE, Style);
		SetWindowPos(Hwnd, nullptr, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
		return true;
	}
	return false;
}

bool FKizunaWindowUtils::SetPos(const int X, const int Y)
{
	if (const auto Hwnd = GetHwnd())
	{
		return SetWindowPos(Hwnd, nullptr, X, Y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
	}
	return false;
}

bool FKizunaWindowUtils::SetSize(const int Width, const int Height)
{
	if (const auto Hwnd = GetHwnd())
	{
		return SetWindowPos(Hwnd, nullptr, 0, 0, Width, Height, SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED);
	}
	return false;
}

bool FKizunaWindowUtils::SetPosAndSize(const int X, const int Y, const int Width, const int Height)
{
	if (const auto Hwnd = GetHwnd())
	{
		return SetWindowPos(Hwnd, nullptr, X, Y, Width, Height, SWP_NOZORDER | SWP_FRAMECHANGED);
	}
	return false;
}
