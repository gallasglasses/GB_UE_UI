// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HASMenuWidget.generated.h"

class UHASMenuSettingsWidget;
class UButton;
class UCanvasPanel;

UCLASS()
class HACKANDSLASH_API UHASMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(meta = (BindWidget))
		UCanvasPanel* CanvasPanel;

	UPROPERTY(meta = (BindWidget))
		UButton* StartGameButton;

	UPROPERTY(meta = (BindWidget))
		UButton* SettingsButton;

	UPROPERTY(meta = (BindWidget))
		UButton* QuitButton;

	UPROPERTY(meta = (BindWidget))
		UHASMenuSettingsWidget* SettingsWidget;

	UPROPERTY(meta = (BindWidget))
		UUserWidget* QuitWidget;

	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
		void OnStartGameClicked();

	UFUNCTION()
		void OnSettingsClicked();

	UFUNCTION()
		void OnQuitClicked();

	UFUNCTION()
		void OnBackToMenuClicked();
};
