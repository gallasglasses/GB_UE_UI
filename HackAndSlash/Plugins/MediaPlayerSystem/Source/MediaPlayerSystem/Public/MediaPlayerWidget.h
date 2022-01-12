// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MediaPlayerWidget.generated.h"

class UButton;
class UImage;
class UMediaPlayer;
class UMaterialInterface;
class UMaterialInstanceDynamic;

UCLASS()
class MEDIAPLAYERSYSTEM_API UMediaPlayerWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
		UButton* BrowseButton;

	UPROPERTY(meta = (BindWidget))
		UImage* MediaImage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UMediaPlayer* MediaPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UMaterialInterface* MediaPlayerMaterial;

	virtual void NativeConstruct() override;

private:
	UFUNCTION()
		void OnBrowseClicked();

	UFUNCTION()
		void OnMediaOpened(FString OpenedUrl);

	UPROPERTY()
		UMaterialInstanceDynamic* MediaPlayerMaterialInstance;

};
