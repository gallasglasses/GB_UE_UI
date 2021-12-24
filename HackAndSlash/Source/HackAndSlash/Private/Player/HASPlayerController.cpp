// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/HASPlayerController.h"
#include "UI/HASGameHUD.h"

DEFINE_LOG_CATEGORY_STATIC(ControllerLog, All, All);

AHASPlayerController::AHASPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AHASPlayerController::BeginPlay()
{
	SetInputMode(FInputModeGameOnly());

	bEnableClickEvents = true;
}

void AHASPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (InputComponent)
	{
		InputComponent->BindKey(EKeys::LeftMouseButton, IE_Released, this, &ThisClass::OnLeftMouseButtonUp);
		InputComponent->BindKey(EKeys::RightMouseButton, IE_Released, this, &ThisClass::OnRightMouseButtonUp);
	}
}

void AHASPlayerController::OnLeftMouseButtonUp()
{
	OnMouseButtonUp.Broadcast();
}

void AHASPlayerController::OnRightMouseButtonUp()
{
	OnMouseButtonUp.Broadcast();
}

void AHASPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn)
	{
		return;
	}
	
	if (AHASGameHUD* GameHUD = GetGameHUD())
	{
		FVector CurrentPlayerPosition = PlayerPawn->GetActorLocation();
		//UE_LOG(ControllerLog, Display, TEXT("Pos X %f, Y %f "), CurrentPlayerPosition.X, CurrentPlayerPosition.Y);

		FVector2D PlayerPosition(CurrentPlayerPosition.X, CurrentPlayerPosition.Y);
		GameHUD->SetPlayerHUDPosition(PlayerPosition);
	}
	
}

AHASGameHUD* AHASPlayerController::GetGameHUD() const
{
	auto PlayerController = GetWorld()->GetFirstPlayerController();

	return Cast<AHASGameHUD>(PlayerController->GetHUD());
}