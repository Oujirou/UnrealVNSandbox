// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/TextBlock.h"
#include "Engine/UserInterfaceSettings.h"

#include "Kismet/GameplayStatics.h"
#include "Engine.h"

#include "../../Config/Options.h"
#include "../BaseStoryAction.h"
#include "../../Managers/DataManager.h"

/**
 * 
 */
class UNREALVNSANDBOX_API DialogAction : public BaseStoryAction
{
	struct TextState
	{
		// List of FStrings to display
		TArray<FString> TextList;
		// Current index of TextList
		int CurrentIndex = 0;
		int CurrentLetter = -1;

		float LettersPerSecond = 0.2;
		float TimeSinceLastLetter = 0.0;

		FString CurrentLine = "";

		bool Complete = true;
	};
	TextState m_TextState;

	UTextBlock* m_pAttributeTextBlock;
	UTextBlock* m_pDialogTextBlock;

	UAudioComponent* m_pDialogSound;
	FString m_strDialogSoundUrl;

	DataManager* m_pDataManager;

	FString m_strChapterKey;
	FString m_strAttributeKey;
	FString m_strTextKey;

public:
	static const FString ACTION_KEY;

	DialogAction(FString text);
	~DialogAction();

	FString GetAttributeKey() const { return m_strAttributeKey; }

	void Setup(FString chapterKey, DataManager* dataManager, UTextBlock* attributeTextBlock, UTextBlock* dialogTextBlock, UWorld* world);

	void Update(float deltaTime) override;

	bool IsComplete() override;

	void Skip() override;

	FString GetActionMapKey() const override;
};
