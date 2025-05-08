// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

struct FInt32ParsedResult
{
	int32 Value;
	bool bError;
	FString ErrorMessage;
};

class FKizunaCommandBase
{
protected:
	static FInt32ParsedResult ParseInt(const FString& Arg);
	static FInt32ParsedResult ParseInt(const FString& Arg, const int Min, const int Max);

	static bool PrintErrorIfHasError(const FInt32ParsedResult& Result);

	static void PrintErrorMessage(const FString& Message);
	static void PrintSuccessMessage(const FString& Message);
};
