// Fill out your copyright notice in the Description page of Project Settings.


#include "BnusioDevice.h"

#include <numeric>

#include "Bnusio.h"
#include "BnusioInputKeys.h"
#include "KizunaKitGameInstanceSubsystem.h"

namespace
{
	unsigned int LastSwIn;

	bool IsPressed(const unsigned int& Switch)
	{
		const auto SwIn = FBnusio::GetSwIn();
		return FBnusio::GetSwIn(Switch) && (SwIn & Switch) != (LastSwIn & Switch);
	}

	bool IsReleased(const unsigned int& Switch)
	{
		const auto SwIn = FBnusio::GetSwIn();
		return !FBnusio::GetSwIn(Switch) && (SwIn & Switch) != (LastSwIn & Switch);
	}

	float Avg(const std::vector<unsigned short>& Vector)
	{
		const auto Total = std::accumulate(Vector.begin(), Vector.end(), 0);
		return static_cast<float>(Total) / Vector.size();
	}

	float Clamp(const float Value, const float Min, const float Max)
	{
		if (Value < Min)
		{
			return Min;
		}
		if (Value > Max)
		{
			return Max;
		}
		return Value;
	}

	float NormalizeAnalogValue(const float Value, const FStickSettings& Settings)
	{
		const auto V = Value < Settings.Idle
			               ? (1.0f - (Value - Settings.Min) / (Settings.Idle - Settings.Min)) * -1
			               : (Value - Settings.Idle) / (Settings.Max - Settings.Idle);
		return Clamp(V, -1, 1);
	}

	float NormalizeAnalogValue(const float Value, const FPedalSettings& Settings)
	{
		const auto Delta = (Value - Settings.Min) / (Settings.Max - Settings.Min);
		return Clamp(Delta, 0, 1);
	}
}

FBnusioDevice::FBnusioDevice(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler)
	: MessageHandler(InMessageHandler)
{
}

FBnusioDevice::~FBnusioDevice()
{
}

void FBnusioDevice::Tick(const float DeltaTime)
{
	UpdateCalibration(DeltaTime);
}

