// Fill out your copyright notice in the Description page of Project Settings.


#include "StoryEntrypointData.h"

StoryEntrypointData::StoryEntrypointData()
{
}

StoryEntrypointData::~StoryEntrypointData()
{
}

void StoryEntrypointData::InitFromJson(FString path)
{
	TSharedPtr<FJsonObject> JsonData = LoadJsonData(path);
	if (JsonData == nullptr || !JsonData.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load entrypoint data from %s"), *path);
		return;
	}

	m_strStartChapterKey = JsonData->GetStringField("startChapterKey");
}