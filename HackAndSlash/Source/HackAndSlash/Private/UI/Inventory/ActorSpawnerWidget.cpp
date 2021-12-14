// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/ActorSpawnerWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Player/HASPlayerController.h"

void UActorSpawnerWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (TextDraggedItem)
	{
		TextDraggedItem->SetText(FText::FromString(NameDraggedItem));
	}
}

void UActorSpawnerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (auto* MyController = Cast<AHASPlayerController>(PlayerController))
	{
		MyController->OnMouseButtonUp.AddUObject(this, &ThisClass::OnMouseButtonUp);
	}
}

void UActorSpawnerWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (SpawnedActor && PlayerController)
	{
		FVector WorldMousePosition;
		FVector WorldMouseDirection;

		PlayerController->DeprojectMousePositionToWorld(WorldMousePosition, WorldMouseDirection);

		FHitResult OutHit;
		const float Dist = 10000.f;

		FCollisionQueryParams Params = FCollisionQueryParams::DefaultQueryParam;
		Params.AddIgnoredActor(SpawnedActor);
		Params.AddIgnoredActor(PlayerController->GetPawn());

		GetWorld()->LineTraceSingleByChannel(OutHit, WorldMousePosition, WorldMousePosition + WorldMouseDirection * Dist, ECollisionChannel::ECC_WorldStatic, Params);

		if (OutHit.bBlockingHit)
		{
			SpawnedActor->SetActorLocation(OutHit.Location);
		}
	}
}

FReply UActorSpawnerWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		//FActorSpawnParameters ActorSpawnParameters;
		FVector SpawnLocation = PlayerController->GetPawn()->GetActorLocation();

		FVector WorldMousePosition;
		FVector WorldMouseDirection;

		PlayerController->DeprojectMousePositionToWorld(WorldMousePosition, WorldMouseDirection);

		const float Dist = 100.f;
		SpawnLocation = SpawnLocation + WorldMouseDirection * Dist;
		FTransform SpawnTransform(PlayerController->GetPawn()->GetActorRotation(), SpawnLocation, FVector(1.f));
		SpawnedActor = GetWorld()->SpawnActor<AActor>(SpawnerClass, SpawnTransform);
	}
	return FReply::Handled();
}

void UActorSpawnerWidget::OnMouseButtonUp()
{
	SpawnedActor = nullptr;
}
