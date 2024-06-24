// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveAction.h"

const FString MoveAction::ACTION_KEY = "move";

MoveAction::MoveAction(FString text) : BaseStoryAction(text)
{
	m_bCleanup = true;

	FString left;
	FString right;

	// move,mc,...
	text.Split(",", &left, &right);

	// mc,...
	right.Split(",", &m_strMoveTargetKey, &right);
}

MoveAction::~MoveAction()
{
}

void MoveAction::Setup(DataManager* dataManager, UCanvasPanelSlot* canvasPanelSlot)
{
	m_pDataManager = dataManager;
	m_pCanvasPanelSlot = canvasPanelSlot;
	m_vStartPosition = FVector2d(m_pCanvasPanelSlot->GetPosition());

	if (m_mExtraParameters.Contains("time"))
	{
		m_fDuration = FCString::Atof(*m_mExtraParameters["time"]);
	}
	else
	{
		m_fDuration = 1.0f;
	}

	if (m_mExtraParameters.Contains("wait"))
	{
		m_bWait = m_mExtraParameters["wait"].ToLower().Equals("true");
	}

	if (m_mExtraParameters.Contains("position"))
	{
		m_vEndPosition = FVector2d(m_pDataManager->GetCharacterPositionByKey(m_mExtraParameters["position"]));
	}

	if (m_mExtraParameters.Contains("x"))
	{
		m_vEndPosition.X = FCString::Atof(*m_mExtraParameters["x"]);
	}

	if (m_mExtraParameters.Contains("y"))
	{
		m_vEndPosition.Y = FCString::Atof(*m_mExtraParameters["y"]);
	}

	m_fTimeElapsed = 0.0f;
}

void MoveAction::Update(float deltaTime)
{
	if (m_fTimeElapsed >= m_fDuration)
	{
		return;
	}

	m_fTimeElapsed += deltaTime;

	if (m_fTimeElapsed > m_fDuration)
	{
		m_fTimeElapsed = m_fDuration;
		m_pCanvasPanelSlot->SetPosition(m_vEndPosition);
		return;
	}

	float t = m_fTimeElapsed / m_fDuration;

	FVector2d position;
	position.X = FMath::Lerp(m_vStartPosition.X, m_vEndPosition.X, t);
	position.Y = FMath::Lerp(m_vStartPosition.Y, m_vEndPosition.Y, t);

	m_pCanvasPanelSlot->SetPosition(position);
}

bool MoveAction::IsComplete()
{
	return m_fTimeElapsed >= m_fDuration;
}

void MoveAction::Skip()
{
	m_fTimeElapsed = m_fDuration;
	m_pCanvasPanelSlot->SetPosition(m_vEndPosition);
}

FString MoveAction::GetActionMapKey() const
{
	return RawText;
}