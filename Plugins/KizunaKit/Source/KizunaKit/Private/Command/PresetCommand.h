#pragma once
#include "KizunaCommandBase.h"

class FPresetCommand final : public FKizunaCommandBase
{
	static constexpr auto X = -2160;
	static constexpr auto Y = 0;
	static constexpr auto Width = 3240;
	static constexpr auto Height = 1920;
	static constexpr auto Monitor0 = 1;
	static constexpr auto Monitor1 = 0;
	static constexpr auto Monitor2 = 2;
	inline static const TCHAR* MpcPath = TEXT("/KizunaKit/Material/MPC_VirtualMonitorLayout.MPC_VirtualMonitorLayout");

public:
	static void OnRun(const TArray<FString>& Args, UWorld* World);
};
