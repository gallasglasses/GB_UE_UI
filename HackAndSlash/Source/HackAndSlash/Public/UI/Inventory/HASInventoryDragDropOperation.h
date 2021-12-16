#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "UI/Inventory/HASInventoryCellWidget.h"
#include "HASInventoryDragDropOperation.generated.h"

//class UHASInventoryCellWidget;

UCLASS()
class HACKANDSLASH_API UHASInventoryDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()

public:

	UPROPERTY()
		UHASInventoryCellWidget* SourceCell;
};
