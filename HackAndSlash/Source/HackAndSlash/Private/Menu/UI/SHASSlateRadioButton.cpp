// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/UI/SHASSlateRadioButton.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SHASSlateRadioButton::Construct(const FArguments& InArgs)
{
	OnRadioButtonChanged = InArgs._OnRadioButtonChanged;

	ChildSlot
	[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
		[
			CreateCheckBox(0, TEXT("Option 1"))
		]
	+ SVerticalBox::Slot()
		[
			CreateCheckBox(1, TEXT("Option 2"))
		]
	+ SVerticalBox::Slot()
		[
			CreateCheckBox(2, TEXT("Option 3"))
		]
	];
}

TSharedRef<SWidget> SHASSlateRadioButton::CreateCheckBox(int32 InIndex, FString InText)
{
	return SNew(SCheckBox)
//.IsChecked_Lambda([InIndex, this](){return InIndex == CurrentIndex ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;})
	.IsChecked_Raw(this, &SHASSlateRadioButton::IsChecked, InIndex)
	.OnCheckStateChanged_Raw(this, &SHASSlateRadioButton::OnCheckBoxStateChanged, InIndex)
	[
		SNew(STextBlock)
		.Text(FText::FromString(InText))
	];
}

ECheckBoxState SHASSlateRadioButton::IsChecked(int32 InIndex) const
{
	return InIndex == CurrentIndex ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
}

void SHASSlateRadioButton::OnCheckBoxStateChanged(ECheckBoxState NewState, int32 InIndex)
{
	if (NewState == ECheckBoxState::Checked)
	{
		CurrentIndex = InIndex;
		OnRadioButtonChanged.ExecuteIfBound(CurrentIndex);
	}
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
