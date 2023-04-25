// Shoot Them Up 4.26.All Rights reserved


#include "Menu/STUMenuPlayerController.h"
#include "STUGameInstance.h"
void ASTUMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;

	//GetWorld()->GetGameInstance<USTUGameInstance>()->TestString = "Menu level says Hello!";
}