// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Menu/UI/Styles/MenuDefaultWidgetStyle.h"
#include "HASMenuSettingsWidget.generated.h"

class UButton;
class UWidgetSwitcher;
class UTextBlock;
class UImage;

UCLASS()
class HACKANDSLASH_API UHASMenuSettingsWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
		UButton* GeneralSettingsButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UTextBlock* GeneralSettingsText;

	UPROPERTY(meta = (BindWidget))
		UButton* GameplaySettingsButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UTextBlock* GameplaySettingsText;

	UPROPERTY(meta = (BindWidget))
		UButton* GraphicsSettingsButton;	

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UTextBlock* GraphicsSettingsText;
		
	UPROPERTY(meta = (BindWidget))
		UButton* SoundSettingsButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UTextBlock* SoundSettingsText;

	UPROPERTY(meta = (BindWidget))
		UButton* BackToMenuButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UTextBlock* BackToMenuText;

	UPROPERTY(meta = (BindWidget))
		UButton* DefaultSettingsButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UTextBlock* DefaultSettingsText;

	UPROPERTY(meta = (BindWidget))
		UButton* ApplySettingsButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UTextBlock* ApplySettingsText;

	UPROPERTY(meta = (BindWidget))
		UWidgetSwitcher* SettingsWidgetSwitcher;

	UPROPERTY(EditAnywhere, Category = Appearance, meta = (DisplayName = Style))
		FMenuDefaultStyle WidgetStyle;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UImage* ThemeImage;

	virtual void NativePreConstruct() override;
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

	void SetMenuTheme(FMenuDefaultStyle MenuWidgetStyle);
	void SetWidgetStyle();

	UPROPERTY(EditAnywhere, Category = Appearance, meta = (DisplayName = Style))
		bool bIsDarkTheme;
};