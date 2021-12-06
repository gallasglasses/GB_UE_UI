// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HASPlayerHUDWidget.h"
#include "UI/HASMiniMapWidget.h"
#include "Components/HASHealthComponent.h"
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
	const auto HealthComponent = GetHealthComponent();
	if (!HealthComponent)
	{
		return 0.0f;
	}
	return HealthComponent->GetHealthPercent();
}

bool UHASPlayerHUDWidget::IsPlayerAlive() const
{
	const auto HealthComponent = GetHealthComponent();
	return HealthComponent && !HealthComponent->IsDead();
}

bool UHASPlayerHUDWidget::IsPlayerSpectating() const
{
	const auto Controller = GetOwningPlayer();
	return Controller && Controller->GetStateName() == NAME_Spectating;
}

bool UHASPlayerHUDWidget::Initialize()
{
	const auto HealthComponent = GetHealthComponent();
	if (HealthComponent)
	{
		HealthComponent->OnHealthChanged.AddUObject(this, &UHASPlayerHUDWidget::OnHealthChanged);
	}
	return Super::Initialize();
}

UHASHealthComponent* UHASPlayerHUDWidget::GetHealthComponent() const
{
	const auto Player = GetOwningPlayerPawn();
	if (!Player)
	{
		return nullptr;
	}
	const auto Component = Player->GetComponentByClass(UHASHealthComponent::StaticClass());
	const auto HealthComponent = Cast<UHASHealthComponent>(Component);
	if (!HealthComponent)
	{
		return nullptr;
	}
	return HealthComponent;
}

void UHASPlayerHUDWidget::OnHealthChanged(float Health, float HealthDelta)
{
	if (HealthDelta < 0.0f)
	{
		OnTakeDamage();
	}
}