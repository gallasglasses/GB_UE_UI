// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DraggableItem.generated.h"

class UTextBlock;

UCLASS()
class HACKANDSLASH_API UDraggableItem : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* TextDraggableItem;

	UPROPERTY(EditAnywhere)
	FString NameDraggableItem;
	
	virtual void NativePreConstruct() override;

	virtual FReply NativeOnMouseButtonDown( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent ) override;

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& Operation) override;

	virtual bool NativeOnDragOver( const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation ) override;

	virtual bool NativeOnDrop( const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation ) override;

	UFUNCTION()
	void RestoreVisuals(UDragDropOperation* Operation);
};
