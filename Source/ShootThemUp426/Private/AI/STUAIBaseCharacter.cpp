// Shoot Them Up 4.26.All Rights reserved


#include "AI/STUAIBaseCharacter.h"
#include "AI/STUAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/STUAIWeaponComponent.h"
#include "Components/WidgetComponent.h"
#include "BrainComponent.h"
#include "UI/STUHealthWidget.h"
#include "Components/STUHealthComponent.h"

ASTUAIBaseCharacter::ASTUAIBaseCharacter(const FObjectInitializer& ObjInit) : 
	Super(ObjInit.SetDefaultSubobjectClass<USTUAIWeaponComponent>("WeaponComponent"))

{
	AutoPossessAI = EAutoPossessAI::Disabled;
	AIControllerClass = ASTUAIBaseCharacter::StaticClass();

	bUseControllerRotationYaw = false;
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0, 200.0f,0.0f);
	}
	HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("Health");
	HealthWidgetComponent->SetupAttachment(GetRootComponent());
	HealthWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	HealthWidgetComponent->SetDrawAtDesiredSize(true);
}

void ASTUAIBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpateHealthWidgetVisibility();
}

void ASTUAIBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	check(HealthWidgetComponent);

}

void ASTUAIBaseCharacter::OnHealthChanged(float Health, float HealthDelta)
{
	Super::OnHealthChanged( Health,  HealthDelta);
	const auto  HealthBarWidget = Cast<USTUHealthWidget>(HealthWidgetComponent->GetUserWidgetObject());
	if (!HealthBarWidget) return;
	HealthBarWidget->SetHeakthPercent(HealthComponent->GetHealthPercent());
}

void ASTUAIBaseCharacter::OnDeath()
{
	Super::OnDeath();
	const auto STUController = Cast<AAIController>(Controller);
	if (STUController && STUController->BrainComponent)
	{
		STUController->BrainComponent->Cleanup();
	}

}

void ASTUAIBaseCharacter::UpateHealthWidgetVisibility()
{
	if (!GetWorld() || !GetWorld()->GetFirstPlayerController() || !GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator())
	return;

	const auto PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator()->GetActorLocation();
	const auto Distance = FVector::Distance(PlayerLocation, GetActorLocation());
	HealthWidgetComponent->SetVisibility(Distance < HealthVisibilityDistance);
}
