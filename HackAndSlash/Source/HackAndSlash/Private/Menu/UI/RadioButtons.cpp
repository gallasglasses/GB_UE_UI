// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/UI/RadioButtons.h"
#include "Menu/UI/SHASSlateRadioButton.h"

void URadioButtons::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	RadioButtons.Reset();
}

TSharedRef<SWidget> URadioButtons::RebuildWidget()
{
	RadioButtons = SNew(SHASSlateRadioButton)
	.OnRadioButtonChanged_UObject(this, &ThisClass::OnRadioButtonsChangedFunc);
	return RadioButtons.ToSharedRef();
}

void URadioButtons::OnRadioButtonsChangedFunc(int32 NewSelectedButton)
{
	OnRadioButtonChanged.Broadcast(NewSelectedButton);
}
