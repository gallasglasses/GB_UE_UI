// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HASMenuQuitWidget.generated.h"

class UButton;

UCLASS()
class HACKANDSLASH_API UHASMenuQuitWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
		UButton* YesButton;

	UPROPERTY(meta = (BindWidget))
		UButton* NoButton;

	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
		void OnYesQuitClicked();

	UFUNCTION()
		void OnNoQuitClicked();
};
