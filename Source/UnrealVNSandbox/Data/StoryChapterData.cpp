// Fill out your copyright notice in the Description page of Project Settings.


#include "StoryChapterData.h"

StoryChapterData::StoryChapterData()
{
}

StoryChapterData::~StoryChapterData()
{
}

void StoryChapterData::InitFromJson(FString path)
{
	TSharedPtr<FJsonObject> JsonData = LoadJsonData(path);
	if (JsonData == nullptr || !JsonData.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load chapter data from %s"), *path);
		return;
	}

	m_strChapterName = JsonData->GetStringField("name");

	m_strChapterKey = JsonData->GetStringField("key");

	TArray<TSharedPtr<FJsonValue>> KeysArray = JsonData->GetArrayField("actions");
	for (auto Value : KeysArray)
	{
		m_vActions.Add(Value->AsString());
	}

	TSharedPtr<FJsonObject> Texts = JsonData->GetObjectField("text");
	for (auto It = Texts->Values.CreateConstIterator(); It; ++It)
	{
		m_mChapterText.Add(It.Key(), It.Value()->AsString());
	}
}