// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseStoryAction.h"

BaseStoryAction::BaseStoryAction(FString text)
{
	RawText = text;

	FString left;
	FString right;
	TArray<FString> textList;
	text.ParseIntoArray(textList, TEXT(","), true);

	// Iterate through the array
	for (FString& param : textList)
	{
		// check if left starts with "-P"
		if (!param.StartsWith("-P") && !param.StartsWith("-p"))
			continue;

		// remove the "-P" from the string
		param.RemoveAt(0, 2);
		// split the string into key and value
		FString key;
		FString value;
		param.Split("=", &key, &value);
		// add the key and value to the map
		m_mExtraParameters.Add(key, value);
	}
}

BaseStoryAction::~BaseStoryAction()
{
}

UCanvasPanelSlot* BaseStoryAction::GetCanvasPanelSlot() const
{
	return nullptr;
}