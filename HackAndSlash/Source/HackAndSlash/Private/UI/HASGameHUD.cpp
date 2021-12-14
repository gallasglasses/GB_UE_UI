// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HASGameHUD.h"
#include "Blueprint/UserWidget.h"
#include "UI/HASMiniMapWidget.h"

DEFINE_LOG_CATEGORY_STATIC(GameHUDLog, All, All);

void AHASGameHUD::BeginPlay()
{
	Super::BeginPlay();

	TSubclassOf<UUserWidget>* MenuWidgetClass = MenuWidgetClasses.Find(EWidgetID::WID_MainMenu);
	if (MenuWidgetClass && *MenuWidgetClass)
	{
		CreateWidgetByClass(*MenuWidgetClass);
	}

	MiniMapHUDWidget = CreateWidget<UHASMiniMapWidget>(GetWorld(), MiniMapWidget);
	if (MiniMapHUDWidget)
	{
		MiniMapHUDWidget->AddToViewport();
	}
}

UUserWidget* AHASGameHUD::CreateWidgetByClass(const TSubclassOf<UUserWidget> MenuWidgetClass, const int32 ZOrder)
{
	CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), MenuWidgetClass);
	if (CurrentWidget)
	{
		CurrentWidget->AddToViewport(ZOrder);
	}
	return CurrentWidget;
}

UUserWidget* AHASGameHUD::GetCurrentWidget() const
{
	return CurrentWidget;
}

UUserWidget* AHASGameHUD::ShowWidget(const EWidgetID WidgetID, const int32 ZOrder)
{
	TSubclassOf<UUserWidget>* MenuWidgetClass = MenuWidgetClasses.Find(WidgetID);
	if (MenuWidgetClass && *MenuWidgetClass)
	{
		CreateWidgetByClass(*MenuWidgetClass, ZOrder);
	}
	return CurrentWidget;
}

void AHASGameHUD::HideWidget()
{
	if (CurrentWidget)
	{
		CurrentWidget->RemoveFromParent();
		CurrentWidget = nullptr;
	}
}


void AHASGameHUD::SetPlayerHUDPosition(FVector2D PlayerHUDPosition)
{
	if (UHASMiniMapWidget* MiniMap = Cast<UHASMiniMapWidget>(MiniMapHUDWidget))
	{
		//UE_LOG(GameHUDLog, Display, TEXT("!!!GameHUDLog X %f, Y %f "), PlayerHUDPosition.X, PlayerHUDPosition.Y);

		MiniMap->SetPlayerWidgetPosition(PlayerHUDPosition);
	}
}

//void AHASGameHUD::BeginPlay()
//{
//	Super::BeginPlay();
//	/*auto PlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass);
//	if (PlayerHUDWidget)
//	{
//		PlayerHUDWidget->AddToViewport();
//	}
//
//	MiniMapHUDWidget = CreateWidget<UHASMiniMapWidget>(GetWorld(), MiniMapWidget);
//	if (MiniMapHUDWidget)
//	{
//		MiniMapHUDWidget->AddToViewport();
//	}*/
//}