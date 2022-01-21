// Fill out your copyright notice in the Description page of Project Settings.

#include "QuestSystemCharacter.h"
#include "Quest.h"
#include "QuestListComponent.h"
#include "QuestList.h"
#include "QuestDialog.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

AQuestSystemCharacter::AQuestSystemCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	QuestListComponent = CreateDefaultSubobject<UQuestListComponent>(TEXT("QuestListComponent"));

	//FAttachmentTransformRules EquipAttachmentRules(EAttachmentRule::KeepRelative, false);

	NewQuestStatus = CreateDefaultSubobject<UStaticMeshComponent>("NewQuestStatus");
	NewQuestStatus->SetupAttachment(GetRootComponent());
	//NewQuestStatus->AttachToComponent(GetMesh(), EquipAttachmentRules, "QuestStatus");
	//NewQuestStatus->SetHiddenInGame(true);

	AcceptedQuestStatus = CreateDefaultSubobject<UStaticMeshComponent>("AcceptedQuestStatus");
	AcceptedQuestStatus->SetupAttachment(GetRootComponent());
	//AcceptedQuestStatus->AttachToComponent(GetMesh(), EquipAttachmentRules, "QuestStatus");
	//AcceptedQuestStatus->SetHiddenInGame(true);

	CompletedQuestStatus = CreateDefaultSubobject<UStaticMeshComponent>("CompletedQuestStatus");
	CompletedQuestStatus->SetupAttachment(GetRootComponent());
	//CompletedQuestStatus->AttachToComponent(GetMesh(), EquipAttachmentRules, "QuestStatus");
	//CompletedQuestStatus->SetHiddenInGame(true);
}

void AQuestSystemCharacter::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> AttachedActors;
	GetAttachedActors(AttachedActors);

	for (auto& Actor : AttachedActors)
	{
		AQuest* CheckedQuest = Cast<AQuest>(Actor);
		if (CheckedQuest == nullptr)
		{
			continue;
		}
		else
		{
			CheckedQuest->OnStatusChanged.AddUObject(this, &AQuestSystemCharacter::AssignedStatusQuest);
		}
	}

}

void AQuestSystemCharacter::AssignedStatusQuest(AQuest* CurrentQuest)
{
	if (!CurrentQuest->bIsTaken && !CurrentQuest->IsCompleted())
	{
		NewQuestStatus->SetHiddenInGame(false);
		AcceptedQuestStatus->SetHiddenInGame(true); 
		CompletedQuestStatus->SetHiddenInGame(true);
	}
	else if (CurrentQuest->bIsTaken && !CurrentQuest->IsCompleted())
	{
		NewQuestStatus->SetHiddenInGame(true);
		AcceptedQuestStatus->SetHiddenInGame(false);
		CompletedQuestStatus->SetHiddenInGame(true);
	}
	else if (CurrentQuest->IsCompleted())
	{
		NewQuestStatus->SetHiddenInGame(true);
		AcceptedQuestStatus->SetHiddenInGame(true);
		CompletedQuestStatus->SetHiddenInGame(false);
	}
	else
	{
		NewQuestStatus->SetHiddenInGame(true);
		AcceptedQuestStatus->SetHiddenInGame(true);
		CompletedQuestStatus->SetHiddenInGame(true);
	}
}



void AQuestSystemCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AQuestSystemCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AQuestSystemCharacter::Interact_Implementation(AActor* InteractInstigator)
{
	if (InteractInstigator == nullptr)
	{
		return;
	}

	UActorComponent* ActorQuestListComp = InteractInstigator->GetComponentByClass(UQuestListComponent::StaticClass());

	if (ActorQuestListComp)
	{
		UQuestListComponent* ActorQuestList = Cast<UQuestListComponent>(ActorQuestListComp);

		UE_LOG(LogTemp, Display, TEXT("Interact_Implementation start"));

		TArray<AActor*> AttachedActors;
		GetAttachedActors(AttachedActors);

		bool bHadQuestsAvailable = false;

		for (auto& Actor : AttachedActors)
		{
			AQuest* Quest = Cast<AQuest>(Actor);
			if (Quest == nullptr)
			{
				continue;
			}

			if (Quest->bIsTaken || (Quest->PreviousQuest && !Quest->PreviousQuest->IsCompleted()))
			{
				continue;
			}

			if (QuestDialogClass)
			{
				UQuestDialog* QuestDialog = CreateWidget<UQuestDialog>(GetWorld(), QuestDialogClass);
				UE_LOG(LogTemp, Display, TEXT("QuestDialog start"));

				QuestDialog->Init(Quest);
				QuestDialog->OnQuestAccepted.BindUObject(ActorQuestList, &UQuestListComponent::AddQuest, Quest);
				QuestDialog->OnDialogExit.BindLambda([this, InteractInstigator]()
					{
						NotifyInteractionFinished(this, InteractInstigator);
					});
				QuestDialog->AddToViewport();
			}
			bHadQuestsAvailable = true;
		}
		if (!bHadQuestsAvailable)
		{
			NotifyInteractionFinished(this, InteractInstigator);
		}
	}
	

	
}