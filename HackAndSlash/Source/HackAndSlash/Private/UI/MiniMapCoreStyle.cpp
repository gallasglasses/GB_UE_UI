#include "UI/MiniMapCoreStyle.h"
#include "Engine.h"
#include "SlateBasics.h"
#include "Slate/SlateGameResources.h"
#include "Styling/ISlateStyle.h"

#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush(Style->RootToContentDir(RelativePath, TEXT(".png")), __VA_ARGS__)

TSharedPtr<ISlateStyle> FMiniMapCoreStyle::StylePtr;

//TSharedPtr<ISlateStyle> FindStyle(const FString& ScopeToDirectory)
//{
//	TSharedPtr<ISlateStyle> Style = FSlateGameResources::New(FName("MiniMapCoreStyle"), ScopeToDirectory, ScopeToDirectory);
//	return Style;
//}

TSharedPtr<ISlateStyle> FindStyle()
{
	FString Path = FPaths::ProjectContentDir() / TEXT("/HASGame/UI");
	//FString Path = "/HASGame/UI";
	TSharedPtr<FSlateStyleSet> Style = FSlateGameResources::New(FName("MiniMapCoreStyle"), Path, Path);
	
	//Style->Set("DefaultPadding", FMargin(1.f));
	Style->Set("SMiniMapBorder",new IMAGE_BRUSH("MiniMapBorder", FVector2D(200.f)));
	Style->Set("SMiniMapImage", new IMAGE_BRUSH("MiniMapImage", FVector2D(2329.f))); 
	Style->Set("SPlayerPointImage", new IMAGE_BRUSH("PlayerPointImage", FVector2D(10.f)));
	Style->Set("DefaultPadding",FMargin(5.f));
	return Style;
}

#undef IMAGE_BRUSH

void FMiniMapCoreStyle::Initialize()
{
	Shutdown();

	StylePtr = FindStyle();
	FSlateStyleRegistry::RegisterSlateStyle(*StylePtr);
}

void FMiniMapCoreStyle::Shutdown()
{
	if (StylePtr.IsValid())
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*StylePtr);
		StylePtr.Reset();
	}
}

const ISlateStyle& FMiniMapCoreStyle::Get()
{
	if (!StylePtr.IsValid())
	{
		Initialize();
	}
	return *StylePtr;
}