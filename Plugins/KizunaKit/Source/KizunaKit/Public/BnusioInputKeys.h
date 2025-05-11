// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

struct FBnusioInputKeys
{
	static const FKey Left_Stick_Left;
	static const FKey Left_Stick_Center;
	static const FKey Left_Stick_Right;
	static const FKey Left_Stick_Trigger;
	
	static const FKey Right_Stick_Left;
	static const FKey Right_Stick_Center;
	static const FKey Right_Stick_Right;
	static const FKey Right_Stick_Trigger;
	
	static const FKey Test;
	static const FKey Enter;
	static const FKey Select_Down;
	static const FKey Select_Up;
	static const FKey Service;
	static const FKey Start;
	static const FKey Volume_Down;
	static const FKey Volume_Up;
	
	static const FKey Left_Stick_X;
	static const FKey Left_Stick_Y;
	static const FKey Left_Stick_2D;
	
	static const FKey Right_Stick_X;
	static const FKey Right_Stick_Y;
	static const FKey Right_Stick_2D;
	
	static const FKey Left_Pedal;
	static const FKey Right_Pedal;

	static void Init();
};
