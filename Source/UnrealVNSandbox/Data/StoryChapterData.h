// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseStoryData.h"

/**
 * 
 */
class UNREALVNSANDBOX_API StoryChapterData : public BaseStoryData
{
	// External - Not a unique , but is used in displays.
	FString m_strChapterName;

	// Chapter Key is unique and used for internal references.
	// May be broken up into multiple parts ie: ch1, ch1-1, ch1-2
	FString m_strChapterKey;

	TArray<FString> m_vActions;
	TMap<FString, FString> m_mChapterText;
public:
	StoryChapterData();
	~StoryChapterData();

	void InitFromJson(FString path);

	FString GetChapterName() { return m_strChapterName; }
	FString GetChapterKey() { return m_strChapterKey; }
	TArray<FString> GetActions() { return m_vActions; }
	FString GetAction(int index) { 
		if (index < 0 || index >= m_vActions.Num())
		{
			UE_LOG(LogTemp, Error, TEXT("Index %d out of range in StoryChapterData"), index);
			return "";
		}
		return m_vActions[index]; 
	}
	int GetActionIndexByRawText(FString rawText) {
		for (int i = 0; i < m_vActions.Num(); i++)
		{
			if (m_vActions[i] == rawText)
				return i;
		}
		UE_LOG(LogTemp, Error, TEXT("RawText %s not found in StoryChapterData"), *rawText);
		return -1;
	}
	FString GetChapterText(FString key) { 
		if (!m_mChapterText.Contains(key))
		{
			UE_LOG(LogTemp, Error, TEXT("Text %s not found in StoryChapterData"), *key);
			return "";
		}
		return m_mChapterText[key]; 
	}
};
