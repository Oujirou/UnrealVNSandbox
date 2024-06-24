// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/Image.h"
#include "Components/CanvasPanel.h"

#include "../BaseStoryAction.h"
#include "../../Managers/DataManager.h"

/**
 * 
 */
class UNREALVNSANDBOX_API CharacterActions : public BaseStoryAction
{
	DataManager* m_pDataManager;

	UCanvasPanel* m_pCanvasPanel;
	UImage* m_pCharacterImage;

	FString actionKeyOverride = "";

	FVector2D m_vPosition;
public:
	static const FString ACTION_KEY;

	CharacterActions(FString text);
	~CharacterActions();

	void Setup(DataManager* dataManager, UCanvasPanel* canvasPanel, FVector2D position, int32 zOrder);

	void UpdateImage(FString characterKey, FString textureKey);

	void Update(float deltaTime) override;

	bool IsComplete() override;

	void Skip() override;

	UCanvasPanelSlot* GetCanvasPanelSlot() const override;

	FString GetActionMapKey() const override;
};
