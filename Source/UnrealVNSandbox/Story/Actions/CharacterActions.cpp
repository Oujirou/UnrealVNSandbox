// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterActions.h"

// Set ACTION_KEY to "text"
const FString CharacterActions::ACTION_KEY = "char";

CharacterActions::CharacterActions(FString text) : BaseStoryAction(text)
{
}

CharacterActions::~CharacterActions()
{
	m_pCanvasPanel->RemoveChild(m_pCharacterImage);
	delete m_pCharacterImage;

	m_pCharacterImage = nullptr;
	m_pDataManager = nullptr;
	m_pCanvasPanel = nullptr;
}

void CharacterActions::Setup(DataManager* dataManager, UCanvasPanel* canvasPanel, FVector2D position, int32 zOrder)
{
	m_pCharacterImage = NewObject<UImage>(canvasPanel);
	m_pCharacterImage->SetVisibility(ESlateVisibility::Visible);

	m_pCanvasPanel = canvasPanel;
	m_pCanvasPanel->AddChild(m_pCharacterImage);

	m_pDataManager = dataManager;

	// Split on the first , of RawText
	FString left;
	FString right;

	FString characterKey;
	FString textureKey;

	//	spawn,mc,normal,left1
	RawText.Split(",", &left, &right);
	//	mc,normal,left1
	right.Split(",", &characterKey, &right);
	//	normal,left1
	right.Split(",", &textureKey, &right);

	actionKeyOverride = ACTION_KEY + "-" + characterKey;


	// Load texture
	UTexture2D* texture = m_pDataManager->GetCharacterTextureByKey(characterKey, textureKey);
	
	m_pCharacterImage->SetBrushFromTexture(texture);

	UCanvasPanelSlot* slot = Cast<UCanvasPanelSlot>(m_pCharacterImage->Slot);

	slot->SetAnchors(FAnchors(0.0f, 1.0f, 0.0f, 1.0f));
	slot->SetAlignment(FVector2D(0.5f, 1.0f));
	slot->SetZOrder(zOrder);

	int32 sizeX = texture->GetSizeX();
	int32 sizeY = texture->GetSizeY();
	slot->SetSize(FVector2D(sizeX, sizeY));

	slot->SetPosition(position);
}

void CharacterActions::UpdateImage(FString characterKey, FString textureKey)
{
	UTexture2D* texture = m_pDataManager->GetCharacterTextureByKey(characterKey, textureKey);

	m_pCharacterImage->SetBrushFromTexture(texture);

	UCanvasPanelSlot* slot = Cast<UCanvasPanelSlot>(m_pCharacterImage->Slot);
	int32 sizeX = texture->GetSizeX();
	int32 sizeY = texture->GetSizeY();
	slot->SetSize(FVector2D(sizeX, sizeY));
}

void CharacterActions::Update(float deltaTime)
{
}

bool CharacterActions::IsComplete()
{
	return true;
}

void CharacterActions::Skip()
{
}

UCanvasPanelSlot* CharacterActions::GetCanvasPanelSlot() const
{
	if (m_pCharacterImage == nullptr)
		return nullptr;
	return Cast<UCanvasPanelSlot>(m_pCharacterImage->Slot);
}

FString CharacterActions::GetActionMapKey() const
{
	return actionKeyOverride == "" ? ACTION_KEY: actionKeyOverride;
}