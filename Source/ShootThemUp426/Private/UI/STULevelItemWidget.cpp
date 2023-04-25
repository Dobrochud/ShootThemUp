// Shoot Them Up 4.26.All Rights reserved

#include "UI/STULevelItemWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void USTULevelItemWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (LevelSelectedButton)
	{
		LevelSelectedButton->OnClicked.AddDynamic(this, &USTULevelItemWidget::OnLevelItemClocked);
		LevelSelectedButton->OnHovered.AddDynamic(this, &USTULevelItemWidget::OnLevelItemHover);
		LevelSelectedButton->OnUnhovered.AddDynamic(this, &USTULevelItemWidget::OnLevelItemUnHover);
	}
}

void USTULevelItemWidget::OnLevelItemClocked()
{
	OnLevelSelected.Broadcast(LevelData);
}

void USTULevelItemWidget::OnLevelItemHover()
{
	if (FrameImage)
	{
		FrameImage->SetVisibility(ESlateVisibility::Visible);
	}
}

void USTULevelItemWidget::OnLevelItemUnHover()
{
	if (FrameImage)
	{
		FrameImage->SetVisibility(ESlateVisibility::Hidden);
	}
}

void USTULevelItemWidget::SetLevelData(const FLevelData& Data)
{
	LevelData = Data;

	if (LevelNameTextBlock)
	{
		LevelNameTextBlock->SetText(FText::FromName(Data.LevelDisplayName));
	}
	if (LevelImage)
	{
		LevelImage->SetBrushFromTexture(Data.LevelThumb);
	}
}

void USTULevelItemWidget::SetSelected(bool IsSelected)
{
	if (LevelImage)
	{
		LevelImage->SetColorAndOpacity(IsSelected ? FLinearColor::Red : FLinearColor::White);
	}
}
