// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Menu/UI/Styles/MenuDefaultWidgetStyle.h"
#include "HASMenuAddContentWidget.generated.h"

class UNativeWidgetHost;
class UButton;
class UImage;
class URadioButtons;
class UTextBlock;

UCLASS()
class HACKANDSLASH_API UHASMenuAddContentWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

// 	UPROPERTY(meta = (BindWidget))
// 		UNativeWidgetHost* RadioButtonsHost;

	UPROPERTY(meta = (BindWidget))
		URadioButtons* BoxRadioButtons;

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

	UPROPERTY(EditAnywhere, Category = Appearance, meta = (DisplayName = Style))
		FMenuDefaultStyle WidgetStyle;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UImage* ThemeImage;

	virtual void NativePreConstruct() override;
	virtual void NativeOnInitialized() override;

private:

public:

	UPROPERTY(EditAnywhere, Category = Appearance, meta = (DisplayName = Style))
		bool bIsDarkTheme;

	UButton* GetBackToMenuButton();

	void SetMenuTheme(FMenuDefaultStyle MenuWidgetStyle);
	void SetWidgetStyle();
};