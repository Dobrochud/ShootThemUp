// Shoot Them Up 4.26.All Rights reserved

#pragma once

#include "CoreMinimal.h"
#include "STUBaseCharacter.h"
#include "STUAIBaseCharacter.generated.h"

class UBehaviorTree;
class UWidgetComponent;

UCLASS()
class SHOOTTHEMUP426_API ASTUAIBaseCharacter : public ASTUBaseCharacter
{
	
	GENERATED_BODY()

public:
	ASTUAIBaseCharacter(const FObjectInitializer& ObjInit);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaviorTreeAsset;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UWidgetComponent* HealthWidgetComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	float HealthVisibilityDistance = 1000;

	virtual void Tick(float DeltaTime)override;

	virtual void BeginPlay()override;
	virtual void OnHealthChanged(float Health, float HealthDelta) override;
	virtual void OnDeath() override;

private:
	void UpateHealthWidgetVisibility();
};
