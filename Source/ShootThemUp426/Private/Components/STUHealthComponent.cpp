// Shoot Them Up 4.26.All Rights reserved


#include "Components/STUHealthComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"
#include "Camera/CameraShake.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "STUGameModeBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All);

USTUHealthComponent::USTUHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

float USTUHealthComponent::GetHealthPercent() const
{
	return Health/MaxHealth;
}

float USTUHealthComponent::GetHealth() const
{
	return Health;
}

bool USTUHealthComponent::TryToAddHealth(float HealthAmount)
{
	if (IsHealthFull() || IsDead())
	{
		return false;
	}
	SetHealth(Health + HealthAmount);
	return true;
}

bool USTUHealthComponent::IsHealthFull() const
{
	return FMath::IsNearlyEqual(Health, MaxHealth);
}

bool USTUHealthComponent::IsDead() const
{
	return FMath::IsNearlyZero(Health);
}

void USTUHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	check(MaxHealth>0);
	SetHealth(MaxHealth);

	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeAnyDamage);
	}
}

void USTUHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f || IsDead() || !GetWorld())
	{
		return;
	}

	SetHealth(Health - Damage);

	GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);

	if (IsDead())
	{
		Killed(InstigatedBy);
		OnDeath.Broadcast();
	}
	else if (AutoHeal )
	{
	
		GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &USTUHealthComponent::HealUpdate, HealUpdateTime, true, HealDelay);
	}
	PlayCameraShake();
}
 
void USTUHealthComponent:: HealUpdate()
{
	SetHealth(Health + HealModifier);
	//OnHealthChanged.Broadcast(Health);

	if (IsHealthFull() && GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	
	}
}

void USTUHealthComponent::SetHealth(float NewHealth)
{
	const auto NextHealth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
	const auto HealthDelta = NextHealth - Health;
	Health = NextHealth;
	OnHealthChanged.Broadcast(Health, HealthDelta);
}

void USTUHealthComponent::PlayCameraShake()
{
	if (IsDead())
	{
		return;
	}
	const auto Player = Cast<APawn>(GetOwner());
	if (!Player)
	{ 
		return;
	}
	const auto Controller = Player->GetController<APlayerController>();
	if (!Controller || !Controller->PlayerCameraManager) return;
	Controller->PlayerCameraManager->StartCameraShake(CameraShake);

}

void USTUHealthComponent::Killed(AController* KillerController)
{
	if (!GetWorld()) return;
	const auto CameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!CameMode) return;

	const auto Player = Cast<APawn>(GetOwner());
	const auto VictimController = Player ? Player->GetController() : nullptr;

	CameMode->Killed(KillerController, VictimController);
}
