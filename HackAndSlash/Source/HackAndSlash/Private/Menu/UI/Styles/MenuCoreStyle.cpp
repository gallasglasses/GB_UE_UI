
#include "Menu/UI/Styles/MenuCoreStyle.h"
#include "Engine.h"
#include "SlateBasics.h"
#include "Slate/SlateGameResources.h"
#include "Styling/ISlateStyle.h"

#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush(StyleMenu->RootToContentDir(RelativePath, TEXT(".png")), __VA_ARGS__)

TSharedPtr<ISlateStyle> FMenuCoreStyle::StyleMenuPtr;

TSharedPtr<ISlateStyle> FindStyle(const FString& ScopeToDirectory)
{
	//FString Path = FPaths::ProjectContentDir() / TEXT("/Game/HASGame/Menu/UI/Styles");

	TSharedPtr<ISlateStyle> StyleMenu = FSlateGameResources::New(FName("MenuCoreStyle"), ScopeToDirectory, ScopeToDirectory);
// 	
// 	StyleMenu->Set("SDefault", new IMAGE_BRUSH("Default", FVector2D(1279.f,720.f)));
// 	StyleMenu->Set("DarkThemeImage", FLinearColor(0.f, 0.f, 0.f, 0.4f));
// 	StyleMenu->Set("LightThemeImage", FLinearColor(1.f, 1.f, 1.f, 0.f));
	return StyleMenu;
}


#undef IMAGE_BRUSH

void FMenuCoreStyle::Initialize()
{
	Shutdown();

	StyleMenuPtr = FindStyle("/Game/HASGame/Menu/UI/Styles");
	//StyleMenuPtr = FindStyle();
	FSlateStyleRegistry::RegisterSlateStyle(*StyleMenuPtr);
}

void FMenuCoreStyle::Shutdown()
{
	if (StyleMenuPtr.IsValid())
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*StyleMenuPtr);
		StyleMenuPtr.Reset();
	}
}

const ISlateStyle& FMenuCoreStyle::Get()
{
	if (!StyleMenuPtr.IsValid())
	{
		Initialize();
	}
	return *StyleMenuPtr;
}