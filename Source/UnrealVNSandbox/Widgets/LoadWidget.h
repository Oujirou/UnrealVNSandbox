// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "../Managers/SaveManager.h"
#include "SaveSlotWidget.h"

#include "LoadWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALVNSANDBOX_API ULoadWidget : public UUserWidget
{
	GENERATED_BODY()
	
	SaveManager* m_pSaveManager;

	TStaticArray<USaveSlotWidget*, 6> m_vSaveSlots;
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	UUserWidget* MainMenuWidget;

	UFUNCTION(BlueprintCallable, Category="Setup")
	void Setup();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetSaveSlot(int saveSlot, USaveSlotWidget* widget);

	UFUNCTION(BlueprintCallable, Category = "Load")
	FString GetDisplayNameBySlot(int saveSlot);

	UFUNCTION(BlueprintCallable, Category = "Load")
	bool HasSaveDataBySlot(int saveSlot);

	UFUNCTION(BlueprintCallable, Category = "Load")
	FString GetChapterKeyBySlot(int saveSlot);

	UFUNCTION(BlueprintCallable, Category = "Load")
	FString GetRawActionTextBySlot(int saveSlot);
};
