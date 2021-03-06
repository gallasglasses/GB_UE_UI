// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/HASBaseCharacter.h"
#include "Animations/HASDealDamageAnimNotifyState.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/HASCharacterMovementComponent.h"
#include "Components/HASHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "UI/HASHealthBarWidget.h"
#include "UI/HASGameHUD.h"
#include "HASInventoryComponent.h"
#include "HASEquipInventoryComponent.h"
#include "HASInventoryManagerComponent.h"
#include "HASInventoryData.h"
#include "InteractionComponent.h"
#include "CollectionComponent.h"
#include "QuestListComponent.h"
#include "QuestList.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

DEFINE_LOG_CATEGORY_STATIC(BaseCharacterLog, All, All);

AHASBaseCharacter::AHASBaseCharacter(const FObjectInitializer& ObjInit):
	Super(ObjInit.SetDefaultSubobjectClass<UHASCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(GetRootComponent());
	//SpringArm->bDoCollisionTest = false;
	//SpringArm->bInheritPitch = false;
	//SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->SocketOffset = FVector(0.0f, 100.0f, 100.0f);
	SpringArm->SetRelativeRotation(FRotator(0.0f, -15.0f, 0.0f));

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArm);

	HealthComponent = CreateDefaultSubobject<UHASHealthComponent>("HealthComponent");

	HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
	HealthTextComponent->SetupAttachment(GetRootComponent());
	HealthTextComponent->bOwnerNoSee = true;
	HealthTextComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 160.0f));
	HealthTextComponent->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));

	HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("HealthWidgetComponent");
	HealthWidgetComponent->SetupAttachment(GetRootComponent());
	HealthWidgetComponent->bOwnerNoSee = true;
	//HealthWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	HealthWidgetComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 160.0f));
	HealthWidgetComponent->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));

	AxeTriggerHitComponent = CreateDefaultSubobject<UBoxComponent>("AxeTriggerHitComponent");
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::KeepRelative, false);
	AxeTriggerHitComponent->AttachToComponent(GetMesh(), AttachmentRules, "FX_Sweep");
	AxeTriggerHitComponent->OnComponentBeginOverlap.AddDynamic(this, &AHASBaseCharacter::OnOverlapHit);
	AxeTriggerHitComponent->IgnoreActorWhenMoving(GetOwner(), true);

	FAttachmentTransformRules EquipAttachmentRules(EAttachmentRule::KeepRelative, false);

	HeadEquipComponent = CreateDefaultSubobject<UStaticMeshComponent>("HeadEquipComponent");
	HeadEquipComponent->AttachToComponent(GetMesh(), EquipAttachmentRules, "ES_HeadEquip"); 
	
	RightHandWeaponryComponent = CreateDefaultSubobject<UStaticMeshComponent>("RightHandWeaponryComponent");
	RightHandWeaponryComponent->AttachToComponent(GetMesh(), EquipAttachmentRules, "ES_RightHandWeaponry");

	LeftHandWeaponryComponent = CreateDefaultSubobject<UStaticMeshComponent>("LeftHandWeaponryComponent");
	LeftHandWeaponryComponent->AttachToComponent(GetMesh(), EquipAttachmentRules, "ES_LeftHandWeaponry");

	InventoryComponent = CreateDefaultSubobject<UHASInventoryComponent>("InventoryComponent");
	EquipComponent = CreateDefaultSubobject<UHASEquipInventoryComponent>("EquipComponent");

	InventoryManagerComponent = CreateDefaultSubobject<UHASInventoryManagerComponent>("InventoryManagerComponent");

	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>("InteractionComponent");
	InteractionComponent->SetupAttachment(GetRootComponent());

	CollectionComponent = CreateDefaultSubobject<UCollectionComponent>("CollectionComponent");
	CollectionComponent->SetupAttachment(GetRootComponent());

	QuestListComponent = CreateDefaultSubobject<UQuestListComponent>(TEXT("QuestListComponent"));
}

// Called when the game starts or when spawned
void AHASBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	check(HealthComponent);
	check(HealthTextComponent);
	check(HealthWidgetComponent);
	check(InventoryComponent);
	check(EquipComponent);
	check(InventoryManagerComponent);
	check(GetCharacterMovement());
	check(GetMesh());


	OnHealthChanged(HealthComponent->GetHealth(), 0.0f);
	HealthComponent->OnDeath.AddUObject(this, &AHASBaseCharacter::OnDeath);
	HealthComponent->OnHealthChanged.AddUObject(this, &AHASBaseCharacter::OnHealthChanged);

	LandedDelegate.AddDynamic(this, &AHASBaseCharacter::OnGroundLanded);

	if (DefaultInventoryPack)
	{
		TArray<FInventorySlotInfo*> SlotInfo;
		DefaultInventoryPack->GetAllRows<FInventorySlotInfo>("", SlotInfo);
		for (int32 i = 0; i < SlotInfo.Num(); i++)
		{
			InventoryComponent->SetItem(i, *SlotInfo[i]);
		}
	}
