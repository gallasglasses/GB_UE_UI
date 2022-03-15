// Fill out your copyright notice in the Description page of Project Settings.


#include "MediaPlayerPlane.h"
#include "DesktopPlatformModule.h"
#include "IDesktopPlatform.h"
#include "MediaSoundComponent.h"
#include "MediaPlayer.h"
#include "FileMediaSource.h"
#include "Kismet/KismetRenderingLibrary.h"

AMediaPlayerPlane::AMediaPlayerPlane()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMediaPlayerPlane::BeginPlay()
{
	Super::BeginPlay();

	if (MediaPlayer)
	{
		FString Path;

		IDesktopPlatform* Platform = FDesktopPlatformModule::Get();
		if (Platform)
		{
			auto* ParentWindowHandle = FSlateApplication::Get().FindBestParentWindowHandleForDialogs(nullptr);
			const FString FileTypes =
				"All Files (*.PNG, *.JPG, *.MP4)|*.PNG;*.JPG;*.MP4|"
				"Video Files (*.MP4)|*.MP4|"
				"Image Files (*.PNG, *.JPG)|*.PNG, *.JPG";

			TArray<FString> OutFiles;
			Platform->OpenFileDialog(ParentWindowHandle, "Choose media", "", "", FileTypes, 0, OutFiles);

			if (OutFiles.Num() > 0)
			{
				Path = OutFiles[0];
			}

			UFileMediaSource* MediaSource = NewObject<UFileMediaSource>();
			MediaSource->FilePath = Path;
			MediaPlayer->OpenSource(MediaSource);

			UMediaSoundComponent* SoundComponent = NewObject<UMediaSoundComponent>(this);
			SoundComponent->SetMediaPlayer(MediaPlayer);
			SoundComponent->RegisterComponent();
		}
	}
}

void AMediaPlayerPlane::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}