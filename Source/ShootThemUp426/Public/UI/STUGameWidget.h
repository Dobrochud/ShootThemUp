// Shoot Them Up 4.26.All Rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUGameWidget.generated.h"

class ASTUGameModeBase;
class ASTU_PlayerState;

UCLASS()
class SHOOTTHEMUP426_API USTUGameWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:


	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetCurrentRoundNum() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetTotalRoundsNum() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetSecondsRemaining() const;

private:
	ASTUGameModeBase* GetSTUGameMode() const;
	ASTU_PlayerState* GetSTUPlayerState() const;

};
