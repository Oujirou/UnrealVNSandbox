// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/CanvasPanel.h"

/**
 * 
 */
class UNREALVNSANDBOX_API BaseStoryAction
{
protected:
	FString RawText;
	bool m_bWait = false;
	bool m_bCleanup = false;

	TMap<FString, FString> m_mExtraParameters;
public:
	BaseStoryAction(FString text);
	virtual ~BaseStoryAction() = 0;

	virtual void Update(float deltaTime) = 0;

	virtual bool IsComplete() = 0;

	virtual void Skip() = 0;

	virtual FString GetActionMapKey() const = 0;

	virtual UCanvasPanelSlot* GetCanvasPanelSlot() const;

	bool Cleanup() { return m_bCleanup; }

	bool Wait() const { return m_bWait; }
};
