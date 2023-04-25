// Shoot Them Up 4.26.All Rights reserved


#include "Pickups/STUHealthPickup.h"
#include "Components/STUHealthComponent.h"
#include "STUUtils.h"

//DEFINE_LOG_CATEGORY_STATIC(LogBasePickup, All, All)
 bool ASTUHealthPickup::GivePickupTo(APawn* PlayerPawn)

{
	const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(PlayerPawn);
	if (!HealthComponent )
	{
		return false;
	}

	return HealthComponent->TryToAddHealth(HealthAmount);
}