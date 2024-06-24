// Fill out your copyright notice in the Description page of Project Settings.


#include "Options.h"
#include "Sound/SoundMix.h"
#include "Kismet/GameplayStatics.h"

// Implement the SaveOptions function
void Options::SaveOptions()
{
	// Create a Json Object
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	JsonObject->SetStringField("MasterVolume", FString::SanitizeFloat(MasterVolume));
	JsonObject->SetStringField("MusicVolume", FString::SanitizeFloat(MusicVolume));
	JsonObject->SetStringField("SFXVolume", FString::SanitizeFloat(SFXVolume));
	JsonObject->SetStringField("VoiceVolume", FString::SanitizeFloat(VoiceVolume));

	// Create a Json String
	FString JsonString;
	TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<>::Create(&JsonString);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);

	// Save the Json String to a file
	FString SaveDirectory = FPaths::ProjectSavedDir();
	FString FileName = "Options.json";
	FString AbsoluteFilePath = SaveDirectory + FileName;

	FFileHelper::SaveStringToFile(JsonString, *AbsoluteFilePath);

	UE_LOG(LogTemp, Warning, TEXT("Saved to: %s"), *AbsoluteFilePath);
}

// Implement the LoadOptions function
void Options::LoadOptions()
{
	// Load the Json String from a file
	FString LoadDirectory = FPaths::ProjectSavedDir();
	FString FileName = "Options.json";
	FString AbsoluteFilePath = LoadDirectory + FileName;

	FString JsonString;
	FFileHelper::LoadFileToString(JsonString, *AbsoluteFilePath);
	
	if (JsonString.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("No file found at: %s"), *AbsoluteFilePath);
		SyncVolume();
		return;
	}

	// Create a Json Object from the Json String
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonString);
	FJsonSerializer::Deserialize(JsonReader, JsonObject);

	// Set the Options values from the Json Object
	MasterVolume = FCString::Atof(*JsonObject->GetStringField("MasterVolume"));
	MusicVolume = FCString::Atof(*JsonObject->GetStringField("MusicVolume"));
	SFXVolume = FCString::Atof(*JsonObject->GetStringField("SFXVolume"));
	VoiceVolume = FCString::Atof(*JsonObject->GetStringField("VoiceVolume"));

	UE_LOG(LogTemp, Warning, TEXT("Loaded from: %s"), *AbsoluteFilePath);
	SyncVolume();
}

// Implement the SyncVolume function
void Options::SyncVolume()
{
	// Set Sound Mix Class modifications
	USoundMix* SoundMixMaster = LoadObjFromPath<USoundMix>(FName("/Game/Blueprints/Sound/SCM_Master"));
	USoundMix* SoundMixMusic = LoadObjFromPath<USoundMix>(FName("/Game/Blueprints/Sound/SCM_Music"));
	USoundMix* SoundMixSFX = LoadObjFromPath<USoundMix>(FName("/Game/Blueprints/Sound/SCM_SFX"));
	USoundMix* SoundMixVoice = LoadObjFromPath<USoundMix>(FName("/Game/Blueprints/Sound/SCM_Voice"));

	USoundClass* SoundClassMaster = LoadObjFromPath<USoundClass>(FName("/Engine/EngineSounds/Master"));
	USoundClass* SoundClassMusic = LoadObjFromPath<USoundClass>(FName("/Engine/EngineSounds/Music"));
	USoundClass* SoundClassSFX = LoadObjFromPath<USoundClass>(FName("/Engine/EngineSounds/SFX"));
	USoundClass* SoundClassVoice = LoadObjFromPath<USoundClass>(FName("/Engine/EngineSounds/Voice"));

	// Get World Context Object
	UWorld* World = GEngine->GetWorldFromContextObject(GEngine->GetWorld(), EGetWorldErrorMode::LogAndReturnNull);

	// Set Sound Mix Class Overrides
	UGameplayStatics::SetSoundMixClassOverride(World, SoundMixMaster, SoundClassMaster, MasterVolume, 1.0, 1.0, true);
	UGameplayStatics::SetSoundMixClassOverride(World, SoundMixMusic, SoundClassMusic, MusicVolume, 1.0, 1.0, true);
	UGameplayStatics::SetSoundMixClassOverride(World, SoundMixSFX, SoundClassSFX, SFXVolume, 1.0, 1.0, true);
	UGameplayStatics::SetSoundMixClassOverride(World, SoundMixVoice, SoundClassVoice, VoiceVolume, 1.0, 1.0, true);
}