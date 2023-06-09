// Shoot Them Up 4.26.All Rights reserved

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "STUAIController.generated.h"

class USTUAIPerceptionComponent;
class USTURespawnComponent;

UCLASS()
class SHOOTTHEMUP426_API ASTUAIController : public AAIController
{
	GENERATED_BODY()

public:
	ASTUAIController();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USTUAIPerceptionComponent* STUAIPerceptionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USTURespawnComponent* RespawnComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FName FocusOnKeyName = "EnemyActor";



	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;
private:
	AActor* GetFocusOnActor() const;
};
