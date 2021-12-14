// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HASHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeathSignature);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHealthChangedSignature, float, float);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HACKANDSLASH_API UHASHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHASHealthComponent();

	FOnDeathSignature OnDeath;
	FOnHealthChangedSignature OnHealthChanged;

	UFUNCTION(BlueprintCallable, Category = "Health")
		bool IsDead() const;

	UFUNCTION(BlueprintCallable, Category = "Health")
		float GetHealthPercent() const;

	float GetHealth() const;

	bool TryToAddHealth(float HealthAmount);
	bool IsHealthFull() const;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
		float MaxHealth = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
		bool AutoHeal = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0.0", ClampMax = "10.0"), meta = (EditCondition = "AutoHeal"))
		float HealUpdateTime = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0.0", ClampMax = "10.0"), meta = (EditCondition = "AutoHeal"))
		float HealDelay = 3.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0.0", ClampMax = "10.0"), meta = (EditCondition = "AutoHeal"))
		float HealModifier = 5.0f;

	virtual void BeginPlay() override;

private:

	FTimerHandle HealTimerHandle;

	UFUNCTION()
		void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	void HealUpdate();
	void SetHealth(float NewHealth);

	float Health = 0.0f;
};
