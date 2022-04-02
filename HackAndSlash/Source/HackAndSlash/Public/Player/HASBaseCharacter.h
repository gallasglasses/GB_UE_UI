// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HASEquipInterface.h"
#include "GameFramework/Character.h"
#include "SaveSystem/SaveData.h"
#include "HASBaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UHASHealthComponent;
class UTextRenderComponent;
class UAnimMontage;
class UBoxComponent;
class UWidgetComponent;
class AHASGameHUD;
class UHASInventoryComponent;
class UHASEquipInventoryComponent;
class UHASInventoryManagerComponent;
class UDataTable;
class UStaticMeshComponent;
class UInteractionComponent;
class UCollectionComponent;
class UQuestListComponent;
class UQuestList;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnLoadingGame, float /*HealthFromData*/);

UCLASS()
class HACKANDSLASH_API AHASBaseCharacter : public ACharacter, public IHASEquipInterface
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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UBoxComponent* AxeTriggerHitComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UWidgetComponent* HealthWidgetComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UHASInventoryComponent* InventoryComponent; 
		
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UHASEquipInventoryComponent* EquipComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UHASInventoryManagerComponent* InventoryManagerComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EquipComponents")
	UStaticMeshComponent* HeadEquipComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "WeaponryComponents")
	UStaticMeshComponent* RightHandWeaponryComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "WeaponryComponents")
	UStaticMeshComponent* LeftHandWeaponryComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UInteractionComponent* InteractionComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UCollectionComponent* CollectionComponent;

	UPROPERTY(EditDefaultsOnly)
	UQuestListComponent* QuestListComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* DeathAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* MeleeAttackAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* HitReactAnimMontage;

	UPROPERTY(EditAnywhere, Category = "InventoryPack")
	UDataTable* DefaultInventoryPack;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	FVector2D LandedDamageVelocity = FVector2D(900.0f, 1200.0f);

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	FVector2D LandedDamage = FVector2D(10.0f, 100.0f);

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float LifeSpanOnDeath = 5.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "WeaponDamage")
	float WeaponDamageAmount = 10.0f;

	FCharacterSaveData SaveData;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EquipItem_Implementation(EEquipSlot Slot, FName ItemId) override;

	virtual void UnequipItem_Implementation(EEquipSlot Slot, FName ItemId) override;

	void OnItemUsed(FName ItemId);

	UStaticMeshComponent* GetEquipComponent(EEquipSlot Slot);

	UFUNCTION(BlueprintCallable)
		void ToggleQuestListVisibility();

	UPROPERTY()
		UQuestList* QuestList;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<UQuestList> QuestListClass;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Serialize(FArchive& Ar) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool IsRunning() const;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool IsAttacking() const;
	
	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetMovementDirection() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
		AHASGameHUD* GetGameHUD() const;

	UFUNCTION(BlueprintCallable, Category = "SaveSystem")
		FCharacterSaveData GetCharacterData();

	UFUNCTION(BlueprintCallable, Category = "SaveSystem")
		void SetCharacterData(FCharacterSaveData SaveData);

	FOnLoadingGame OnLoadingGame;

private:
	FTimerHandle MeleeAttackTimerHandle;
	APlayerController* GetPlayerController() const;

	UFUNCTION()
		void OnGroundLanded(const FHitResult& Hit);
	UFUNCTION()
		void OnOverlapHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	void MoveForward(float Amount);
	void MoveRight(float Amount);
	void OnStartRunning();
	void OnStopRunning();
	void OnDeath();
	void OnHealthChanged(float Health, float HealthDelta);
	void MeleeAttack();
	void OpenInventory();
	void OnStartAttacking();
	void OnStopAttacking();
	//void InitAnimations();
	
	//void OnDealDamage();
	void MakeDamage(const FHitResult& HitResult);

	bool bWantsToRun = false;
	bool bIsAttacking = false;
	bool bIsMovingForward = false;
	bool bIsDamageDone = false;
	bool bIsInventoryVisible = false;
	bool bIsEquipVisible = false;
};
