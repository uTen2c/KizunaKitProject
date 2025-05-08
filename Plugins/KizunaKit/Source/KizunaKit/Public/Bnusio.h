// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class KIZUNAKIT_API FBnusio
{
	FBnusio();
	~FBnusio();

public:
	static constexpr int RetOk = 0;
	static constexpr int RetError = -1;
	static constexpr int RetErrorIo = -5;
	static constexpr int RetErrorBusy = -16;
	static constexpr int RetErrorExist = -17;
	static constexpr int RetErrorNoDev = -19;
	static constexpr int RetErrorInvalid = -22;
	static constexpr int RetErrorNotConnected = -126;
	static constexpr int RetErrorTimeout = -138;

	// 左スティック
	static constexpr unsigned int SwLeftButtonLeft = 0x80000;
	static constexpr unsigned int SwLeftButtonCenter = 0x4000000;
	static constexpr unsigned int SwLeftButtonRight = 0x40000;
	static constexpr unsigned int SwLeftTrigger = 0x8000000;
	//右スティック
	static constexpr unsigned int SwRightButtonLeft = 0x20000;
	static constexpr unsigned int SwRightButtonCenter = 0x1000000;
	static constexpr unsigned int SwRightButtonRight = 0x10000;
	static constexpr unsigned int SwRightTrigger = 0x2000000;
	// その他
	static constexpr unsigned int SwTest = 0x80;
	static constexpr unsigned int SwEnter = 0x200;
	static constexpr unsigned int SwSelectDown = 0x1000;
	static constexpr unsigned int SwSelectUp = 0x2000;
	static constexpr unsigned int SwService = 0x4000;
	static constexpr unsigned int SwStart = 0x200000;
	static constexpr unsigned int SwVolumeDown = 0x400000;
	static constexpr unsigned int SwVolumeUp = 0x800000;

	// GetAnalogInのチャンネル
	static constexpr char ChLeftX = 0;
	static constexpr char ChLeftY = 1;
	static constexpr char ChRightX = 2;
	static constexpr char ChRightY = 3;
	static constexpr char ChLeftPedal = 4;
	static constexpr char ChRightPedal = 5;

	static int Open();
	static int Close();
	static int Communication(int DelayMs);
	static bool IsConnected();
	static unsigned short GetAnalogIn(char Channel);
	static unsigned int GetSwIn();

	/**
	  * 特定のスイッチが押されているかを判定する
	  * @param Switch スイッチのフラグ
	  * @return 
	  */
	static bool GetSwIn(unsigned int Switch);
};
