// Fill out your copyright notice in the Description page of Project Settings.


#include "StoryCharacterData.h"

StoryCharacterData::StoryCharacterData()
{
}

StoryCharacterData::~StoryCharacterData()
{
}

void StoryCharacterData::InitFromJson(FString path)
{
	TSharedPtr<FJsonObject> JsonData = LoadJsonData(path);
	if (JsonData == nullptr || !JsonData.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load character data from %s"), *path);
		return;
	}

	m_strName = JsonData->GetStringField("name");

	m_strKey = JsonData->GetStringField("key");

	TSharedPtr<FJsonObject> Textures = JsonData->GetObjectField("textures");
	for (auto It = Textures->Values.CreateConstIterator(); It; ++It)
	{
		FString texturePath = "/Game/Assets/Characters/" + It.Value()->AsString();
		UTexture2D* texture = LoadObject<UTexture2D>(nullptr, *texturePath);
		m_mCharacterTextures.Add(It.Key(), texture);
	}
}