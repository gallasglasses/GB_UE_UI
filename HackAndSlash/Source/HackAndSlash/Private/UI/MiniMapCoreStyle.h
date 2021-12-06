#pragma once

#include "Slate.h"

class HACKANDSLASH_API FMiniMapCoreStyle
{
public:

	static void Initialize();
	static void Shutdown();
	static const ISlateStyle& Get();

private:

	static TSharedPtr<ISlateStyle> StylePtr;
};