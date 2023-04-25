// Shoot Them Up 4.26.All Rights reserved


#include "UI/STUGoToMenuWidget.h"
#include "Components/Button.h"
#include "STUGameInstance.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUGoToMenuWidget, All, All);

void USTUGoToMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (GOTOMenuButton)
	{
		GOTOMenuButton->OnClicked.AddDynamic(this, &USTUGoToMenuWidget::OnGOTOMenu);
	}
}

void USTUGoToMenuWidget::OnGOTOMenu()
{
	if (!GetWorld()) return;
	
	const auto STUGameInstance = GetWorld()->GetGameInstance<USTUGameInstance>();
	if (!STUGameInstance) return;

	if (STUGameInstance->GetMenuLevelName().IsNone())
	{
		UE_LOG(LogSTUGoToMenuWidget, Error, TEXT("Menu level name is NoNe!"));
		return;
	}

	UGameplayStatics::OpenLevel(this, STUGameInstance->GetMenuLevelName());
}
