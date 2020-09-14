// Copyright 2020. Team slow, All right reserved.
#include "UI/Widget/SlowStageSelectsWidget.h"
#include "UI/Control/SlowTextButton.h"
#include "Manager/SceneManager.h"


void USlowStageSelectsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Stage1_1->Clicked.AddUObject(this, &USlowStageSelectsWidget::OnClicked_Stage1_1);
	Button_Stage1_2->Clicked.AddUObject(this, &USlowStageSelectsWidget::OnClicked_Stage1_2);
	Button_Stage1_3->Clicked.AddUObject(this, &USlowStageSelectsWidget::OnClicked_Stage1_3);
	Button_Cancel->Clicked.AddUObject(this, &USlowStageSelectsWidget::OnClicked_Cancel);
}

void USlowStageSelectsWidget::OnClicked_Stage1_1(USlowTextButton* InClickedButton)
{
	USceneManager::LoadScene(TEXT("Gameplay"));
	Disposing.Broadcast();
}

void USlowStageSelectsWidget::OnClicked_Stage1_2(USlowTextButton* InClickedButton)
{
	Disposing.Broadcast();
}

void USlowStageSelectsWidget::OnClicked_Stage1_3(USlowTextButton* InClickedButton)
{
	Disposing.Broadcast();
}

void USlowStageSelectsWidget::OnClicked_Cancel(USlowTextButton* InClickedButton)
{
	Disposing.Broadcast();
}