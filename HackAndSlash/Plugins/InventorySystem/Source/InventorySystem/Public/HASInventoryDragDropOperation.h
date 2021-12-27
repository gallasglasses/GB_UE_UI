#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "HASInventoryCellWidget.h"
#include "HASInventoryDragDropOperation.generated.h"

UCLASS()
class INVENTORYSYSTEM_API UHASInventoryDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()

public:

	UPROPERTY()
		UHASInventoryCellWidget* DragVisualWidget;
};