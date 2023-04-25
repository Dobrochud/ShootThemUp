// Shoot Them Up 4.26.All Rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STURifleWeapon.generated.h"

class USTUWeaponFXComponent;
class UNiagaraComponent;
class UNiagaraComponent;
class UAudioComponent;

UCLASS()
class SHOOTTHEMUP426_API ASTURifleWeapon : public ASTUBaseWeapon
{
	GENERATED_BODY()

public:

	ASTURifleWeapon();

	virtual void StartFire() override;
	virtual void StopFire() override;
	virtual void Zoom(bool Enabled) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float TimeBetweenShots = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float BulletSpread = 1.5f;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float DamageAmount = 10.0f;

	UPROPERTY(VisibleAnyWhere, Category = "VFX")
	USTUWeaponFXComponent* WeaponFXComponent;

	UPROPERTY(EditDefaultsOnly, Category = "VFX")
	UNiagaraSystem* TraceFX;

	UPROPERTY(EditDefaultsOnly, Category = "VFX")
	FString TraceTargetName = "TRaceTarget";


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float FOVZoomAngle = 50.0f;

	virtual void BeginPlay() override;
	virtual void MakeShot() override;
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;

private:
	FTimerHandle ShotTimerHandle;

	UPROPERTY()
	UNiagaraComponent* MuzzelFXComponent;

	UPROPERTY()
	UAudioComponent* FireAudioComponent;

	void MakeDamage(const FHitResult& HitResult);
	void InitFX();
	void SetFXActive(bool IsActive);
	void SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd);
	AController* GetController() const;

	float DefaultCameraFOV = 90.0f;
};
