// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "../BaseStoryAction.h"
#include "../../Managers/DataManager.h"
#include "../../Widgets/StoryBackground.h"

/**
 * 
 */
class UNREALVNSANDBOX_API BackgroundAction : public BaseStoryAction
{
	UStoryBackground* m_pBackgroundA;
	UStoryBackground* m_pBackgroundB;

	DataManager* m_pDataManager;

	FString m_strEnvironmentKey;
	FString m_strBackgroundKey;
public:
	static const FString ACTION_KEY;

	BackgroundAction(FString text);
	~BackgroundAction();

	void Setup(DataManager* dataManager, UStoryBackground* attributeTextBlock, UStoryBackground* dialogTextBlock);

	void UpdateImage(FString rawText, bool setToActive);

	void Animate();

	void Update(float deltaTime) override;

	bool IsComplete() override;

	void Skip() override;

	FString GetActionMapKey() const override;
};
