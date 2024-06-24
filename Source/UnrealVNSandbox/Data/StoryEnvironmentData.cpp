// Fill out your copyright notice in the Description page of Project Settings.


#include "StoryEnvironmentData.h"

StoryEnvironmentData::StoryEnvironmentData()
{
}

StoryEnvironmentData::~StoryEnvironmentData()
{
}

// Implement LoadFromJson
void StoryEnvironmentData::InitFromJson(FString path)
{
	TSharedPtr<FJsonObject> JsonData = LoadJsonData(path);
	if (JsonData == nullptr || !JsonData.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load environment data from %s"), *path);
		return;
	}

	m_strFolderName = JsonData->GetStringField("folderName");

	m_strKey = JsonData->GetStringField("key");

	TSharedPtr<FJsonObject> Textures = JsonData->GetObjectField("textures");
	for (auto It = Textures->Values.CreateConstIterator(); It; ++It)
	{
		m_mBackgroundTextures.Add(It.Key(), It.Value()->AsString());
	}
}