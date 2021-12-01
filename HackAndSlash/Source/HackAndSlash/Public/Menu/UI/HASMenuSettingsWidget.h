// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HASMenuSettingsWidget.generated.h"

class UButton;
class UWidgetSwitcher;

UCLASS()
class HACKANDSLASH_API UHASMenuSettingsWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
		UButton* GeneralSettingsButton;

	UPROPERTY(meta = (BindWidget))
		UButton* GameplaySettingsButton;

	UPROPERTY(meta = (BindWidget))
		UButton* GraphicsSettingsButton;	
		
	UPROPERTY(meta = (BindWidget))
		UButton* SoundSettingsButton;

	UPROPERTY(meta = (BindWidget))
		UButton* BackToMenuButton;

	UPROPERTY(meta = (BindWidget))
		UWidgetSwitcher* SettingsWidgetSwitcher;


	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
		void OnGeneralSettingsClicked();

	UFUNCTION()
		void OnGameplaySettingsClicked();

	UFUNCTION()
		void OnGraphicsSettingsClicked();

	UFUNCTION()
		void OnSoundSettingsClicked();

	public:
		UButton* GetBackToMenuButton();

		void SetFirstActiveWidgetIndex();
};
