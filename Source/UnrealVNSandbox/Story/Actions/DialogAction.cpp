// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogAction.h"
#include "Fonts/FontMeasure.h"

// Set ACTION_KEY to "text"
const FString DialogAction::ACTION_KEY = "text";

DialogAction::DialogAction(FString text) : BaseStoryAction(text)
{
	m_bCleanup = true;

	// Raw Text Example: text,mc-c1-1
	// Split on the first ,
	FString actionKey;
	FString actionContents;
	text.Split(",", &actionKey, &actionContents);

	// Split on the first -
	actionContents.Split(",", &m_strAttributeKey, &m_strTextKey);

	m_bWait = true;
}

DialogAction::~DialogAction()
{
	if (m_pDialogSound != nullptr && m_pDialogSound->Sound != nullptr)
	{
		m_pDialogSound->Stop();
		m_pDialogSound->DestroyComponent();
	}

	m_pAttributeTextBlock = nullptr;
	m_pDialogTextBlock = nullptr;
	m_pDataManager = nullptr;
	m_pDialogSound = nullptr;
}

void DialogAction::Update(float deltaTime)
{
	if (m_pDialogTextBlock == nullptr || m_pDataManager == nullptr)
		return;

	if (m_TextState.Complete)
		return;

	m_TextState.TimeSinceLastLetter += deltaTime;
	float difference = 1.0f / m_TextState.LettersPerSecond;
	while (m_TextState.TimeSinceLastLetter > difference)
	{
		m_TextState.TimeSinceLastLetter -= difference;
		m_TextState.CurrentLetter++;

		bool addSpace = false;
		bool addNewLine = false;

		if (m_TextState.CurrentLetter >= m_TextState.TextList[m_TextState.CurrentIndex].Len())
		{
			m_TextState.CurrentLetter = 0;
			m_TextState.CurrentIndex++;
			addSpace = true;

			if (m_TextState.CurrentIndex >= m_TextState.TextList.Num())
			{
				m_TextState.Complete = true;
				return;
			}

			// Get Size from DialogTextBlock
			FVector2D size = m_pDialogTextBlock->GetCachedGeometry().GetLocalSize();

			FString testLine = m_TextState.CurrentLine + " " + m_TextState.TextList[m_TextState.CurrentIndex];

			const TSharedRef<FSlateFontMeasure> FontMeasure = FSlateApplication::Get().GetRenderer()->GetFontMeasureService();
			int extraOffset = 125;
			if (FontMeasure->Measure(testLine, m_pDialogTextBlock->Font).X > size.X - extraOffset)
			{
				// Add new line to DialogTextBlock
				addNewLine = true;
				m_TextState.CurrentLine = m_TextState.TextList[m_TextState.CurrentIndex];
			}
			else
			{
				m_TextState.CurrentLine += " " + m_TextState.TextList[m_TextState.CurrentIndex];
			}
		}

		// Get Text from DialogBox
		FString CurrentText = m_pDialogTextBlock->GetText().ToString();

		TCHAR c = m_TextState.TextList[m_TextState.CurrentIndex][m_TextState.CurrentLetter];

		if (addSpace)
		{
			CurrentText += " ";
		}

		if (addNewLine)
		{
			CurrentText += "\n";
		}

		// Add c to CurrentText
		CurrentText += c;

		m_pDialogTextBlock->SetText(FText::FromString(CurrentText));
	}
}

void DialogAction::Setup(FString chapterKey, DataManager* dataManager, UTextBlock* attributeTextBlock, UTextBlock* dialogTextBlock, UWorld* world)
{
	m_strChapterKey = chapterKey;
	m_pDataManager = dataManager;

	m_pAttributeTextBlock = attributeTextBlock;
	m_pDialogTextBlock = dialogTextBlock;

	float fTextLength = 3.0f; // Set to length of audio

	m_strDialogSoundUrl = "/Game/Assets/Audio/Story/" + chapterKey + "/" + m_strTextKey;
	USoundWave* Loaded = LoadObjFromPath<USoundWave>(FName(*m_strDialogSoundUrl));
	if (Loaded != nullptr)
	{
		m_pDialogSound = UGameplayStatics::SpawnSound2D(world, Loaded);
		fTextLength = Loaded->GetDuration();
	}

	m_pAttributeTextBlock->SetText(FText::FromString(m_pDataManager->GetCharacterNameByKey(m_strAttributeKey)));

	// Get Current Line
	StoryChapterData* currentChapter = m_pDataManager->GetChapterByKey(m_strChapterKey);
	FString currentLine = currentChapter->GetChapterText(m_strTextKey);

	// Set Text Info
	TArray<FString> TextList;
	int TextLength = currentLine.Len();

	// Split currentLine.GetText() by " "
	currentLine.ParseIntoArray(TextList, TEXT(" "), true);

	m_TextState.TextList = TextList;
	m_TextState.CurrentIndex = 0;
	m_TextState.CurrentLetter = -1;
	m_TextState.LettersPerSecond = float(TextLength) / fTextLength; // TODO: Set to length of audio
	m_TextState.TimeSinceLastLetter = 0;
	m_TextState.CurrentLine = "";
	m_TextState.Complete = false;
}

bool DialogAction::IsComplete()
{
	return m_TextState.Complete;
}

void DialogAction::Skip()
{
	m_TextState.Complete = true;

	m_TextState.CurrentIndex = 0;
	m_TextState.CurrentLetter = -1;

	m_pDialogTextBlock->SetText(FText::FromString(m_TextState.TextList[m_TextState.CurrentIndex]));

	//if (m_TextState.TextList.Num() < m_TextState.CurrentIndex && m_TextState.CurrentLetter < m_TextState.TextList[m_TextState.CurrentIndex].Len())
	//{
		//FString CurrentText = m_pDialogTextBlock->GetText().ToString();
		//FString RemainingText = m_TextState.TextList[m_TextState.CurrentIndex].RightChop(m_TextState.CurrentLetter + 1);
		//CurrentText += RemainingText;
		//m_pDialogTextBlock->SetText(FText::FromString(CurrentText));
	//}

	while (m_TextState.CurrentIndex < m_TextState.TextList.Num())
	{
		m_TextState.CurrentIndex++;
		if (m_TextState.CurrentIndex >= m_TextState.TextList.Num())
		{
			break;
		}
		FString CurrentText = m_pDialogTextBlock->GetText().ToString();

		// Get Size from DialogBox
		FVector2D size = m_pDialogTextBlock->GetCachedGeometry().GetLocalSize();

		FString testLine = m_TextState.CurrentLine + " " + m_TextState.TextList[m_TextState.CurrentIndex];

		const TSharedRef<FSlateFontMeasure> FontMeasure = FSlateApplication::Get().GetRenderer()->GetFontMeasureService();
		if (FontMeasure->Measure(testLine, m_pDialogTextBlock->Font).X > size.X - 125)
		{
			// Add new line to DialogBox
			m_TextState.CurrentLine = m_TextState.TextList[m_TextState.CurrentIndex];

			CurrentText += "\n";
			CurrentText += m_TextState.TextList[m_TextState.CurrentIndex];

		}
		else
		{
			m_TextState.CurrentLine += " " + m_TextState.TextList[m_TextState.CurrentIndex];

			CurrentText += " " + m_TextState.TextList[m_TextState.CurrentIndex];
		}

		// Set DialogBox to contain text
		m_pDialogTextBlock->SetText(FText::FromString(CurrentText));
	}
}

FString DialogAction::GetActionMapKey() const
{
	return ACTION_KEY;
}