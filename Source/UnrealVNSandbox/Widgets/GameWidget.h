// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanel.h"
#include "StoryBackground.h"

#include "../Story/StorySceneContext.h"
#include "../Story/BaseStoryAction.h"
#include "../Story/Actions/DialogAction.h"
#include "../Story/Actions/BackgroundAction.h"
#include "../Story/Actions/CharacterActions.h"
#include "../Story/Actions/MoveAction.h"

#include "../Managers/DataManager.h"
#include "../Managers/SaveManager.h"

#include "GameWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALVNSANDBOX_API UGameWidget : public UUserWidget
{
	GENERATED_BODY()

	struct TextState
	{
		// List of FStrings to display
		TArray<FString> TextList;
		// Current index of TextList
		int CurrentIndex = 0;
		int CurrentLetter = -1;

		float LettersPerSecond = 0.2;
		float TimeSinceLastLetter = 0.0;

		FString currentLine = "";

		bool Complete = true;
	};
	TextState m_TextState;

	DataManager* m_pDataManager;
	SaveManager* m_pSaveManager;

	StoryChapterData* m_pCurrentChapterData;
	int m_iCurrentActionIndex = -1;

	StorySceneContext* m_pStorySceneContext;

	FString m_strChapterKey = "";
	FString m_strRawActionText = "";

	TMap<FString, BaseStoryAction*> m_ActionMap;

	BaseStoryAction* GetActionFromRawText(FString key);
	void ResolveNextAction();

	TMap<FString, int> m_mCharacterZOffsets;
	int m_nBaseZOffset = 10;

	bool m_bActionsComplete = false;

	float AutoTime = 2.0f;
	float m_fAutoTime = 0.0f;
public:
	bool Initialize() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	UStoryBackground* BackgroundImage1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	UStoryBackground* BackgroundImage2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	UTextBlock* AttributeTextBlock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	UTextBlock* DialogTextBlock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Play")
	bool AutoPlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Play")
	bool GameOver;

	UFUNCTION(BlueprintCallable, Category = "Load")
	void SetStoryStart(FString chapterKey, FString rawActionText);
	
	UFUNCTION(BlueprintCallable, Category = "Start")
	void StartGame();

	UFUNCTION(BlueprintCallable, Category = "Play")
	void OnTick();

	UFUNCTION(BlueprintCallable, Category = "Play")
	void ForwardStory();

};
