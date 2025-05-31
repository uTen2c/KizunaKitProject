// Fill out your copyright notice in the Description page of Project Settings.


#include "BnusioInputKeys.h"

#define LOCTEXT_NAMESPACE "KizunaKit"

static const FName Category = "BNUsio";

const FKey FBnusioInputKeys::Left_Stick_Left("Bnusio_Left_Stick_Left");
const FKey FBnusioInputKeys::Left_Stick_Center("Bnusio_Left_Stick_Center");
const FKey FBnusioInputKeys::Left_Stick_Right("Bnusio_Left_Stick_Right");
const FKey FBnusioInputKeys::Left_Stick_Trigger("Bnusio_Left_Stick_Trigger");

const FKey FBnusioInputKeys::Right_Stick_Left("Bnusio_Right_Stick_Left");
const FKey FBnusioInputKeys::Right_Stick_Center("Bnusio_Right_Stick_Center");
const FKey FBnusioInputKeys::Right_Stick_Right("Bnusio_Right_Stick_Right");
const FKey FBnusioInputKeys::Right_Stick_Trigger("Bnusio_Right_Stick_Trigger");

const FKey FBnusioInputKeys::Test("Bnusio_Test");
const FKey FBnusioInputKeys::Enter("Bnusio_Enter");
const FKey FBnusioInputKeys::Select_Down("Bnusio_Select_Down");
const FKey FBnusioInputKeys::Select_Up("Bnusio_Select_Up");
const FKey FBnusioInputKeys::Service("Bnusio_Service");
const FKey FBnusioInputKeys::Start("Bnusio_Start");
const FKey FBnusioInputKeys::Volume_Down("Bnusio_Volume_Down");
const FKey FBnusioInputKeys::Volume_Up("Bnusio_Volume_Up");

const FKey FBnusioInputKeys::Left_Stick_X("Bnusio_Left_Stick_X");
const FKey FBnusioInputKeys::Left_Stick_Y("Bnusio_Left_Stick_Y");
const FKey FBnusioInputKeys::Left_Stick_2D("Bnusio_Left_Stick_2D");

const FKey FBnusioInputKeys::Right_Stick_X("Bnusio_Right_Stick_X");
const FKey FBnusioInputKeys::Right_Stick_Y("Bnusio_Right_Stick_Y");
const FKey FBnusioInputKeys::Right_Stick_2D("Bnusio_Right_Stick_2D");

const FKey FBnusioInputKeys::Left_Pedal("Bnusio_Left_Pedal");
const FKey FBnusioInputKeys::Right_Pedal("Bnusio_Right_Pedal");

