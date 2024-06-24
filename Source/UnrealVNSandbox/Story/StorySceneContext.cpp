// Fill out your copyright notice in the Description page of Project Settings.


#include "StorySceneContext.h"

StorySceneContext::StorySceneContext()
{
}

StorySceneContext::~StorySceneContext()
{
}

bool StorySceneContext::IsActionDone()
{
	return false;
}

void StorySceneContext::ExecuteAction()
{
}

void StorySceneContext::ResolveState()
{
	if (m_strCurrentRawActionText.IsEmpty())
	{
		return;
	}

	m_pCurrentChapterData = m_pDataManager->GetChapterByKey(m_strCurrentChapterKey);
	m_vCurrentActions = m_pCurrentChapterData->GetActions();

	TMap<FString, FString> actionMap;
	TMap<FString, FString> characterMap;
	TArray<FString> moveActions;

	FString lastAction = m_vCurrentActions[m_iCurrentActionIndex];
	while (lastAction != m_strCurrentRawActionText)
	{
		// Split string on first instance of ,
		FString actionKey;
		FString actionContents;
		lastAction.Split(",", &actionKey, &actionKey);

		if (actionKey == "bg")
			actionMap["bg"] = actionContents;
		else if (actionKey == "text")
			actionMap["text"] = actionContents;
		else if (actionKey == "spawn") {
			// Split actionContents on first instance of ,
			FString characterKey;
			FString characterContents;
			actionContents.Split(",", &characterKey, &characterContents);

			characterMap[characterKey] = characterContents;
		}
		else if (actionKey == "despawn") {
			FString characterKey;
			FString characterContents;
			actionContents.Split(",", &characterKey, &characterContents);

			if (characterMap.Contains(characterKey))
				characterMap.Remove(characterKey);
		}
		else if (actionKey == "move")
			moveActions.Add(actionContents);

		m_iCurrentActionIndex++;
		if (m_iCurrentActionIndex >= m_vCurrentActions.Num())
			break;

		lastAction = m_vCurrentActions[m_iCurrentActionIndex];
	}

	if (actionMap.Contains("bg"))
		m_strCurrentBackgroundTexture = actionMap["bg"];

	if (actionMap.Contains("text")) {
		// TODO: Queue Text Display
	}

	for (auto& character : characterMap)
	{
		// TODO: Spawn Characters
	}

	for (auto& moveAction : moveActions)
	{
		// Split moveAction on first instance of ,
		FString characterKey;
		FString characterContents;
		moveAction.Split(",", &characterKey, &characterContents);

		// TODO: Check if character is spawned and move them.
	}

}