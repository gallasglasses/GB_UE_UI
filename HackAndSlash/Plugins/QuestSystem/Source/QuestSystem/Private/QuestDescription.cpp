// Fill out your copyright notice in the Description page of Project Settings.

#include "QuestDescription.h"
#include "Quest.h"
#include "ObjectiveWidget.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"

void UQuestDescription::Init(AQuest* Quest)
{
	if (Quest == nullptr)
	{
		return;
	}

	NameText->SetText(Quest->Name);
	DescriptionText->SetText(Quest->Description);

	if (ObjectiveWidgetClass)
	{
		ObjectivesList->ClearChildren();
		for (auto* Objective : Quest->GetObjectives())
		{
			auto* ObjectiveWidget = CreateWidget<UObjectiveWidget>(this, ObjectiveWidgetClass);
			ObjectiveWidget->Init(Objective);
			ObjectivesList->AddChild(ObjectiveWidget);
		}
	}
}
