// Shoot Them Up 4.26.All Rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/STUWeaponComponent.h"
#include "STUAIWeaponComponent.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP426_API USTUAIWeaponComponent : public USTUWeaponComponent
{
	GENERATED_BODY()
	
	virtual void StartFire() override;
	virtual void NextWeapon()override;
};
