// Shoot Them Up 4.26.All Rights reserved


#include "UI/STUPlayerWidget.h"
#include "Components/STUHealthComponent.h"
#include "STUUtils.h"
#include "Components/STUWeaponComponent.h"
#include "Components/ProgressBar.h"
#include "STU_PlayerState.h"
float USTUPlayerWidget::GetHealthPercent() const
{

	const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(GetOwningPlayerPawn());
	if (!HealthComponent)
	{
		return 0.0f;
	}

	return HealthComponent->GetHealthPercent();
}

bool USTUPlayerWidget::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{
	const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(GetOwningPlayerPawn());
	if (!WeaponComponent)
	{
		return false;
	}
	return WeaponComponent->GetCurrentWeaponUIData(UIData);
}

bool USTUPlayerWidget::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const
{
	const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(GetOwningPlayerPawn());
	if (!WeaponComponent)
	{
		return false;
	}
	return WeaponComponent->GetCurrentWeaponAmmoData(AmmoData);
}

bool USTUPlayerWidget::IsPlayerAlive() const
{
	const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(GetOwningPlayerPawn());
	return HealthComponent && !HealthComponent->IsDead();
}

bool USTUPlayerWidget::IsPlayerSpectating() const
{
	const auto Controller = GetOwningPlayer();
	return Controller && Controller->GetStateName()== NAME_Spectating;
}

void USTUPlayerWidget::OnHealthChanged(float Health, float HealthDelta)
{
	if (HealthDelta<0.0f)
	{
		OnTakeDamage();
		if (!IsAnimationPlaying(DamageAnimation))
		{
			PlayAnimation(DamageAnimation);
		}
	}
	UpdateHealthBar();
}

void USTUPlayerWidget::OneNewPawn(APawn* NewPawn)
{
	const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(NewPawn);
	if (HealthComponent && !HealthComponent->OnHealthChanged.IsBoundToObject(this))
	{
		HealthComponent->OnHealthChanged.AddUObject(this, &USTUPlayerWidget::OnHealthChanged);
	}
	UpdateHealthBar();
}

void USTUPlayerWidget::UpdateHealthBar()
{
	if (HealthProgressBar)
	{
		HealthProgressBar->SetFillColorAndOpacity(GetHealthPercent() > PercentColorThreshold ? GoodColor : BadColor);
	}
}


void USTUPlayerWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (GetOwningPlayer())
	{
		GetOwningPlayer()->GetOnNewPawnNotifier().AddUObject(this, &USTUPlayerWidget::OneNewPawn);
		OneNewPawn(GetOwningPlayerPawn());
	}
}

int32 USTUPlayerWidget::GetKilssNum() const
{
	const auto Controller = GetOwningPlayer();
	if (!Controller) return 0;

	const auto PlayerState = Cast<ASTU_PlayerState>(Controller->PlayerState);
	return PlayerState ? PlayerState->GetKillsNum() : 0;
}

FString USTUPlayerWidget::FormatBullets(int32 BulletsNum) const
{
	const int32 MaxLen = 3;
	const TCHAR PrefixSymbol = '0';

	auto BulletStr = FString::FromInt(BulletsNum);
	const auto SymbolsNumToAdd = MaxLen - BulletStr.Len();

	if (SymbolsNumToAdd>0)
	{
		BulletStr = FString::ChrN(SymbolsNumToAdd, PrefixSymbol).Append(BulletStr);
	}

	return BulletStr;
}
