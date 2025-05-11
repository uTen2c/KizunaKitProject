// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IInputDevice.h"

enum class ECalibrationMode
{
	None, // なにもしない
	Idle, // アイドル状態
	Active // 動かしている状態
};

/**
 * 
 */
class KIZUNAKIT_API FBnusioDevice final : public IInputDevice
{
public:
	inline static float IdleCalibrationSeconds = 0;
	inline static std::vector<unsigned short> IdleLeftXVec = {};
	inline static std::vector<unsigned short> IdleLeftYVec = {};
	inline static std::vector<unsigned short> IdleRightXVec = {};
	inline static std::vector<unsigned short> IdleRightYVec = {};
	inline static ECalibrationMode CalibrationMode = ECalibrationMode::None;
	inline static ECalibrationMode LastCalibrationMode = ECalibrationMode::None;

	explicit FBnusioDevice(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler);
	virtual ~FBnusioDevice() override;

	virtual void Tick(float DeltaTime) override;
	virtual void SendControllerEvents() override;
	virtual void SetMessageHandler(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler) override;
	virtual bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;
	virtual void SetChannelValue(int32 ControllerId, FForceFeedbackChannelType ChannelType, float Value) override;
	virtual void SetChannelValues(int32 ControllerId, const FForceFeedbackValues& Values) override;

private:
	TSharedRef<FGenericApplicationMessageHandler> MessageHandler;

	void UpdateButtons() const;
	void UpdateAnalogs() const;

	void UpdateButton(const unsigned int& Switch, const FKey& Key) const;
	static void UpdateCalibration(const float& DeltaTime);
	static void UpdateCalibrationIdle(const float& DeltaTime);
	static void UpdateCalibrationActive(const float& DeltaTime);
};
