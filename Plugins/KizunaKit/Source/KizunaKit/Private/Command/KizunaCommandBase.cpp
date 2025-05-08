// Fill out your copyright notice in the Description page of Project Settings.


#include "Command/KizunaCommandBase.h"

FInt32ParsedResult FKizunaCommandBase::ParseInt(const FString& Arg)
{
	if (!FCString::IsNumeric(*Arg))
	{
		return {0, true, FString::Printf(TEXT("不正な引数。 整数である必要があります: %s"), *Arg)};
	}

	const auto Result = FCString::Atoi(*Arg);
	return {Result, false, ""};
}

FInt32ParsedResult FKizunaCommandBase::ParseInt(const FString& Arg, const int Min, const int Max)
{
	const auto& Result = ParseInt(Arg);

	if (Result.bError)
	{
		return Result;
	}

	if (Result.Value < Min || Result.Value > Max)
	{
		return {Result.Value, true, FString::Printf(TEXT("不正な引数。 %d から %d の範囲である必要があります: %s"), Min, Max, *Arg)};
	}

	return Result;
}

bool FKizunaCommandBase::PrintErrorIfHasError(const FInt32ParsedResult& Result)
{
	if (Result.bError)
	{
		PrintErrorMessage(Result.ErrorMessage);
		return true;
	}
	return false;
}

void FKizunaCommandBase::PrintErrorMessage(const FString& Message)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, Message);
}

void FKizunaCommandBase::PrintSuccessMessage(const FString& Message)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, Message);
}
