// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Data/StoryChapterData.h"
#include "../Data/StoryCharacterData.h"
#include "../Data/StoryEnvironmentData.h"
#include "../Data/StoryEntrypointData.h"
#include "../Data/StoryPositionData.h"

/**
 * 
 */
class UNREALVNSANDBOX_API DataManager
{
	TMap<FString, StoryChapterData*> m_mChapterData;
	TMap<FString, StoryCharacterData*> m_mCharacterData;
	TMap<FString, StoryEnvironmentData*> m_mEnvironmentData;

	StoryEntrypointData* m_pEntrypointData = nullptr;
	StoryPositionData* m_pPositionData = nullptr;

	bool m_bInitialized = false;

	void ListFilesInDirectory(const FString& ProjectDirectory, TArray<FString>& Files, FString Text = "*.json");

	void LoadChapterData();
	void LoadCharacterData();
	void LoadEnvironmentData();
	
public:
	DataManager();
	~DataManager();

	void LoadData();

	FString GetEntrypointChapterKey() const { 
		if (m_pEntrypointData == nullptr)
			return "";
		return m_pEntrypointData->GetStartChapterKey();
	}

	StoryChapterData* GetChapterByKey(FString key) const {
		if (m_mChapterData.Contains(key))
			return m_mChapterData[key];
		return nullptr;
	}

	FString GetCharacterNameByKey(FString key) const {
		if (m_mCharacterData.Contains(key))
			return m_mCharacterData[key]->GetName();
		return "";
	}

	UTexture2D* GetCharacterTextureByKey(FString characterKey, FString textureKey) const {
		if (m_mCharacterData.Contains(characterKey))
			return m_mCharacterData[characterKey]->GetCharacterTexture(textureKey);
		return nullptr;
	}

	FString GetBackgroundByKey(FString environmentKey, FString backgroundKey) const {
		if (m_mEnvironmentData.Contains(environmentKey))
			return m_mEnvironmentData[environmentKey]->GetBackgroundTexture(backgroundKey);
		return "";
	}

	FVector2D GetCharacterPositionByKey(FString positionKey) const {
		if (m_pPositionData == nullptr)
			return FVector2D();
		return m_pPositionData->GetCharacterPosition(positionKey);
	}
};