// 	InventoryManagerComponent->Init(InventoryComponent);
// 	InventoryManagerComponent->InitEquip(EquipComponent);

	InventoryManagerComponent->OnItemUse.AddUObject(this, &AHASBaseCharacter::OnItemUsed);
}

void AHASBaseCharacter::EquipItem_Implementation(EEquipSlot Slot, FName ItemId)
{
	IHASEquipInterface::EquipItem_Implementation(Slot, ItemId);
	
	UStaticMeshComponent* EquipMeshItem = GetEquipComponent(Slot);
	if (EquipMeshItem)
	{
		FInventoryItemInfo* ItemInfoPtr = InventoryManagerComponent->GetItemData(ItemId);
		if (ItemInfoPtr)
		{
			EquipMeshItem->SetStaticMesh(ItemInfoPtr->Mesh.LoadSynchronous());

			WeaponDamageAmount += ItemInfoPtr->Damage;
			UE_LOG(BaseCharacterLog, Display, TEXT("Damage: %f"), WeaponDamageAmount);

			/*ArmorStat += ItemInfoPtr->Armor;
			IntelligenceStat += ItemInfoPtr->Intelligence;*/
		}
	}

}

void AHASBaseCharacter::UnequipItem_Implementation(EEquipSlot Slot, FName ItemId)
{
	IHASEquipInterface::UnequipItem_Implementation(Slot, ItemId);

	UStaticMeshComponent* EquipMeshItem = GetEquipComponent(Slot);
	if (EquipMeshItem)
	{
		EquipMeshItem->SetStaticMesh(nullptr);
		FInventoryItemInfo* ItemInfoPtr = InventoryManagerComponent->GetItemData(ItemId);
		if (ItemInfoPtr)
		{
			WeaponDamageAmount -= ItemInfoPtr->Damage;
			UE_LOG(BaseCharacterLog, Display, TEXT("Damage: %f"), WeaponDamageAmount);

			/*ArmorStat -= ItemInfoPtr->Armor;
			IntelligenceStat -= ItemInfoPtr->Intelligence;*/
		}
	}

}

void AHASBaseCharacter::OnItemUsed(FName ItemId)
{
	FInventoryItemInfo* ItemInfoPtr = InventoryManagerComponent->GetItemData(ItemId);
	if (ItemInfoPtr)
	{
		UE_LOG(BaseCharacterLog, Display, TEXT("Heal: %d"), ItemInfoPtr->Heal);
		HealthComponent->TryToAddHealth(ItemInfoPtr->Heal);
	}
}

UStaticMeshComponent* AHASBaseCharacter::GetEquipComponent(EEquipSlot Slot)
{
	FName EquipTag = "";

	switch (Slot)
	{
		case EEquipSlot::ES_None:
			break;
		case EEquipSlot::ES_RightHandWeaponry:
			EquipTag = "ES_RightHandWeaponry";
			break;
		case EEquipSlot::ES_LeftHandWeaponry:
			EquipTag = "ES_LeftHandWeaponry";
			break;
		case EEquipSlot::ES_AddRightHandWeaponry:
			EquipTag = "ES_AddRightHandWeaponry";
			break;
		case EEquipSlot::ES_AddLeftHandWeaponry:
			EquipTag = "ES_AddLeftHandWeaponry";
			break;
		case EEquipSlot::ES_HeadEquip:
			EquipTag = "ES_HeadEquip";
			break;
		case EEquipSlot::ES_ArmsEquip:
			EquipTag = "ES_ArmsEquip";
			break;
		case EEquipSlot::ES_BodyEquip:
			EquipTag = "ES_BodyEquip";
			break;
		case EEquipSlot::ES_LegsEquip:
			EquipTag = "ES_LegsEquip";
			break;
		case EEquipSlot::ES_FeetEquip:
			EquipTag = "ES_FeetEquip";
			break;
		default:
			break;
	}
	TArray<UActorComponent*> Components = GetComponentsByTag(UStaticMeshComponent::StaticClass(), EquipTag);
	return Components.Num() > 0 ? Cast<UStaticMeshComponent>(Components[0]) : nullptr;
}

void AHASBaseCharacter::ToggleQuestListVisibility()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (QuestList)
	{
		QuestList->RemoveFromParent();
		QuestList = nullptr;
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(PC);
	}
	else
	{
		if (QuestListClass)
		{
			QuestList = CreateWidget<UQuestList>(GetWorld(), QuestListClass);
			QuestList->Init(QuestListComponent);
			QuestList->AddToViewport();
			UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(PC);
			PC->SetShowMouseCursor(true);
		}
	}
	
}