void FBnusioInputKeys::Init()
{
	EKeys::AddMenuCategoryDisplayInfo(
		Category,
		LOCTEXT("BNUsioSubCategory", "BNUsio"),
		TEXT("GraphEditor.PadEvent_16x")
	);

	EKeys::AddKey({
		Left_Stick_Left,
		LOCTEXT("BnusioLeftStickLeft", "BNUsio Left stick left"),
		FKeyDetails::GamepadKey,
		Category
	});
	EKeys::AddKey({
		Left_Stick_Center,
		LOCTEXT("BnusioLeftStickCenter", "BNUsio Left stick center"),
		FKeyDetails::GamepadKey,
		Category
	});
	EKeys::AddKey({
		Left_Stick_Right,
		LOCTEXT("BnusioLeftStickRight", "BNUsio Left stick right"),
		FKeyDetails::GamepadKey,
		Category
	});
	EKeys::AddKey({
		Left_Stick_Trigger,
		LOCTEXT("BnusioLeftStickTrigger", "BNUsio Left stick trigger"),
		FKeyDetails::GamepadKey,
		Category
	});

	EKeys::AddKey({
		Right_Stick_Left,
		LOCTEXT("BnusioRightStickLeft", "BNUsio Right stick left"),
		FKeyDetails::GamepadKey,
		Category
	});
	EKeys::AddKey({
		Right_Stick_Center,
		LOCTEXT("BnusioRightStickCenter", "BNUsio Right stick center"),
		FKeyDetails::GamepadKey,
		Category
	});
	EKeys::AddKey({
		Right_Stick_Right,
		LOCTEXT("BnusioRightStickRight", "BNUsio Right stick right"),
		FKeyDetails::GamepadKey,
		Category
	});
	EKeys::AddKey({
		Right_Stick_Trigger,
		LOCTEXT("BnusioRightStickTrigger", "BNUsio Right stick trigger"),
		FKeyDetails::GamepadKey,
		Category
	});

	EKeys::AddKey({
		Test,
		LOCTEXT("BnusioTest", "BNUsio Test"),
		FKeyDetails::GamepadKey,
		Category
	});
	EKeys::AddKey({
		Enter,
		LOCTEXT("BnusioEnter", "BNUsio Enter"),
		FKeyDetails::GamepadKey,
		Category
	});
	EKeys::AddKey({
		Select_Down,
		LOCTEXT("BnusioSelectDown", "BNUsio Select down"),
		FKeyDetails::GamepadKey,
		Category
	});
	EKeys::AddKey({
		Select_Up,
		LOCTEXT("BnusioSelectUp", "BNUsio Select up"),
		FKeyDetails::GamepadKey,
		Category
	});
	EKeys::AddKey({
		Service,
		LOCTEXT("BnusioService", "BNUsio Service"),
		FKeyDetails::GamepadKey,
		Category
	});
	EKeys::AddKey({
		Start,
		LOCTEXT("BnusioStart", "BNUsio Start"),
		FKeyDetails::GamepadKey,
		Category
	});
	EKeys::AddKey({
		Volume_Down,
		LOCTEXT("BnusioVolumeDown", "BNUsio Volume down"),
		FKeyDetails::GamepadKey,
		Category
	});
	EKeys::AddKey({
		Volume_Up,
		LOCTEXT("BnusioVolumeUp", "BNUsio Volume up"),
		FKeyDetails::GamepadKey,
		Category
	});

	EKeys::AddKey({
		Left_Stick_X,
		LOCTEXT("BnusioLeftStickX", "BNUsio Left stick x (Analog)"),
		FKeyDetails::GamepadKey | FKeyDetails::Axis1D,
		Category
	});
	EKeys::AddKey({
		Left_Stick_Y,
		LOCTEXT("BnusioLeftStickY", "BNUsio Left stick y (Analog)"),
		FKeyDetails::GamepadKey | FKeyDetails::Axis1D,
		Category
	});
	EKeys::AddPairedKey(
		{
			Left_Stick_2D,
			LOCTEXT("BnusioLeftStick2D", "BNUsio Left stick 2D (Analog)"),
			FKeyDetails::GamepadKey | FKeyDetails::Axis2D,
			Category
		},
		Left_Stick_X, Left_Stick_Y
	);

	EKeys::AddKey({
		Right_Stick_X,
		LOCTEXT("BnusioRightStickX", "BNUsio Right stick x (Analog)"),
		FKeyDetails::GamepadKey | FKeyDetails::Axis1D,
		Category
	});
	EKeys::AddKey({
		Right_Stick_Y,
		LOCTEXT("BnusioRightStickY", "BNUsio Right stick y (Analog)"),
		FKeyDetails::GamepadKey | FKeyDetails::Axis1D,
		Category
	});
	EKeys::AddPairedKey(
		{
			Right_Stick_2D,
			LOCTEXT("BnusioRightStick2D", "BNUsio Right stick 2D (Analog)"),
			FKeyDetails::GamepadKey | FKeyDetails::Axis2D,
			Category
		},
		Right_Stick_X, Right_Stick_Y
	);

	EKeys::AddKey({
		Left_Pedal,
		LOCTEXT("BnusioLeftPedal", "BNUsio Left pedal (Analog)"),
		FKeyDetails::GamepadKey | FKeyDetails::Axis1D,
		Category
	});
	EKeys::AddKey({
		Right_Pedal,
		LOCTEXT("BnusioRightPedal", "BNUsio Right pedal (Analog)"),
		FKeyDetails::GamepadKey | FKeyDetails::Axis1D,
		Category
	});
}
