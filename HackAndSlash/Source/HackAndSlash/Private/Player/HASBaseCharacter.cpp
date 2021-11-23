// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/HASBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "Components/HASCharacterMovementComponent.h"
#include "Components/HASHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Controller.h"

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
	SpringArm->SocketOffset = FVector(0.0f, 0.0f, 100.0f);
	SpringArm->SetRelativeRotation(FRotator(0.0f, -15.0f, 0.0f));

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArm);

	HealthComponent = CreateDefaultSubobject<UHASHealthComponent>("HealthComponent");

	HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
	HealthTextComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AHASBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	check(HealthComponent);
	check(HealthTextComponent);
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
}

bool AHASBaseCharacter::IsRunning() const
{
	return bWantsToRun && bIsMovingForward && !GetVelocity().IsZero();
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
}

void AHASBaseCharacter::OnHealthChanged(float Health, float HealthDelta)
{
	HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
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