// Called every frame
void AHASBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*FVector CurrentPlayerPosition;
	if (!HealthComponent->IsDead() && Controller->GetStateName() != NAME_Spectating)
	{
		CurrentPlayerPosition = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

		if (AHASGameHUD* GameHUD = GetGameHUD())
		{
			UE_LOG(BaseCharacterLog, Display, TEXT("Pos X %f, Y %f "), CurrentPlayerPosition.X, CurrentPlayerPosition.Y);

			FVector2D PlayerPosition(CurrentPlayerPosition.X, CurrentPlayerPosition.Y);
			GameHUD->SetPlayerHUDPosition(PlayerPosition);
		}
	}*/
	
}

// Called to bind functionality to input
void AHASBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AHASBaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AHASBaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &AHASBaseCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &AHASBaseCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AHASBaseCharacter::Jump);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AHASBaseCharacter::OnStartRunning);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &AHASBaseCharacter::OnStopRunning);
	PlayerInputComponent->BindAction("MeleeAttack", IE_Pressed, this, &AHASBaseCharacter::MeleeAttack);
	PlayerInputComponent->BindAction("OpenInventory", IE_Pressed, this, &AHASBaseCharacter::OpenInventory);
}

bool AHASBaseCharacter::IsRunning() const
{
	return bWantsToRun && bIsMovingForward && !GetVelocity().IsZero();
}

bool AHASBaseCharacter::IsAttacking() const
{
	return bIsAttacking;
}

float AHASBaseCharacter::GetMovementDirection() const
{
	if (GetVelocity().IsZero())
	{
		return 0.0f;
	}
	const auto VelocityNormal = GetVelocity().GetSafeNormal();
	const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
	const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
	const auto Degrees = FMath::RadiansToDegrees(AngleBetween);
	return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}

AHASGameHUD* AHASBaseCharacter::GetGameHUD() const
{
	auto PlayerController = GetWorld()->GetFirstPlayerController();

	return Cast<AHASGameHUD>(PlayerController->GetHUD());
}

FCharacterSaveData AHASBaseCharacter::GetCharacterData()
{
	SaveData.ActorName = GetFName();
	SaveData.Transform = GetActorTransform();
	SaveData.Health = HealthComponent->GetHealth();
	SaveData.InventoryItems = InventoryComponent->GetItems();
	SaveData.EquipItems = EquipComponent->GetItems();
	return SaveData;
}

void AHASBaseCharacter::SetCharacterData(FCharacterSaveData SavedData)
{
	if (SavedData.ActorName == GetFName())
	{
		SetActorRelativeTransform(SavedData.Transform);
		auto PlayerController = GetWorld()->GetFirstPlayerController();
		PlayerController->SetInitialLocationAndRotation(SavedData.Transform.GetLocation(), SavedData.Transform.GetRotation().Rotator());
		
		OnLoadingGame.Broadcast(SavedData.Health);

		InventoryComponent->ClearItems();
		for (auto InventoryItem : SavedData.InventoryItems)
		{
			InventoryComponent->SetItem(InventoryItem.Key, InventoryItem.Value);
		}

		EquipComponent->ClearItems();
		for (auto EquipItem : SavedData.EquipItems)
		{
			EquipComponent->SetItem(EquipItem.Key, EquipItem.Value);
		}
	}
}

void AHASBaseCharacter::MoveForward(float Amount)
{
	bIsMovingForward = Amount > 0.0f;
	AddMovementInput(GetActorForwardVector(), Amount);
}

void AHASBaseCharacter::MoveRight(float Amount)
{
	if (Amount == 0.0f)
	{
		return;
	}
	AddMovementInput(GetActorRightVector(), Amount);
}

void AHASBaseCharacter::OnStartRunning()
{
	bWantsToRun = true;
}

void AHASBaseCharacter::OnStopRunning()
{
	bWantsToRun = false;
}

