// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseStoryData.h"

/**
 * 
 */
class UNREALVNSANDBOX_API StoryEnvironmentData : public BaseStoryData
{
	//	Internal - Used as a key to help group similar backgrounds.
	FString m_strFolderName;

	//  Internal - Used as a key to help group similar backgrounds.
	FString m_strKey;

	TMap<FString, FString> m_mBackgroundTextures;

public:
	StoryEnvironmentData();
	~StoryEnvironmentData();

	void InitFromJson(FString path);

	FString GetFolderName() const { return m_strFolderName; }
	FString GetKey() const { return m_strKey; }

	FString GetBackgroundTexture(FString textureKey) const
	{
		if (!m_mBackgroundTextures.Contains(textureKey))
		{
			UE_LOG(LogTemp, Error, TEXT("Texture %s not found in StoryEnvironmentData key: %s"), *textureKey, *m_strKey);
			return "";
		}
		return "/Game/Assets/Environments/" + m_strFolderName + "/" + m_mBackgroundTextures[textureKey];
	}
};
