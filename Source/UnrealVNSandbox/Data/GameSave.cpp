// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSave.h"

GameSave::GameSave()
{
}

GameSave::~GameSave()
{
}

// Implement the LoadSaveData function
void GameSave::LoadSaveData(int saveSlot)
{
	// Create a variable to hold the save file path
	FString path = FPaths::ProjectSavedDir() + "Saves/SaveData" + FString::FromInt(saveSlot) + ".json";
	// Check if File Exists at path
	
	// Load the save data
	TSharedPtr<FJsonObject> JsonObject = LoadJsonData(path);
	// Check if the JSON object is valid
	if (JsonObject != nullptr && JsonObject.IsValid())
	{
		// Get the display name from the JSON object
		m_strDisplayName = JsonObject->GetStringField("displayName");
		// Get the chapter key from the JSON object
		m_strChapterKey = JsonObject->GetStringField("chapterKey");
		// Get the raw action text from the JSON object
		m_strRawActionText = JsonObject->GetStringField("rawActionText");
		// Get the story text from the JSON object
		m_strStoryText = JsonObject->GetStringField("storyText");
		// Get the date from the JSON object
		m_strDate = JsonObject->GetStringField("date");
		// Set the flag to indicate that save data has been loaded
		m_bHasSaveData = true;
	}
}

// Implement the ClearSaveData function
void GameSave::ClearSaveData()
{
	// Clear the save data
	m_strDisplayName = "Empty";
	m_strChapterKey = "";
	m_strRawActionText = "";
	m_strDate = "";
	m_bHasSaveData = false;
}