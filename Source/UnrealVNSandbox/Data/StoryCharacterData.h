// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseStoryData.h"

/**
 * 
 */
class UNREALVNSANDBOX_API StoryCharacterData : public BaseStoryData
{
	// External - Shown to the player.
	FString m_strName;

	// Internal - Used for identification.
	FString m_strKey;

	// Will be empty in the case of the narrator.
	TMap<FString, UTexture2D*> m_mCharacterTextures;

public:
	StoryCharacterData();
	~StoryCharacterData();

	void InitFromJson(FString path);

	FString GetName() const { return m_strName; }
	FString GetKey() const { return m_strKey; }

	UTexture2D* GetCharacterTexture(FString textureKey) const
	{
		if (!m_mCharacterTextures.Contains(textureKey))
		{
			UE_LOG(LogTemp, Error, TEXT("Texture %s not found in StoryCharacterData"), *textureKey);
			return nullptr;
		}
		return m_mCharacterTextures[textureKey];
	}
};
