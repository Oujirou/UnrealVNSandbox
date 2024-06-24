// Fill out your copyright notice in the Description page of Project Settings.


#include "GameWidget.h"

#include "Fonts/FontMeasure.h"

BaseStoryAction* UGameWidget::GetActionFromRawText(FString key)
{
	// Progress Save File
	m_pSaveManager->ReadChapterLine(m_strChapterKey, m_iCurrentActionIndex);

	// Split key on the first ,
	FString actionKey;
	FString actionContents;
	key.Split(",", &actionKey, &actionContents);

	// Check Against All Action Types
	if (actionKey == DialogAction::ACTION_KEY)
	{
		GetWorld();
		DialogAction* dialogAction = new DialogAction(key);
		dialogAction->Setup(m_strChapterKey, m_pDataManager, AttributeTextBlock, DialogTextBlock, GetWorld());
		return dialogAction;
	}
	else if (actionKey == BackgroundAction::ACTION_KEY)
	{
		BackgroundAction* backgroundAction = nullptr;
		if (m_ActionMap.Find(BackgroundAction::ACTION_KEY) != nullptr)
		{
			// cast m_ActionMap[BackgroundAction::ACTION_KEY] to BackgroundAction*
			backgroundAction = (BackgroundAction*)m_ActionMap[BackgroundAction::ACTION_KEY];
			backgroundAction->UpdateImage(key, false);
			return backgroundAction;
		}

		backgroundAction = new BackgroundAction(key);
		backgroundAction->Setup(m_pDataManager, BackgroundImage1, BackgroundImage2);
		backgroundAction->UpdateImage(key, true);
		return backgroundAction;
	}
	else if (actionKey == MoveAction::ACTION_KEY)
	{
		MoveAction* moveAction = new MoveAction(key);

		UCanvasPanelSlot* canvasPanelSlot = nullptr;

		if (m_ActionMap.Contains(moveAction->GetMoveTargetKey()))
		{
			canvasPanelSlot = m_ActionMap[moveAction->GetMoveTargetKey()]->GetCanvasPanelSlot();
		}
		
		if (canvasPanelSlot == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("Could not find canvas panel slot for %s"), *moveAction->GetMoveTargetKey());
			delete moveAction;
			return nullptr;
		}

		moveAction->Setup(m_pDataManager, canvasPanelSlot);
		return moveAction;
	}
	else if (actionKey == CharacterActions::ACTION_KEY)
	{
		// "char,mc,happy"
		// "mc,happy"
		FString characterKey;
		FString characterState;

		actionContents.Split(",", &characterKey, &characterState);

		FString mapKey = CharacterActions::ACTION_KEY + "-" + characterKey;

		if (m_ActionMap.Find(mapKey) != nullptr)
		{
			CharacterActions* characterAction = (CharacterActions*)m_ActionMap[mapKey];
			characterAction->UpdateImage(characterKey, characterState);
			return nullptr;
		}
	}
	else if (actionKey == "spawn")
	{
		//"spawn,mc,normal,left1",
		// Split on the first , of actionContents
		FString characterKey;
		FString characterState;

		actionContents.Split(",", &characterKey, &characterState);

		if (m_ActionMap.Find(characterKey) != nullptr)
		{
			return m_ActionMap[characterKey];
		}

		FString imageKey;
		FString positionKey;
		characterState.Split(",", &imageKey, &positionKey);

		UCanvasPanel* canvasPanel = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("CanvasPanel")));

		//UImage* CharacterImage = NewObject<UImage>(CanvasPanel);
		//CharacterImage->SetVisibility(ESlateVisibility::Visible);

		if (m_mCharacterZOffsets.Find(characterKey) == nullptr)
		{
			m_mCharacterZOffsets.Add(characterKey, m_nBaseZOffset);
			m_nBaseZOffset++;
		}

		//CanvasPanel->AddChild(CharacterImage);
		//UCanvasPanelSlot* slot = Cast<UCanvasPanelSlot>(CharacterImage->Slot);
		//slot->SetAnchors(FAnchors(0.0f, 1.0f, 0.0f, 1.0f));
		//slot->SetAlignment(FVector2D(0.5f, 1.0f));
		//slot->SetZOrder(m_mCharacterZOffsets[characterKey]);

		FVector2D position = m_pDataManager->GetCharacterPositionByKey(positionKey);

		CharacterActions* characterAction = new CharacterActions(key);
		characterAction->Setup(m_pDataManager, canvasPanel, position, m_mCharacterZOffsets[characterKey]);
		return characterAction;
	}
	else if (actionKey == "despawn")
	{
		// "despawn,mc",
		if (m_ActionMap.Find(actionContents) != nullptr)
		{
			BaseStoryAction* action = m_ActionMap[actionContents];
			m_ActionMap.Remove(actionContents);
			delete action;

			return nullptr;
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Could not find character to despawn %s"), *actionContents);
		}
	}
	else if (actionKey == "chapter")
	{
		if (m_pDataManager->GetChapterByKey(actionContents) != nullptr)
		{
			m_pCurrentChapterData = m_pDataManager->GetChapterByKey(actionContents);
			m_iCurrentActionIndex = -1;
			m_strChapterKey = actionContents;
			return nullptr;
		}
	}


	// Error log saying we could not find the action type
	UE_LOG(LogTemp, Error, TEXT("Could not find action type %s"), *actionKey);
	return nullptr;
}

