// Fill out your copyright notice in the Description page of Project Settings.


#include "MediaPlayerWidget.h"
#include "DesktopPlatformModule.h"
#include "IDesktopPlatform.h"
#include "MediaSoundComponent.h"
#include "MediaPlayer.h"
#include "FileMediaSource.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Components/Image.h"
#include "Components/Button.h"

void UMediaPlayerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	MediaPlayerMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), MediaPlayerMaterial);

	if (BrowseButton)
	{
		BrowseButton->OnClicked.AddDynamic(this, &UMediaPlayerWidget::OnBrowseClicked);
	}

	if (MediaPlayer)
	{
		MediaPlayer->OnMediaOpened.AddDynamic(this, &UMediaPlayerWidget::OnMediaOpened);
	}
}

void UMediaPlayerWidget::OnBrowseClicked()
{
	if (MediaPlayer)
	{
		if (MediaPlayer->IsPlaying())
		{
			MediaPlayer->Pause();
		}

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
			if (Platform->OpenFileDialog(ParentWindowHandle, "Choose media", "", "", FileTypes, 0, OutFiles))
			{
				if (OutFiles.Num() > 0)
				{
					Path = OutFiles[0];
				}

				UFileMediaSource* MediaSource = NewObject<UFileMediaSource>();
				MediaSource->FilePath = Path;
				if (MediaPlayer->CanPlaySource(MediaSource))
				{
					MediaImage->SetBrushFromMaterial(MediaPlayerMaterialInstance);

					const auto Outer = GetWorld()->GetFirstPlayerController()->GetPawn();
					if (Outer)
					{
						UMediaSoundComponent* SoundComponent = NewObject<UMediaSoundComponent>(Outer);
						SoundComponent->SetMediaPlayer(MediaPlayer);
						SoundComponent->RegisterComponent();
					}

					MediaPlayer->OpenSource(MediaSource);
				}
				else
				{
					MediaPlayer->Close();
					FSlateBrush SlateBrush;
					UTexture2D* Texture = UKismetRenderingLibrary::ImportFileAsTexture2D(this, Path);
					SlateBrush.SetResourceObject(Texture);
					MediaImage->SetBrush(SlateBrush);
					MediaImage->SetBrushSize(FVector2D(Texture->GetSizeX(), Texture->GetSizeY()));
					UE_LOG(LogTemp, Display, TEXT("ImageDimensions X = %d Y = %d"), Texture->GetSizeX(), Texture->GetSizeY());
					MediaImage->SetVisibility(ESlateVisibility::Visible);
				}
			}
			if (MediaPlayer->IsPaused())
			{
				MediaPlayer->Play();
			}
		}
	}
}

void UMediaPlayerWidget::OnMediaOpened(FString OpenedUrl)
{
	const FVector2D MediaDimensions = MediaPlayer->GetVideoTrackDimensions(INDEX_NONE, INDEX_NONE);
	UE_LOG(LogTemp, Display, TEXT("MediaDimensions %s"), *MediaDimensions.ToString());
	if (MediaImage)
	{
		MediaImage->SetBrushSize(FVector2D(MediaDimensions.X, MediaDimensions.Y));
		MediaImage->SetVisibility(ESlateVisibility::Visible);
	}
}
