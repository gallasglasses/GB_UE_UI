// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Menu/UI/Styles/MenuDefaultWidgetStyle.h"
#include "HASMenuWidget.generated.h"

class UHASMenuSettingsWidget;
class UHASMenuAddContentWidget;
class UButton;
class UCanvasPanel;
class UCheckBox;
class UBackgroundBlur;
class UImage;
class UTextBlock;
class UHASMenuQuitWidget;

UCLASS()
class HACKANDSLASH_API UHASMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(meta = (BindWidget))
		UCanvasPanel* CanvasPanel; 
	
	UPROPERTY(meta = (BindWidget))
		UBackgroundBlur* MenuBackgroundBlur; 
	
	UPROPERTY(meta = (BindWidget))
		UImage* DarkThemeImage;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UButton* NewGameButton; 
		
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UTextBlock* NewGameText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* SettingsButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UTextBlock* SettingsText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* AdditionalContentButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UTextBlock* AdditionalContentText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* CreditButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UTextBlock* CreditText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* QuitButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UTextBlock* QuitText;

	UPROPERTY(meta = (BindWidget))
		UHASMenuSettingsWidget* SettingsWidget;

	UPROPERTY(meta = (BindWidget))
		UHASMenuAddContentWidget* AddContentWidget;

	UPROPERTY(meta = (BindWidget))
		UHASMenuQuitWidget* QuitWidget;
		
	UPROPERTY(meta = (BindWidget))
		UCheckBox* DarkThemeCheckBox;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UTextBlock* DarkThemeText;

	UPROPERTY(EditAnywhere, Category = Appearance, meta = (DisplayName = Style))
		FMenuDefaultStyle WidgetStyle;

	virtual void NativePreConstruct() override;
	virtual void NativeOnInitialized() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	UFUNCTION()
		void OnStartGameClicked();

	UFUNCTION()
		void OnSettingsClicked(); 
		
	UFUNCTION()
		void OnAddContentClicked(); 
		
	UFUNCTION()
		void OnCreditClicked();

	UFUNCTION()
		void OnQuitClicked(); 
	
	UFUNCTION()
		void OnChecked(bool bIsChecked);

	UFUNCTION()
		void OnBackSettingsToMenuClicked();

	UFUNCTION()
		void OnBackAddContentToMenuClicked();

	void SetWidgetStyle();
	void SetMenuTheme(FMenuDefaultStyle MenuWidgetStyle);

public:
	UPROPERTY(EditAnywhere, Category = Appearance, meta = (DisplayName = Style))
		bool bIsDarkTheme = false;
};
