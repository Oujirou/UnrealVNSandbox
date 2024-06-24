// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveManager.h"

SaveManager::SaveManager()
{
	m_bInitialized = false;
}

SaveManager::~SaveManager()
{
	for (size_t i = 0; i < m_vSaveData.Num(); i++)
	{
		delete m_vSaveData[i];
	}
	m_vSaveData.Empty();
}

void SaveManager::Initialize(DataManager* dataManager)
{
	if (m_bInitialized)
		return;

	m_pDataManager = dataManager;

	for (size_t i = 0; i < 6; i++)
	{
		GameSave* Save = new GameSave();
		Save->LoadSaveData(i);
		m_vSaveData.Add(Save);
	}

	// Load the progress file into m_mChapterReadProgress
	FString path = FPaths::ProjectSavedDir() + "Saves/Progress.json";
	TSharedPtr<FJsonObject> JsonObject = LoadJsonData(path);
	if (JsonObject != nullptr && JsonObject.IsValid())
	{
		// Iterate over each key value pair in the JSON object
		for (auto Pair = JsonObject->Values.CreateConstIterator(); Pair; ++Pair)
		{
			// Get the key and value from the pair
			FString key = Pair.Key();
			int value = Pair.Value()->AsNumber();
			// Add the key value pair to m_mChapterReadProgress
			m_mChapterReadProgress.Add(key, value);
		}
	}
}

void SaveManager::SaveGame(int saveSlot, SaveData saveData)
{
	if (saveSlot < 0 || saveSlot >= 6)
		return;

	FString displayName = m_pDataManager->GetChapterByKey(saveData.ChapterKey)->GetChapterName();

	// Get the current date and time
	FDateTime now = FDateTime::Now();
	FString date = now.ToString();

	// Make a json file at Saves/DataSave{saveSlot}.json
	FString path = FPaths::ProjectSavedDir() + "Saves/SaveData" + FString::FromInt(saveSlot) + ".json";
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	JsonObject->SetStringField("displayName", displayName);
	JsonObject->SetStringField("chapterKey", saveData.ChapterKey);
	JsonObject->SetStringField("rawActionText", saveData.RawActionText);
	JsonObject->SetStringField("date", date);

	// Make a json object for the action map
	TSharedPtr<FJsonObject> ActionMapObject = MakeShareable(new FJsonObject());
	// Iterate over each key value pair in the action map
	for (auto Pair = saveData.ActionMap.CreateConstIterator(); Pair; ++Pair)
	{
		// Get the key and value from the pair
		FString key = Pair.Key();
		FString value = Pair.Value();
		// Add the key value pair to the action map object
		ActionMapObject->SetStringField(key, value);
	}

	// Add the action map object to the save data json object
	JsonObject->SetObjectField("actionMap", ActionMapObject);

	// Write the json object to the file
	FString OutputString;
	TSharedRef<TJsonWriter<TCHAR>> Writer = TJsonWriterFactory<TCHAR>::Create(&OutputString);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);
	FFileHelper::SaveStringToFile(OutputString, *path);

	// Load the save data
	m_vSaveData[saveSlot]->LoadSaveData(saveSlot);
}

// Implement the ReadChapterLine function
void SaveManager::ReadChapterLine(FString chapterKey, int line)
{
	// Check if the chapter key is in m_mChapterReadProgress
	if (m_mChapterReadProgress.Contains(chapterKey))
	{
		// Get the current line number from m_mChapterReadProgress
		int currentLine = m_mChapterReadProgress[chapterKey];
		// If the current line number is less than the new line number
		if (line < currentLine)
		{
			//	The line was already read, no need to update the progress file.
			return;
		}
		else
		{
			// Update the line number in m_mChapterReadProgress
			m_mChapterReadProgress[chapterKey] = line;
		}
	}
	else
	{
		// Add the chapter key and line number to m_mChapterReadProgress
		m_mChapterReadProgress.Add(chapterKey, line);
	}

	// Make a json file at Saves/Progress.json
	FString path = FPaths::ProjectSavedDir() + "Saves/Progress.json";
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	// Iterate over each key value pair in m_mChapterReadProgress
	for (auto Pair = m_mChapterReadProgress.CreateConstIterator(); Pair; ++Pair)
	{
		// Get the key and value from the pair
		FString key = Pair.Key();
		int value = Pair.Value();
		// Add the key value pair to the json object
		JsonObject->SetNumberField(key, value);
	}
	// Write the json object to the file
	FString OutputString;
	TSharedRef<TJsonWriter<TCHAR>> Writer = TJsonWriterFactory<TCHAR>::Create(&OutputString);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);
	FFileHelper::SaveStringToFile(OutputString, *path);
}