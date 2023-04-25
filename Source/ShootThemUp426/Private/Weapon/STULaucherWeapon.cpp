// Shoot Them Up 4.26.All Rights reserved


#include "Weapon/STULaucherWeapon.h"
#include "Weapon/STUProjectile.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"


void ASTULaucherWeapon::StartFire()
{
	MakeShot();
}

void ASTULaucherWeapon::MakeShot()
{
	if (!GetWorld() ) return;

	if (IsAmmoEmpty())
	{
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), NoAmmoSound, GetActorLocation());
		return;
	}

	FVector TraceStart, TraceEnd;
	if (!GetTraceData(TraceStart, TraceEnd)) return;

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
	const FVector Direction = (EndPoint - GetMuzzelWorldLocation()).GetSafeNormal();


	const FTransform SpawnTrancform(FRotator::ZeroRotator, GetMuzzelWorldLocation());
	ASTUProjectile* Projectile = GetWorld()-> SpawnActorDeferred<ASTUProjectile>(ProjectileClass, SpawnTrancform);
	if (Projectile)
	{
		Projectile->SetShortDirection(Direction);
		Projectile->SetOwner(GetOwner());
		Projectile->FinishSpawning(SpawnTrancform);
	}
	DecreaseAmmo();
	SpawnMuzzelFX();
	UGameplayStatics::SpawnSoundAttached(FireSound, WeaponMesh, MuzzleSocketName);
}