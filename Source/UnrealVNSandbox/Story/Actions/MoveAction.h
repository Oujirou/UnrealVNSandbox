// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/CanvasPanel.h"

#include "../BaseStoryAction.h"
#include "../../Managers/DataManager.h"

/**
 * 
 */
class UNREALVNSANDBOX_API MoveAction : public BaseStoryAction
{
	UCanvasPanelSlot* m_pCanvasPanelSlot;
	DataManager* m_pDataManager;

	FVector2d m_vStartPosition;
	FVector2d m_vEndPosition;

	FString m_strMoveTargetKey;

	float m_fDuration;
	float m_fTimeElapsed;
public:
	static const FString ACTION_KEY;

	MoveAction(FString text);
	~MoveAction();

	void Setup(DataManager* dataManager, UCanvasPanelSlot* canvasPanelSlot);

	FString GetMoveTargetKey() const { return m_strMoveTargetKey; }

	void Update(float deltaTime) override;

	bool IsComplete() override;

	void Skip() override;

	FString GetActionMapKey() const override;
};
