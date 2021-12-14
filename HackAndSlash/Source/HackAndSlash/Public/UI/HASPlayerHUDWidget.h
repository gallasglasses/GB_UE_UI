// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HASPlayerHUDWidget.generated.h"

class UHASMiniMapWidget;

UCLASS()
class HACKANDSLASH_API UHASPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	float GetHealthPercent() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool IsPlayerAlive() const;
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	bool IsPlayerSpectating() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void OnTakeDamage();

	virtual bool Initialize() override;

protected:

	virtual void NativePreConstruct() override;

private:

	void OnHealthChanged(float Health, float HealthDelta);
};
