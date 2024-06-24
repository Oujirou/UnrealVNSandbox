// Fill out your copyright notice in the Description page of Project Settings.


#include "DataManager.h"

DataManager::DataManager()
{
	LoadData();
}

DataManager::~DataManager()
{
	for (auto& Chapter : m_mChapterData)
	{
		delete Chapter.Value;
	}

	for (auto& Character : m_mCharacterData)
	{
		delete Character.Value;
	}

	for (auto& Environment : m_mEnvironmentData)
	{
		delete Environment.Value;
	}

	delete m_pEntrypointData;
}

void DataManager::ListFilesInDirectory(const FString& ProjectDirectory, TArray<FString>& Files, FString Text)
{
	FString BaseDataPath = FPaths::ProjectContentDir() + ProjectDirectory;

	IFileManager::Get().FindFiles(Files, *BaseDataPath, *Text);
}

void DataManager::LoadChapterData()
{
	FString RelativeDirectory = "../Data/Chapters";
	TArray<FString> Files;

	ListFilesInDirectory(RelativeDirectory, Files);

	for (FString File : Files)
	{
		FString FilePath = FPaths::ProjectContentDir() + RelativeDirectory + "/" + File;

		StoryChapterData* ChapterData = new StoryChapterData();
		ChapterData->InitFromJson(FilePath);

		m_mChapterData.Add(ChapterData->GetChapterKey(), ChapterData);
	}
}

void DataManager::LoadCharacterData()
{
	FString RelativeDirectory = "../Data/Characters";
	TArray<FString> Files;

	ListFilesInDirectory(RelativeDirectory, Files);

	for (FString File : Files)
	{
		FString FilePath = FPaths::ProjectContentDir() + RelativeDirectory + "/" + File;

		StoryCharacterData* CharacterData = new StoryCharacterData();
		CharacterData->InitFromJson(FilePath);

		m_mCharacterData.Add(CharacterData->GetKey(), CharacterData);
	}
}

void DataManager::LoadEnvironmentData()
{
	FString RelativeDirectory = "../Data/Environments";
	TArray<FString> Files;

	ListFilesInDirectory(RelativeDirectory, Files);

	for (FString File : Files)
	{
		FString FilePath = FPaths::ProjectContentDir() + RelativeDirectory + "/" + File;

		StoryEnvironmentData* EnvironmentData = new StoryEnvironmentData();
		EnvironmentData->InitFromJson(FilePath);

		// Add to map
		m_mEnvironmentData.Add(EnvironmentData->GetKey(), EnvironmentData);
	}

}

void DataManager::LoadData()
{
	if (m_bInitialized)
		return;

	LoadChapterData();
	LoadCharacterData();
	LoadEnvironmentData();

	FString EntrypointPath = FPaths::ProjectContentDir() + "../Data/Entrypoint.json";

	m_pEntrypointData = new StoryEntrypointData();
	m_pEntrypointData->InitFromJson(EntrypointPath);

	FString PositionPath = FPaths::ProjectContentDir() + "../Data/Positions.json";

	m_pPositionData = new StoryPositionData();
	m_pPositionData->InitFromJson(PositionPath);

	m_bInitialized = true;
}