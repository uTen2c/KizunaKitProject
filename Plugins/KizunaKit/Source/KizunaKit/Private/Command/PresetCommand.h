#pragma once
#include "KizunaCommandBase.h"

class FPresetCommand final : public FKizunaCommandBase
{
public:
	static void OnRun(const TArray<FString>& Args, UWorld* World);
};