void FBnusioDevice::SendControllerEvents()
{
	const auto Viewport = GEngine->GameViewport;
	if (!Viewport)
	{
		return;
	}

	// エディター上では入力を処理しない
	if (
		const auto WorldType = Viewport->GetWorld()->WorldType;
		WorldType == EWorldType::Editor || WorldType == EWorldType::EditorPreview)
	{
		return;
	}

	FBnusio::Communication(0);

	// キャリブレーション中は入力を処理しない
	if (CalibrationMode != ECalibrationMode::None)
	{
		return;
	}

	if (!FBnusio::IsConnected())
	{
		return;
	}

	UpdateButtons();
	UpdateAnalogs();
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

void FBnusioDevice::SetChannelValues(int32 ControllerId, const FForceFeedbackValues& Values)
{
}

void FBnusioDevice::UpdateButtons() const
{
	UpdateButton(FBnusio::SwLeftButtonLeft, FBnusioInputKeys::Left_Stick_Left);
	UpdateButton(FBnusio::SwLeftButtonCenter, FBnusioInputKeys::Left_Stick_Center);
	UpdateButton(FBnusio::SwLeftButtonRight, FBnusioInputKeys::Left_Stick_Right);
	UpdateButton(FBnusio::SwLeftTrigger, FBnusioInputKeys::Left_Stick_Trigger);

	UpdateButton(FBnusio::SwRightButtonLeft, FBnusioInputKeys::Right_Stick_Left);
	UpdateButton(FBnusio::SwRightButtonCenter, FBnusioInputKeys::Right_Stick_Center);
	UpdateButton(FBnusio::SwRightButtonRight, FBnusioInputKeys::Right_Stick_Right);
	UpdateButton(FBnusio::SwRightTrigger, FBnusioInputKeys::Right_Stick_Trigger);

	UpdateButton(FBnusio::SwTest, FBnusioInputKeys::Test);
	UpdateButton(FBnusio::SwEnter, FBnusioInputKeys::Enter);
	UpdateButton(FBnusio::SwSelectDown, FBnusioInputKeys::Select_Down);
	UpdateButton(FBnusio::SwSelectUp, FBnusioInputKeys::Select_Up);
	UpdateButton(FBnusio::SwService, FBnusioInputKeys::Service);
	UpdateButton(FBnusio::SwStart, FBnusioInputKeys::Start);
	UpdateButton(FBnusio::SwVolumeDown, FBnusioInputKeys::Volume_Down);
	UpdateButton(FBnusio::SwVolumeUp, FBnusioInputKeys::Volume_Up);

	LastSwIn = FBnusio::GetSwIn();
}

void FBnusioDevice::UpdateAnalogs() const
{
	const auto Viewport = GEngine->GameViewport;
	if (!Viewport)
	{
		return;
	}

	FPlatformUserId UserId = FGenericPlatformMisc::GetPlatformUserForUserIndex(0);
	FInputDeviceId DeviceId = INPUTDEVICEID_NONE;
	IPlatformInputDeviceMapper::Get().RemapControllerIdToPlatformUserAndDevice(0, UserId, DeviceId);

	const auto SubSystem = Viewport->GetGameInstance()->GetSubsystem<UKizunaKitGameInstanceSubsystem>();

	MessageHandler->OnControllerAnalog(
		FBnusioInputKeys::Left_Stick_X.GetFName(),
		UserId,
		DeviceId,
		NormalizeAnalogValue(FBnusio::GetAnalogIn(FBnusio::ChLeftX), SubSystem->WindowData->LeftStickX)
	);
	MessageHandler->OnControllerAnalog(
		FBnusioInputKeys::Left_Stick_Y.GetFName(),
		UserId,
		DeviceId,
		NormalizeAnalogValue(FBnusio::GetAnalogIn(FBnusio::ChLeftY), SubSystem->WindowData->LeftStickY)
	);
	MessageHandler->OnControllerAnalog(
		FBnusioInputKeys::Right_Stick_X.GetFName(),
		UserId,
		DeviceId,
		NormalizeAnalogValue(FBnusio::GetAnalogIn(FBnusio::ChRightX), SubSystem->WindowData->RightStickX)
	);
	MessageHandler->OnControllerAnalog(
		FBnusioInputKeys::Right_Stick_Y.GetFName(),
		UserId,
		DeviceId,
		NormalizeAnalogValue(FBnusio::GetAnalogIn(FBnusio::ChRightY), SubSystem->WindowData->RightStickY)
	);
	MessageHandler->OnControllerAnalog(
		FBnusioInputKeys::Left_Pedal.GetFName(),
		UserId,
		DeviceId,
		NormalizeAnalogValue(FBnusio::GetAnalogIn(FBnusio::ChLeftPedal), SubSystem->WindowData->LeftPedal)
	);
	MessageHandler->OnControllerAnalog(
		FBnusioInputKeys::Right_Pedal.GetFName(),
		UserId,
		DeviceId,
		NormalizeAnalogValue(FBnusio::GetAnalogIn(FBnusio::ChRightPedal), SubSystem->WindowData->RightPedal)
	);
}

void FBnusioDevice::UpdateButton(const unsigned int& Switch, const FKey& Key) const
{
	FPlatformUserId UserId = FGenericPlatformMisc::GetPlatformUserForUserIndex(0);
	FInputDeviceId DeviceId = INPUTDEVICEID_NONE;
	IPlatformInputDeviceMapper::Get().RemapControllerIdToPlatformUserAndDevice(0, UserId, DeviceId);

	if (IsPressed(Switch))
	{
		MessageHandler->OnControllerButtonPressed(Key.GetFName(), UserId, DeviceId, false);
	}
	else if (IsReleased(Switch))
	{
		MessageHandler->OnControllerButtonReleased(Key.GetFName(), UserId, DeviceId, false);
	}
}

void FBnusioDevice::UpdateCalibration(const float& DeltaTime)
{
	if (CalibrationMode == ECalibrationMode::Idle)
	{
		UpdateCalibrationIdle(DeltaTime);
	}

	if (CalibrationMode == ECalibrationMode::Active)
	{
		UpdateCalibrationActive(DeltaTime);
	}

	LastCalibrationMode = CalibrationMode;
}

void FBnusioDevice::UpdateCalibrationIdle(const float& DeltaTime)
{
	if (LastCalibrationMode != ECalibrationMode::Idle)
	{
		IdleCalibrationSeconds = 0;
		IdleLeftXVec.clear();
		IdleLeftYVec.clear();
		IdleRightXVec.clear();
		IdleRightYVec.clear();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("アイドル状態のキャリブレーション中..."));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("スティックやペダルに触らないでください"));
	}

	if (IdleCalibrationSeconds > 5)
	{
		const auto SubSystem = GEngine->GameViewport->GetGameInstance()->GetSubsystem<
			UKizunaKitGameInstanceSubsystem>();
		SubSystem->WindowData->LeftStickX.Idle = Avg(IdleLeftXVec);
		SubSystem->WindowData->LeftStickY.Idle = Avg(IdleLeftYVec);
		SubSystem->WindowData->RightStickX.Idle = Avg(IdleRightXVec);
		SubSystem->WindowData->RightStickY.Idle = Avg(IdleRightYVec);
		SubSystem->Save();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("アイドル状態のキャリブレーションを完了しました"));
		CalibrationMode = ECalibrationMode::None;
		return;
	}

	const auto LeftX = FBnusio::GetAnalogIn(FBnusio::ChLeftX);
	const auto LeftY = FBnusio::GetAnalogIn(FBnusio::ChLeftY);
	const auto RightX = FBnusio::GetAnalogIn(FBnusio::ChRightX);
	const auto RightY = FBnusio::GetAnalogIn(FBnusio::ChRightY);

	if (IdleCalibrationSeconds > 2)
	{
		IdleLeftXVec.emplace_back(LeftX);
		IdleLeftYVec.emplace_back(LeftY);
		IdleRightXVec.emplace_back(RightX);
		IdleRightYVec.emplace_back(RightY);
	}

	GEngine->AddOnScreenDebugMessage(1000, 1.f, FColor::Cyan, FString::Printf(TEXT("Left X: %d"), LeftX));
	GEngine->AddOnScreenDebugMessage(1001, 1.f, FColor::Cyan, FString::Printf(TEXT("Left Y: %d"), LeftY));
	GEngine->AddOnScreenDebugMessage(1002, 1.f, FColor::Cyan, FString::Printf(TEXT("Right X: %d"), RightX));
	GEngine->AddOnScreenDebugMessage(1003, 1.f, FColor::Cyan, FString::Printf(TEXT("Right Y: %d"), RightY));
	GEngine->AddOnScreenDebugMessage(1004, 1.f, FColor::Cyan,
	                                 FString::Printf(TEXT("IdleCalibrationSeconds: %f"), IdleCalibrationSeconds));

	IdleCalibrationSeconds += DeltaTime;
}

