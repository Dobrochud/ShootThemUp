// Shoot Them Up 4.26.All Rights reserved


#include "Components/STUAIPerceptionComponent.h"
#include "AIController.h"
#include "STUUtils.h"
#include "Components/STUHealthComponent.h"
#include "Perception/AISense_Sight.h"

AActor* USTUAIPerceptionComponent :: GetClosesEnemy() const
{
	TArray<AActor*> PerciveActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PerciveActors);
	if (PerciveActors.Num()==0)
	{
		return nullptr;
	}

	const auto Controller = Cast<AAIController>(GetOwner());
	if (!Controller)
	{
		return nullptr;
	}

	const auto Pawn = Controller->GetPawn();
	if (!Pawn)
	{
		return nullptr;
	}
	float BestDistance = MAX_FLT;
	AActor* BestPawn = nullptr;

	for (const auto PerciveActor: PerciveActors)
	{
		const auto HeathComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(PerciveActor);

		const auto PercivePawn = Cast<APawn>(PerciveActor);
		const auto AreEnemies = PercivePawn && STUUtils::AreEnemies(Controller, PercivePawn->GetController());

		if (HeathComponent && !HeathComponent->IsDead() && AreEnemies)
		{
			const auto CurrentDistance = (PerciveActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
			if (CurrentDistance<BestDistance)
			{
				BestDistance = CurrentDistance;
				BestPawn = PerciveActor;
			}
		}
	}
	return BestPawn;
}