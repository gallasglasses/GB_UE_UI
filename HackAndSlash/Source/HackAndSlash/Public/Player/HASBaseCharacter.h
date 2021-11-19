// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HASBaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UHASHealthComponent;
class UTextRenderComponent;
class UAnimMontage;

UCLASS()
class HACKANDSLASH_API AHASBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHASBaseCharacter(const FObjectInitializer& ObjInit);

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UHASHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UTextRenderComponent* HealthTextComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* DeathAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	FVector2D LandedDamageVelocity = FVector2D(900.0f, 1200.0f);

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	FVector2D LandedDamage = FVector2D(10.0f, 100.0f);

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float LifeSpanOnDeath = 5.0f;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool IsRunning() const;
	
	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetMovementDirection() const;

private:

	UFUNCTION()
		void OnGroundLanded(const FHitResult& Hit);

	void MoveForward(float Amount);
	void MoveRight(float Amount);
	void OnStartRunning();
	void OnStopRunning();
	void OnDeath();
	void OnHealthChanged(float Health);

	bool bWantsToRun = false;
	bool bIsMovingForward = false;
};
