// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "../Managers/DataManager.h"

/**
 * 
 */
class UNREALVNSANDBOX_API StorySceneContext
{
	DataManager* m_pDataManager;

	StoryChapterData* m_pCurrentChapterData;
	TArray<FString> m_vCurrentActions;
	int m_iCurrentActionIndex = 0;

	FString m_strCurrentChapterKey;
	FString m_strCurrentBackgroundTexture;
	FString m_strCurrentCharacterName;
	FString m_strCurrentCharacterDialog;

	FString m_strCurrentRawActionText;

public:
	StorySceneContext();
	~StorySceneContext();

	void SetDataManager(DataManager* dataManager) { m_pDataManager = dataManager; }

	FString GetCurrentChapterKey() const { return m_strCurrentChapterKey; }
	void SetCurrentChapterKey(FString chapterKey) { m_strCurrentChapterKey = chapterKey; }
	
	FString GetCurrentBackgroundTexture() const { return m_strCurrentBackgroundTexture; }
	void SetCurrentBackgroundTexture(FString backgroundTexture) { m_strCurrentBackgroundTexture = backgroundTexture; }
	
	FString GetCurrentCharacterName() const { return m_strCurrentCharacterName; }
	void SetCurrentCharacterName(FString characterName) { m_strCurrentCharacterName = characterName; }
	
	FString GetCurrentCharacterDialog() const { return m_strCurrentCharacterDialog; }
	void SetCurrentCharacterDialog(FString characterDialog) { m_strCurrentCharacterDialog = characterDialog; }
	
	void SetCurrentRawActionText(FString rawActionText) { m_strCurrentRawActionText = rawActionText; }

	void OnTick();

	bool IsActionDone();

	void ExecuteAction();

	void ResolveState();
};
