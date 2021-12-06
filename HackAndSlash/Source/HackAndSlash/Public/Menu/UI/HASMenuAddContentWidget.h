// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HASMenuAddContentWidget.generated.h"

class UNativeWidgetHost;
class UButton;
class UImage;

UCLASS()
class HACKANDSLASH_API UHASMenuAddContentWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(meta = (BindWidget))
		UNativeWidgetHost* RadioButtonsHost;

	UPROPERTY(meta = (BindWidget))
		UButton* BackToMenuButton;

	/*UPROPERTY(meta = (BindWidget))
		UImage* BorderImage;*/

	virtual void NativePreConstruct() override;
	virtual void NativeOnInitialized() override;

private:

public:

	UButton* GetBackToMenuButton();
};
