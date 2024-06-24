// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "DataManager.h"
#include "../Data/GameSave.h"
#include "../Data/JsonHandler.h"

/**
 * 
 */
class UNREALVNSANDBOX_API SaveManager : public JsonHandler
{
public:
	struct SaveData {
		FString ChapterKey;
		FString RawActionText;
		FString StoryText;
		TMap<FString, FString> ActionMap;
	};
private:
	TArray<GameSave*> m_vSaveData;

	TMap<FString, int> m_mChapterReadProgress;

	DataManager* m_pDataManager;

	bool m_bInitialized = false;
public:
	SaveManager();
	~SaveManager();

	void Initialize(DataManager* dataManager);

	void SaveGame(int saveSlot, SaveData saveData);

	SaveData LoadGame(int saveSlot);

	void ReadChapterLine(FString chapterKey, int line);

	FString GetDisplayName(int slot) { 
		if (slot < 0 || slot >= m_vSaveData.Num())
			return "Empty";
		return m_vSaveData[slot]->GetDisplayName(); 
	}

	FString GetChapterKey(int slot) {
		if (slot < 0 || slot >= m_vSaveData.Num())
			return "";
		return m_vSaveData[slot]->GetChapterKey();
	}

	FString GetRawActionText(int slot) {
		if (slot < 0 || slot >= m_vSaveData.Num())
			return "";
		return m_vSaveData[slot]->GetRawActionText();
	}

	FString GetStoryText(int slot) {
		if (slot < 0 || slot >= m_vSaveData.Num())
			return "";
		return m_vSaveData[slot]->GetStoryText();
	}

	FString GetDate(int slot) {
		if (slot < 0 || slot >= m_vSaveData.Num())
			return "";
		return m_vSaveData[slot]->GetDate();
	}

	FString GetThumbnail(int slot) {
		if (slot < 0 || slot >= m_vSaveData.Num() || m_vSaveData[slot]->GetDisplayName() == "Empty")
			return "/Game/Assets/Menu/T_SavePortrait";
		// Split m_vSaveData[slot]->GetDisplayName() at the first space
		// Return the second half of the split string
		FString Thumbnail;
		m_vSaveData[slot]->GetDisplayName().Split(" ", nullptr, &Thumbnail);
		return "/Game/Assets/Menu/T_PortraitChapter" + Thumbnail;
	}

};
