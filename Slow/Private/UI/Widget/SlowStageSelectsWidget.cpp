// Copyright 2020. Team slow, All right reserved.

#include "UI/Widget/SlowStageSelectsWidget.h"

#include "UI/Control/SlowTextButton.h"
#include "Manager/SceneManager.h"
#include "Scene/GameplayLobbyScene.h"
#include "Scene/GameplayStage01Scene.h"

void USlowStageSelectsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Stage1_1->Clicked.AddUObject(this, &USlowStageSelectsWidget::OnClicked_Stage1_1);
	Button_Stage1_2->Clicked.AddUObject(this, &USlowStageSelectsWidget::OnClicked_Stage1_2);
	Button_Stage1_3->Clicked.AddUObject(this, &USlowStageSelectsWidget::OnClicked_Stage1_3);
	Button_Cancel->Clicked.AddUObject(this, &USlowStageSelectsWidget::OnClicked_Cancel);
}

USceneBase* USlowStageSelectsWidget::GetNextScene() const
{
	return NextScene;
}

void USlowStageSelectsWidget::OnClicked_Stage1_1(USlowTextButton* InClickedButton)
{
	NextScene = NewObject<UGameplayLobbyScene>();
	Disposing.Broadcast();
}

void USlowStageSelectsWidget::OnClicked_Stage1_2(USlowTextButton* InClickedButton)
{
	NextScene = NewObject<UGameplayStage01Scene>();
	Disposing.Broadcast();
}

void USlowStageSelectsWidget::OnClicked_Stage1_3(USlowTextButton* InClickedButton)
{

}

void USlowStageSelectsWidget::OnClicked_Cancel(USlowTextButton* InClickedButton)
{
	NextScene = nullptr;
	Disposing.Broadcast();
}	