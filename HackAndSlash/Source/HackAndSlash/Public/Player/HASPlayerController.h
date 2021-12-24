// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HASPlayerController.generated.h"

class AHASGameHUD;

UCLASS()
class HACKANDSLASH_API AHASPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AHASPlayerController();

	FSimpleMulticastDelegate OnMouseButtonUp;

	virtual void Tick(float DeltaSeconds) override;
	
	AHASGameHUD* GetGameHUD() const;
protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	void OnLeftMouseButtonUp();
	void OnRightMouseButtonUp();
};
