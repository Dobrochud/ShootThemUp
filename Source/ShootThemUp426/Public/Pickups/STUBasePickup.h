// Shoot Them Up 4.26.All Rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBasePickup.generated.h"

class USphereComponent;
class USoundCue;

UCLASS()
class SHOOTTHEMUP426_API ASTUBasePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	ASTUBasePickup();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PickUP")
	USphereComponent* CollisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickUP")
	float RespawnTime  = 5.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
	USoundCue* PickUpTakenSound;

	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:	

	virtual void Tick(float DeltaTime) override;
	bool CouldBeTaken() const;
private:
	float RotationYaw = 0.0f;
	FTimerHandle RespawnTimerHandle;
	void GenerateRotationYaw();
	void PickupWasTaken();
	void Respawn();
	virtual bool GivePickupTo(APawn* PlayerPawn);

};
