// Shoot Them Up 4.26.All Rights reserved


#include "UI/STUGameWidget.h"
#include "STUGameModeBase.h"
#include "STU_PlayerState.h"



int32 USTUGameWidget::GetCurrentRoundNum() const
{
	const auto GameMode = GetSTUGameMode();

	return GameMode ? GameMode->GetCurrentRoundNum() : 0;
}

int32 USTUGameWidget::GetTotalRoundsNum() const
{
	const auto GameMode = GetSTUGameMode();

	return GameMode ? GameMode->GetGameData().RoundsNum : 0;
}

int32 USTUGameWidget::GetSecondsRemaining() const
{
	const auto GameMode = GetSTUGameMode();

	return GameMode ? GameMode->GetRoundSecondsRemaining() : 0;
}

ASTUGameModeBase* USTUGameWidget::GetSTUGameMode() const
{
	return GetWorld() ? Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode()) : nullptr;
}

ASTU_PlayerState* USTUGameWidget::GetSTUPlayerState() const
{
	return GetOwningPlayer() ? Cast<ASTU_PlayerState>(GetOwningPlayer()->PlayerState) : nullptr;
}
