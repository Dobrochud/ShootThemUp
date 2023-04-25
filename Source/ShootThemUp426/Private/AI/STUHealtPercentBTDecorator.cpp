// Shoot Them Up 4.26.All Rights reserved


#include "AI/STUHealtPercentBTDecorator.h"
#include "AIController.h"
#include "STUUtils.h"
#include "Components/STUHealthComponent.h"

USTUHealtPercentBTDecorator::USTUHealtPercentBTDecorator()
{
	NodeName = "Health Percent";

}

bool USTUHealtPercentBTDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto Controller = OwnerComp.GetAIOwner();
	if (!Controller) return false;

	const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>((Controller->GetPawn()));

	if (!HealthComponent || HealthComponent->IsDead()) return false;

	return HealthComponent->GetHealthPercent() <= HealthPecent;

}
