// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Menu/UI/Styles/MenuDefaultWidgetStyle.h"
#include "HASMenuQuitWidget.generated.h"

class UButton;
class UTextBlock;
class UImage;

UCLASS()
class HACKANDSLASH_API UHASMenuQuitWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
		UButton* YesButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UTextBlock* YesText;

	UPROPERTY(meta = (BindWidget))
		UButton* NoButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UTextBlock* NoText;
		
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UTextBlock* QuestionText;

	UPROPERTY(EditAnywhere, Category = Appearance, meta = (DisplayName = Style))
		FMenuDefaultStyle WidgetStyle; 
		
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UImage* ThemeImage;

	virtual void NativePreConstruct() override;
	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
		void OnYesQuitClicked();

	UFUNCTION()
		void OnNoQuitClicked();

public:
		void SetMenuTheme(FMenuDefaultStyle MenuWidgetStyle);
		void SetWidgetStyle();
		//void SetIsThemeDark(bool bIsDark);

	UPROPERTY(EditAnywhere, Category = Appearance, meta = (DisplayName = Style))
		bool bIsDarkTheme;
};