void FBnusioDevice::UpdateCalibrationActive(const float& DeltaTime)
{
	const auto Viewport = GEngine->GameViewport;
	if (!Viewport)
	{
		return;
	}
	const auto SubSystem = Viewport->GetGameInstance()->GetSubsystem<UKizunaKitGameInstanceSubsystem>();
	if (LastCalibrationMode != ECalibrationMode::Active)
	{
		SubSystem->WindowData->LeftStickX.Min = 65535;
		SubSystem->WindowData->LeftStickX.Max = 0;
		SubSystem->WindowData->LeftStickY.Min = 65535;
		SubSystem->WindowData->LeftStickY.Max = 0;
		SubSystem->WindowData->RightStickX.Min = 65535;
		SubSystem->WindowData->RightStickX.Max = 0;
		SubSystem->WindowData->RightStickY.Min = 65535;
		SubSystem->WindowData->RightStickY.Max = 0;
		SubSystem->WindowData->LeftPedal.Min = 65535;
		SubSystem->WindowData->LeftPedal.Max = 0;
		SubSystem->WindowData->RightPedal.Min = 65535;
		SubSystem->WindowData->RightPedal.Max = 0;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("アクティブ状態のキャリブレーション中..."));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("スティックやペダルを十分に動かしてください"));
	}

	const auto LeftStickX = static_cast<float>(FBnusio::GetAnalogIn(FBnusio::ChLeftX));
	const auto LeftStickY = static_cast<float>(FBnusio::GetAnalogIn(FBnusio::ChLeftY));
	const auto RightStickX = static_cast<float>(FBnusio::GetAnalogIn(FBnusio::ChRightX));
	const auto RightStickY = static_cast<float>(FBnusio::GetAnalogIn(FBnusio::ChRightY));
	const auto LeftPedal = static_cast<float>(FBnusio::GetAnalogIn(FBnusio::ChLeftPedal));
	const auto RightPedal = static_cast<float>(FBnusio::GetAnalogIn(FBnusio::ChRightPedal));

	SubSystem->WindowData->LeftStickX.Min = std::ranges::min(SubSystem->WindowData->LeftStickX.Min, LeftStickX);
	SubSystem->WindowData->LeftStickX.Max = std::ranges::max(SubSystem->WindowData->LeftStickX.Max, LeftStickX);
	SubSystem->WindowData->LeftStickY.Min = std::ranges::min(SubSystem->WindowData->LeftStickY.Min, LeftStickY);
	SubSystem->WindowData->LeftStickY.Max = std::ranges::max(SubSystem->WindowData->LeftStickY.Max, LeftStickY);

	SubSystem->WindowData->RightStickX.Min = std::ranges::min(SubSystem->WindowData->RightStickX.Min, RightStickX);
	SubSystem->WindowData->RightStickX.Max = std::ranges::max(SubSystem->WindowData->RightStickX.Max, RightStickX);
	SubSystem->WindowData->RightStickY.Min = std::ranges::min(SubSystem->WindowData->RightStickY.Min, RightStickY);
	SubSystem->WindowData->RightStickY.Max = std::ranges::max(SubSystem->WindowData->RightStickY.Max, RightStickY);

	SubSystem->WindowData->LeftPedal.Min = std::ranges::min(SubSystem->WindowData->LeftPedal.Min, LeftPedal);
	SubSystem->WindowData->LeftPedal.Max = std::ranges::max(SubSystem->WindowData->LeftPedal.Max, LeftPedal);

	SubSystem->WindowData->RightPedal.Min = std::ranges::min(SubSystem->WindowData->RightPedal.Min, RightPedal);
	SubSystem->WindowData->RightPedal.Max = std::ranges::max(SubSystem->WindowData->RightPedal.Max, RightPedal);
}
