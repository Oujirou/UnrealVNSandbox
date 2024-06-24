// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JsonHandler.h"

/**
 * 
 */
class UNREALVNSANDBOX_API GameSave : public JsonHandler
{
	bool m_bHasSaveData = false;

	FString m_strDisplayName = "Empty";
	FString m_strChapterKey = "";
	FString m_strRawActionText = "";
	FString m_strStoryText = "";
	FString m_strDate = "";

	TMap<FString, FString> m_ActionMap;

public:
	GameSave();
	~GameSave();

	void LoadSaveData(int saveSlot);
	void ClearSaveData();

	FString GetDisplayName() { return m_strDisplayName; }
	FString GetChapterKey() { return m_strChapterKey; }
	FString GetRawActionText() { return m_strRawActionText; }
	FString GetStoryText() { return m_strStoryText; }
	FString GetDate() { return m_strDate; }
};
