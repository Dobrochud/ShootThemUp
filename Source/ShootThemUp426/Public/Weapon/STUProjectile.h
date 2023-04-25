// Shoot Them Up 4.26.All Rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class	USTUWeaponFXComponent;


UCLASS()
class SHOOTTHEMUP426_API ASTUProjectile : public AActor
{
	GENERATED_BODY()
	
public:	

	ASTUProjectile();
	void SetShortDirection(const FVector& Direction);

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
	USphereComponent* CollisionComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
	UProjectileMovementComponent* MovementComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float DamageRadius = 200.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float DamageAmount = 200.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	bool DoFullDamage = false;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float LifeSeconds = 5.0f;

	UPROPERTY(VisibleAnyWhere, Category = "VFX")
	USTUWeaponFXComponent* WeaponFXComponent;

	virtual void BeginPlay() override;
private:
	FVector ShotDirection;

	UFUNCTION()
	void OnProjetileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	AController* GetController() const;
};