void AHASBaseCharacter::OnDeath()
{
	UE_LOG(BaseCharacterLog, Display, TEXT("%s, you are dead!"), *GetName());
	PlayAnimMontage(DeathAnimMontage);
	GetCharacterMovement()->DisableMovement();
	SetLifeSpan(LifeSpanOnDeath);

	if (Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
}

void AHASBaseCharacter::OnHealthChanged(float Health, float HealthDelta)
{
	HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
	const auto HealthBarWidget = Cast<UHASHealthBarWidget>(HealthWidgetComponent->GetUserWidgetObject());
	if (!HealthBarWidget)
	{
		return;
	}
	HealthBarWidget->SetHealthPercent(HealthComponent->GetHealthPercent());
	HealthBarWidget->SetScaleDamage(HealthDelta);
}

void AHASBaseCharacter::MeleeAttack()
{
	if (IsAttacking())
	{
		return;
	}
	OnStartAttacking();
	UE_LOG(BaseCharacterLog, Display, TEXT("SLASH!"));
	GetWorld()->GetTimerManager().SetTimer(MeleeAttackTimerHandle, this, &AHASBaseCharacter::OnStopAttacking, MeleeAttackAnimMontage->CalculateSequenceLength(), false);
}

void AHASBaseCharacter::OpenInventory()
{
	/*AHASGameHUD* HUD = Cast<AHASGameHUD>(GetGameHUD());
	if (!HUD)
	{
		return;
	}
	UUserWidget* Inventory = Cast<UUserWidget>(HUD->InventoryTest);
	if (bIsInventoryOpen)
	{
		Inventory->SetVisibility(ESlateVisibility::Hidden);
		bIsInventoryOpen = false;
	}
	else
	{
		Inventory->SetVisibility(ESlateVisibility::Visible);
		bIsInventoryOpen = true;
	}*/

	if (bIsInventoryVisible && bIsEquipVisible)
	{
		InventoryManagerComponent->RemoveInventory();
		InventoryManagerComponent->RemoveEquip();
		bIsInventoryVisible = false;
		bIsEquipVisible = false;
	}
	else
	{
		InventoryManagerComponent->Init(InventoryComponent);
		InventoryManagerComponent->InitEquip(EquipComponent);
		bIsInventoryVisible = true;
		bIsEquipVisible = true;
	}
}

void AHASBaseCharacter::OnStartAttacking()
{
	bIsAttacking = true;
	if (bIsAttacking)
	{
		UE_LOG(BaseCharacterLog, Display, TEXT("1 Attack"));
		UE_LOG(BaseCharacterLog, Display, TEXT("time : %f"), MeleeAttackAnimMontage->CalculateSequenceLength());
	}
	else
	{
		UE_LOG(BaseCharacterLog, Display, TEXT("1 Not Attack"));
	}
	PlayAnimMontage(MeleeAttackAnimMontage);
	//InitAnimations();
}

void AHASBaseCharacter::OnStopAttacking()
{
	bIsAttacking = false; 
	bIsDamageDone = false;
	if (bIsAttacking)
	{
		UE_LOG(BaseCharacterLog, Display, TEXT("2 Attack"));
	}
	else
	{
		UE_LOG(BaseCharacterLog, Display, TEXT("2 Not Attack"));
	}
	GetWorld()->GetTimerManager().ClearTimer(MeleeAttackTimerHandle);
}

//void AHASBaseCharacter::InitAnimations()
//{
//	if (!MeleeAttackAnimMontage)
//	{
//		return;
//	}
//	const auto NotifyEvents = MeleeAttackAnimMontage->Notifies;
//	for (auto NotifyEvent : NotifyEvents)
//	{
//		UHASDealDamageAnimNotifyState* DealDamageNotify = Cast<UHASDealDamageAnimNotifyState>(NotifyEvent.NotifyStateClass);
//		if (DealDamageNotify)
//		{
//			DealDamageNotify->OnNotifiedStateSignature.AddUObject(this, &AHASBaseCharacter::OnOverlapHit);
//			break;
//		}
//	}
//}

void AHASBaseCharacter::OnOverlapHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsAttacking())
	{
		const auto HitActor = SweepResult.GetActor();
		if (!HitActor)
		{
			return;
		}
		if (HitActor == this)
		{
			return;
		}
		UE_LOG(BaseCharacterLog, Display, TEXT("%s, you got damage"), *SweepResult.GetActor()->GetName());
		MakeDamage(SweepResult);
	}
}

void AHASBaseCharacter::MakeDamage(const FHitResult& HitResult)
{
	const auto HitActor = HitResult.GetActor();

	if (!bIsDamageDone)
	{
		HitActor->TakeDamage(WeaponDamageAmount, FDamageEvent{}, GetPlayerController(), this);
		bIsDamageDone = true;
	}
}

void AHASBaseCharacter::OnGroundLanded(const FHitResult& Hit)
{
	const auto FallVelocityZ = -GetVelocity().Z;
	UE_LOG(BaseCharacterLog, Display, TEXT("On landed: %f"), FallVelocityZ);

	if (FallVelocityZ < LandedDamageVelocity.X)
	{
		return;
	}

	const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocityZ);
	UE_LOG(BaseCharacterLog, Display, TEXT("FinalDamage: %f"), FinalDamage);
	TakeDamage(FinalDamage, FDamageEvent{}, nullptr, nullptr);
}

APlayerController* AHASBaseCharacter::GetPlayerController() const
{
	const auto Player = Cast<ACharacter>(GetOwner());
	if (!Player)
	{
		return nullptr;
	}
	return Player->GetController<APlayerController>();
}