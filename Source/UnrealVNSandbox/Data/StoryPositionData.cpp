// Fill out your copyright notice in the Description page of Project Settings.


#include "StoryPositionData.h"

StoryPositionData::StoryPositionData()
{
}

StoryPositionData::~StoryPositionData()
{
}

// Implement LoadFromJson
void StoryPositionData::InitFromJson(FString path)
{
	TSharedPtr<FJsonObject> JsonData = LoadJsonData(path);
	if (JsonData == nullptr || !JsonData.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load position data from %s"), *path);
		return;
	}

	TSharedPtr<FJsonObject> Positions = JsonData->GetObjectField("positions");
	for (auto It = Positions->Values.CreateConstIterator(); It; ++It)
	{
		// Convert the value to a json object and get the x and y value from it.
		TSharedPtr<FJsonObject> Position = It.Value()->AsObject();
		float x = FCString::Atof(*Position->GetStringField("x"));
		float y = FCString::Atof(*Position->GetStringField("y"));
		FVector2D position(x, y);

		// Add the position to the map.
		m_mCharacterPositions.Add(It.Key(), position);
	}
}