// Fill out your copyright notice in the Description page of Project Settings.


#include "BackgroundAction.h"

#include <Components/CanvasPanelSlot.h>

// Set ACTION_KEY to "text"
const FString BackgroundAction::ACTION_KEY = "bg";

BackgroundAction::BackgroundAction(FString text) : BaseStoryAction(text)
{
	// Raw Text Example: bg,mc-c1-1
	// Split on the first ,
	FString actionKey;
	FString actionContents;
	text.Split(",", &actionKey, &actionContents);

	// Split on the first -
	actionContents.Split(",", &m_strEnvironmentKey, &m_strBackgroundKey);

	m_bWait = false;
}

BackgroundAction::~BackgroundAction()
{
}

void BackgroundAction::Update(float deltaTime)
{
	// Add debug log
	if (m_pBackgroundA == nullptr || m_pBackgroundB == nullptr || m_pDataManager == nullptr)
		return;

	if (!m_pBackgroundA->IsAnimationComplete() || !m_pBackgroundB->IsAnimationComplete())
	{
		UE_LOG(LogTemp, Warning, TEXT("BackgroundAction::Update"));
	}
}

bool BackgroundAction::IsComplete()
{
	return true;
}

void BackgroundAction::Skip()
{

}

void BackgroundAction::Setup(DataManager* dataManager, UStoryBackground* backgroundA, UStoryBackground* backgroundB)
{
	m_pDataManager = dataManager;
	m_pBackgroundA = backgroundA;
	m_pBackgroundB = backgroundB;

	m_pBackgroundA->SendToBack();
	Cast<UCanvasPanelSlot>(m_pBackgroundA->Slot)->SetZOrder(0);
	
	m_pBackgroundB->SendToBack();

	// Get z order of m_pBackgroundA->BackgroundImage
	//int32 zOrderA = Cast<UCanvasPanelSlot>(m_pBackgroundA->Slot)->GetZOrder();
	//int32 zOrderB = Cast<UCanvasPanelSlot>(m_pBackgroundB->Slot)->GetZOrder();
	
	//UStoryBackground* activeBackground = (zOrderA > zOrderB ? m_pBackgroundA : m_pBackgroundB);
	//UStoryBackground* extraBackground = (zOrderA < zOrderB ? m_pBackgroundA : m_pBackgroundB);

	// Set the background image of the extra background
	//activeBackground->SetBackgroundImage(m_pDataManager->GetBackgroundByKey(m_strEnvironmentKey, m_strBackgroundKey));
	//extraBackground->SendToBack();
}

void BackgroundAction::UpdateImage(FString rawText, bool setToActive)
{
	// Raw Text Example: bg,mc-c1-1
	// Split on the first ,
	FString actionKey;
	FString actionContents;
	rawText.Split(",", &actionKey, &actionContents);

	// Split on the first -
	actionContents.Split(",", &m_strEnvironmentKey, &m_strBackgroundKey);

	// Get z order of m_pBackgroundA->BackgroundImage
	int32 zOrderA = Cast<UCanvasPanelSlot>(m_pBackgroundA->Slot)->GetZOrder();
	int32 zOrderB = Cast<UCanvasPanelSlot>(m_pBackgroundB->Slot)->GetZOrder();

	UStoryBackground* activeBackground = (zOrderA > zOrderB ? m_pBackgroundA : m_pBackgroundB);
	UStoryBackground* extraBackground = (m_pBackgroundA == activeBackground ? m_pBackgroundB : m_pBackgroundA);

	// Set the background image of the extra background
	if (setToActive)
		activeBackground->SetBackgroundImage(m_pDataManager->GetBackgroundByKey(m_strEnvironmentKey, m_strBackgroundKey));
	else {
		extraBackground->SetBackgroundImage(m_pDataManager->GetBackgroundByKey(m_strEnvironmentKey, m_strBackgroundKey));
		activeBackground->Animate();
	}
}

//	Fade out animation
void BackgroundAction::Animate()
{
	// Get z order of m_pBackgroundA->BackgroundImage
	//int32 zOrderA = Cast<UCanvasPanelSlot>(m_pBackgroundA->Slot)->GetZOrder();
	//int32 zOrderB = Cast<UCanvasPanelSlot>(m_pBackgroundB->Slot)->GetZOrder();

	//UStoryBackground* activeBackground = (zOrderA > zOrderB ? m_pBackgroundA : m_pBackgroundB);
	//UStoryBackground* extraBackground = (m_pBackgroundA == activeBackground ? m_pBackgroundB : m_pBackgroundA);

	// Play the fade out animation on the extra background
	//extraBackground->Animate();
}

FString BackgroundAction::GetActionMapKey() const
{
	return ACTION_KEY;
}