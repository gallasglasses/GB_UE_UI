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
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "UI/HASHealthBarWidget.h"
#include "UI/HASGameHUD.h"

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
}

// Called when the game starts or when spawned
void AHASBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	check(HealthComponent);
	check(HealthTextComponent);
	check(HealthWidgetComponent);
	check(GetCharacterMovement());
	check(GetMesh());

	OnHealthChanged(HealthComponent->GetHealth(), 0.0f);
	HealthComponent->OnDeath.AddUObject(this, &AHASBaseCharacter::OnDeath);
	HealthComponent->OnHealthChanged.AddUObject(this, &AHASBaseCharacter::OnHealthChanged);

	LandedDelegate.AddDynamic(this, &AHASBaseCharacter::OnGroundLanded);
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