// Shoot Them Up 4.26.All Rights reserved

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "STUHealtPercentBTDecorator.generated.h"

UCLASS()
class SHOOTTHEMUP426_API USTUHealtPercentBTDecorator : public UBTDecorator
{
	GENERATED_BODY()
public:
	USTUHealtPercentBTDecorator();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float HealthPecent = 0.6f;

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
}; 
