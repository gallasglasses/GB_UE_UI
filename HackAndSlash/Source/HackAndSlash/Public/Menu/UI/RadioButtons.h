// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RadioButtons.generated.h"

class SHASSlateRadioButton;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRadioButtonsChangedEvent, int32, NewSelectedButton);

UCLASS()
class HACKANDSLASH_API URadioButtons : public UWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
		FOnRadioButtonsChangedEvent OnRadioButtonChanged;

	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

protected:

	virtual TSharedRef<SWidget> RebuildWidget() override;

private:
	TSharedPtr<SHASSlateRadioButton> RadioButtons;

	void OnRadioButtonsChangedFunc(int32 NewSelectedButton);

};
