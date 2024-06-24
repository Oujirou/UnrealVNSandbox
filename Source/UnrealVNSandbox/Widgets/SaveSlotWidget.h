// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "../Managers/SaveManager.h"

#include "SaveSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALVNSANDBOX_API USaveSlotWidget : public UUserWidget
{
	GENERATED_BODY()

	UTextBlock* m_tbTitle = nullptr;
	UTextBlock* m_tbDate = nullptr;
	UTextBlock* m_tbLine = nullptr;

	UImage* m_imgThumbnail = nullptr;

	SaveManager* m_pSaveManager;

	int m_nPosition;

	void RefreshSlot();
	
public:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetValues(UTextBlock* Title, UTextBlock* Date, UTextBlock* Line, UImage* Image);

	void SetSlotInfo(int position, SaveManager* saveManager);
};
