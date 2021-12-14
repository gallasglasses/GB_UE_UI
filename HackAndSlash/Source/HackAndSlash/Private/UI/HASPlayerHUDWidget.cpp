// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HASPlayerHUDWidget.h"
#include "UI/HASMiniMapWidget.h"
#include "Components/HASHealthComponent.h"
#include "HASUtils.h"
//#include "Components/CanvasPanelSlot.h"

void UHASPlayerHUDWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	/*if (MiniMapWidget)
	{
		Cast<UCanvasPanelSlot>(MiniMapWidget->Slot)->SetAutoSize(true);
		Cast<UCanvasPanelSlot>(MiniMapWidget->Slot)->SetPosition(FVector2D(-50.f, -50.f));
	}*/
}

float UHASPlayerHUDWidget::GetHealthPercent() const
{
	const auto HealthComponent = HASUtils::GetHASPlayerComponent<UHASHealthComponent>(GetOwningPlayerPawn());
	if (!HealthComponent)
	{
		return 0.0f;
	}
	return HealthComponent->GetHealthPercent();
}

bool UHASPlayerHUDWidget::IsPlayerAlive() const
{
	const auto HealthComponent = HASUtils::GetHASPlayerComponent<UHASHealthComponent>(GetOwningPlayerPawn());
	return HealthComponent && !HealthComponent->IsDead();
}

bool UHASPlayerHUDWidget::IsPlayerSpectating() const
{
	const auto Controller = GetOwningPlayer();
	return Controller && Controller->GetStateName() == NAME_Spectating;
}

bool UHASPlayerHUDWidget::Initialize()
{
	const auto HealthComponent = HASUtils::GetHASPlayerComponent<UHASHealthComponent>(GetOwningPlayerPawn());
	if (HealthComponent)
	{
		HealthComponent->OnHealthChanged.AddUObject(this, &UHASPlayerHUDWidget::OnHealthChanged);
	}
	return Super::Initialize();
}

void UHASPlayerHUDWidget::OnHealthChanged(float Health, float HealthDelta)
{
	if (HealthDelta < 0.0f)
	{
		OnTakeDamage();
	}
}