// Implement the ResolveNextAction function
void UGameWidget::ResolveNextAction()
{
	TArray<FString> removeKeys;
	// Iterate through all actions and delete them if Cleanup is true
	for (auto& action : m_ActionMap)
	{
		if (action.Value->IsComplete() && action.Value->Cleanup())
		{
			delete action.Value;
			removeKeys.Add(action.Key);
		}
	}

	for (FString key : removeKeys)
	{
		m_ActionMap.Remove(key);
	}

	AttributeTextBlock->SetText(FText::FromString(""));
	DialogTextBlock->SetText(FText::FromString(""));

	m_bActionsComplete = false;
	m_fAutoTime = AutoTime;

	while (true)
	{
		// Get the next action
		m_iCurrentActionIndex++;
		FString rawAction = m_pCurrentChapterData->GetAction(m_iCurrentActionIndex);

		if (rawAction.IsEmpty())
		{
			// End of Story - Return to Main Menu
			GameOver = true;
			return;
		}

		BaseStoryAction* action = GetActionFromRawText(rawAction);

		if (action != nullptr)
		{
			if (m_ActionMap.Find(action->GetActionMapKey()) == nullptr)
			{
				m_ActionMap.Add(action->GetActionMapKey(), action);
			}
			
			if (action->Wait())
			{
				return;
			}
		}
	}
}

// Implement the Initialize function
bool UGameWidget::Initialize()
{
	// Call the parent class's Initialize function
	bool success = Super::Initialize();

	// Create a new instance of the DataManager class
	m_pDataManager = new DataManager();

	// Create a new instance of the SaveManager class
	m_pSaveManager = new SaveManager();
	m_pSaveManager->Initialize(m_pDataManager);

	// Get the Starting Chapter Key
	m_strChapterKey = m_pDataManager->GetEntrypointChapterKey();

	// Create the StorySceneContext
	m_pStorySceneContext = new StorySceneContext();

	return success;
}

// Implement the SetStoryStart function
void UGameWidget::SetStoryStart(FString chapterKey, FString rawActionText)
{
	// Set the chapter key
	m_strChapterKey = chapterKey;

	// Set the raw action text
	m_strRawActionText = rawActionText;

	// Set the current chapter data
	m_pCurrentChapterData = m_pDataManager->GetChapterByKey(m_strChapterKey);
	int index = m_pCurrentChapterData->GetActionIndexByRawText(m_strRawActionText);
	if (index == -1)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not find action index for %s"), *m_strRawActionText);
		m_strRawActionText = "";
		return;
	}

	m_iCurrentActionIndex = index - 1;
}

// Implement the StartGame function
void UGameWidget::StartGame()
{
	AttributeTextBlock->SetText(FText::FromString(""));
	DialogTextBlock->SetText(FText::FromString(""));

	m_pCurrentChapterData = m_pDataManager->GetChapterByKey(m_strChapterKey);

	// TODO: Handle the case where m_iCurrentActionIndex is not 0.
	ResolveNextAction();
}

void UGameWidget::OnTick()
{
	float deltaTime = GetWorld()->GetDeltaSeconds();

	if (m_bActionsComplete == false)
	{
		bool bAllActionsComplete = true;
		// Loop through all actions
		for (auto& action : m_ActionMap)
		{
			// Update the action
			action.Value->Update(deltaTime);
			if (!action.Value->IsComplete())
			{
				// If the action is complete, remove it from the map
				bAllActionsComplete = false;
			}
		}

		m_bActionsComplete = bAllActionsComplete;
		if (!m_bActionsComplete)
		{
			return;
		}
	}

	if (AutoPlay && m_bActionsComplete)
	{
		m_fAutoTime -= deltaTime;

		if (m_fAutoTime <= 0.0f)
		{
			ResolveNextAction();
		}
	}
}

void UGameWidget::ForwardStory()
{
	if (!m_bActionsComplete)
	{
		m_bActionsComplete = true;
		for (auto& action : m_ActionMap)
		{
			action.Value->Skip();
		}
		return;

	}

	ResolveNextAction();
}