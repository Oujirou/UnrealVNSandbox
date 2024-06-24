// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveSlotWidget.h"

// Inplement the Setup function
void USaveSlotWidget::SetValues(UTextBlock* Title, UTextBlock* Date, UTextBlock* Line, UImage* Image)
{
	m_tbTitle = Title;
	m_tbDate = Date;
	m_tbLine = Line;
	m_imgThumbnail = Image;
	RefreshSlot();
}

// Implement the SetSlotInfo function
void USaveSlotWidget::SetSlotInfo(int position, SaveManager* saveManager)
{
	m_nPosition = position;
	m_pSaveManager = saveManager;
	RefreshSlot();
}

// Implement the RefreshSlot function
void USaveSlotWidget::RefreshSlot()
{
	if (m_pSaveManager == nullptr || m_tbTitle == nullptr)
	{
		return;
	}

	// Set the title
	m_tbTitle->SetText(FText::FromString(m_pSaveManager->GetDisplayName(m_nPosition)));

	// Set the date
	m_tbDate->SetText(FText::FromString(m_pSaveManager->GetDate(m_nPosition)));

	// Set the line
	m_tbLine->SetText(FText::FromString(m_pSaveManager->GetStoryText(m_nPosition)));

	// Set the thumbnail
	FString ThumbnailName = m_pSaveManager->GetThumbnail(m_nPosition);
	UTexture2D* ThumbnailTexture = LoadObject<UTexture2D>(nullptr, *ThumbnailName);
	m_imgThumbnail->SetBrushFromTexture(ThumbnailTexture);
}