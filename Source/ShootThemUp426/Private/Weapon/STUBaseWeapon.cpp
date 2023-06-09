// Shoot Them Up 4.26.All Rights reserved


#include "Weapon/STUBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "..\Public\STUBaseCharacter.h" 
#include "GameFramework/PlayerController.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"


DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All);


ASTUBaseWeapon::ASTUBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);
}

void ASTUBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	check(WeaponMesh);
	checkf(DefaultAmmo.Bullets>0, TEXT("Bullets count couldn't be less or equal zero"));
	checkf(DefaultAmmo.Clips > 0, TEXT("Clips count couldn't be less or equal zero"));
	CurrentAmmo = DefaultAmmo;
}

void ASTUBaseWeapon::MakeShot()
{
}


void ASTUBaseWeapon::StartFire()
{
}
void ASTUBaseWeapon::StopFire()
{
}
bool ASTUBaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
	const auto STUCharacter = Cast<ACharacter>(GetOwner());
	if (!STUCharacter) return false;

	if (STUCharacter->IsPlayerControlled())
	{
		const auto Controller = STUCharacter->GetController<APlayerController>();
		if (!Controller) return false;
		Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
	}

	else
	{
		ViewLocation = GetMuzzelWorldLocation();
		ViewRotation = WeaponMesh->GetSocketRotation(MuzzleSocketName);
	}

	return true;
}

FVector ASTUBaseWeapon::GetMuzzelWorldLocation() const
{
	return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

bool ASTUBaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;

	if(!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;


	TraceStart = ViewLocation;
	const FVector ShooDirection = ViewRotation.Vector();
	TraceEnd = TraceStart + ShooDirection * TraceMaxDistance;
	return true;
}

void ASTUBaseWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd)
{
	if (!GetWorld()) return;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());
	CollisionParams.bReturnPhysicalMaterial = true;


	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);
}

void ASTUBaseWeapon::DecreaseAmmo()
{
	if (CurrentAmmo.Bullets == 0)
	{
		return;
	}

	CurrentAmmo.Bullets--;

	if (IsClipEmpty() && !IsAmmoEmpty())
	{
		OnClipEmpty.Broadcast(this);
		StopFire();
	}
}

bool ASTUBaseWeapon::IsAmmoEmpty() const
{
	return !CurrentAmmo.Infinite && CurrentAmmo.Clips ==0 && IsClipEmpty();
}

bool ASTUBaseWeapon::IsClipEmpty() const
{
	return CurrentAmmo.Bullets == 0;
}

bool ASTUBaseWeapon::IsAmmoFull() const
{
	return CurrentAmmo.Clips == DefaultAmmo.Clips && CurrentAmmo.Bullets == DefaultAmmo.Bullets;
}

void ASTUBaseWeapon::ChangeClip()
{
	if (!CurrentAmmo.Infinite)
	{
		if (CurrentAmmo.Clips == 0)
		{
			return;
		}
		CurrentAmmo.Clips--;
	}
	CurrentAmmo.Bullets = DefaultAmmo.Bullets;
}

bool ASTUBaseWeapon::CanReload() const
{
	return CurrentAmmo.Bullets < DefaultAmmo.Bullets && CurrentAmmo.Clips > 0;
}

bool ASTUBaseWeapon::TryToAddAmmo(int32 ClipsAmount)
{
	if (CurrentAmmo.Infinite || IsAmmoFull()	|| ClipsAmount<=0)
	{
		return false; 
	}
	else if (IsAmmoEmpty())
	{
		CurrentAmmo.Clips = FMath::Clamp(ClipsAmount, 0,DefaultAmmo.Clips+1 );
		OnClipEmpty.Broadcast(this);
	}
	else if (CurrentAmmo.Clips< DefaultAmmo.Clips)
	{
		const auto NextClipsAmount = CurrentAmmo.Clips + ClipsAmount;
		if (DefaultAmmo.Clips - NextClipsAmount>=0)
		{
			CurrentAmmo.Clips = NextClipsAmount;
		}
		else
		{
			CurrentAmmo.Clips = DefaultAmmo.Clips;
			CurrentAmmo.Bullets = DefaultAmmo.Bullets;
		}
	}
	else 
	{
		CurrentAmmo.Bullets = DefaultAmmo.Bullets;
	}
	return true;
}

void ASTUBaseWeapon::LogAmmo()
{
	FString AmmoInfo = "Ammo: "+ FString::FromInt(CurrentAmmo.Bullets)+ " / ";
	AmmoInfo += CurrentAmmo.Infinite ? "Infinite" : FString::FromInt(CurrentAmmo.Clips);
	UE_LOG(LogBaseWeapon, Display, TEXT("%s"), *AmmoInfo);
}

UNiagaraComponent* ASTUBaseWeapon::SpawnMuzzelFX()
{
	return UNiagaraFunctionLibrary::SpawnSystemAttached(
		MuzzleFX,//
		WeaponMesh,//
		MuzzleSocketName,//
		FVector::ZeroVector,
		FRotator::ZeroRotator,
		EAttachLocation::SnapToTarget, true);
	return nullptr;
}


