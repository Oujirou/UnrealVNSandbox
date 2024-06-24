// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseStoryData.h"

/**
 * 
 */
class UNREALVNSANDBOX_API StoryEntrypointData : public BaseStoryData
{
	FString m_strStartChapterKey;
public:
	StoryEntrypointData();
	~StoryEntrypointData();

	void InitFromJson(FString path);

	FString GetStartChapterKey() const { return m_strStartChapterKey; }
};
