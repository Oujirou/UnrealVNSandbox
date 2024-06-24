// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseStoryData.h"

/**
 * 
 */
class UNREALVNSANDBOX_API StoryPositionData : public BaseStoryData
{
	// Will be empty in the case of the narrator.
	TMap<FString, FVector2D> m_mCharacterPositions;
public:
	StoryPositionData();
	~StoryPositionData();

	void InitFromJson(FString path);

	FVector2D GetCharacterPosition(FString positionName) const
	{
		if (!m_mCharacterPositions.Contains(positionName))
		{
			UE_LOG(LogTemp, Error, TEXT("Position %s not found in StoryPositionData"), *positionName);
			return FVector2D();
		}
		return m_mCharacterPositions[positionName];
	}
};
