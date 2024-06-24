// Fill out your copyright notice in the Description page of Project Settings.


#include "LoadWidget.h"

// Implement to Initialize method
void ULoadWidget::Setup()
{
	m_pSaveManager = new SaveManager();
	m_pSaveManager->Initialize(nullptr);
}

// Implement to SetSaveSlot method
void ULoadWidget::SetSaveSlot(int saveSlot, USaveSlotWidget* widget)
{
	m_vSaveSlots[saveSlot] = widget;
	widget->SetSlotInfo(saveSlot, m_pSaveManager);
}

// Implement to GetDisplayNameBySlot method
FString ULoadWidget::GetDisplayNameBySlot(int saveSlot)
{
	if (m_pSaveManager == nullptr)
	{
		return "No Save Manager Assigned";
	}
	if (saveSlot < 0 || saveSlot >= m_vSaveSlots.Num())
	{
		return "Bad Index";
	}
	return m_pSaveManager->GetDisplayName(saveSlot);
}

// Implement to HasSaveDataBySlot method
bool ULoadWidget::HasSaveDataBySlot(int saveSlot)
{
	if (m_pSaveManager == nullptr)
	{
		return false;
	}
	if (saveSlot < 0 || saveSlot >= m_vSaveSlots.Num())
	{
		return false;
	}
	return m_pSaveManager->GetChapterKey(saveSlot) != "";
}

// Implement to GetChapterKeyBySlot method
FString ULoadWidget::GetChapterKeyBySlot(int saveSlot)
{
	if (m_pSaveManager == nullptr)
	{
		return "No Save Manager Assigned";
	}
	if (saveSlot < 0 || saveSlot >= m_vSaveSlots.Num())
	{
		return "Bad Index";
	}
	return m_pSaveManager->GetChapterKey(saveSlot);
}

// Implement to GetRawActionTextBySlot method
FString ULoadWidget::GetRawActionTextBySlot(int saveSlot)
{
	if (m_pSaveManager == nullptr)
	{
		return "No Save Manager Assigned";
	}
	if (saveSlot < 0 || saveSlot >= m_vSaveSlots.Num())
	{
		return "Bad Index";
	}
	return m_pSaveManager->GetRawActionText(saveSlot);
}