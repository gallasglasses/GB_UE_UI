// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HASHealthBarWidget.h"
#include "components/ProgressBar.h"

void UHASHealthBarWidget::SetHealthPercent(float Percent)
{
	if (!HealthProgressBar)
	{
		return;
	}

	const auto HealthProgressBarVisibility = (Percent > PercentVisibilityThreshold || FMath::IsNearlyZero(Percent))
	? ESlateVisibility::Hidden : ESlateVisibility::Visible;
	HealthProgressBar->SetVisibility(HealthProgressBarVisibility);

	const auto HealthProgressBarColor = Percent > PercentColorThreshold ? GoodColor : BadColor;
	HealthProgressBar->SetFillColorAndOpacity(HealthProgressBarColor);

	HealthProgressBar->SetPercent(Percent);
}