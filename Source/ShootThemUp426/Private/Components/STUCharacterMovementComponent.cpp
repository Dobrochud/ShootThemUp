// Shoot Them Up 4.26.All Rights reserved


#include "Components/STUCharacterMovementComponent.h"
#include "..\Public\STUBaseCharacter.h" 

float USTUCharacterMovementComponent:: GetMaxSpeed() const 
{
	const float MaxSpeed = Super::GetMaxSpeed();
	const ASTUBaseCharacter* Player = Cast<ASTUBaseCharacter>(GetPawnOwner());
	return Player && Player->IsRunning() ? MaxSpeed * RunModifier : MaxSpeed;
}
