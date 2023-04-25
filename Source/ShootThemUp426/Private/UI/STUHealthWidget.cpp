// Shoot Them Up 4.26.All Rights reserved


#include "UI/STUHealthWidget.h"
#include "Components/ProgressBar.h"

void USTUHealthWidget::SetHeakthPercent(float Percent)
{
	if (!HealthProgressBar) return;
	const auto HealthBarVisibility = Percent > PercentVisibilityThreshold || FMath::IsNearlyZero(Percent)//
		? ESlateVisibility::Hidden : ESlateVisibility::Visible;

	HealthProgressBar->SetVisibility(HealthBarVisibility);

	const auto HealthBarColor = Percent > PercentColorThreshold ? GoodColor : BadColor;
	HealthProgressBar->SetFillColorAndOpacity(HealthBarColor);

	HealthProgressBar->SetPercent(Percent);
}