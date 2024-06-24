// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Slider.h"

/**
 *	Called at the launch of the gamee to set the volume levels, also used in the option menu.
 */
class UNREALVNSANDBOX_API Options
{
	float MasterVolume = 1.0;
	float MusicVolume = 1.0;
	float SFXVolume = 1.0;
	float VoiceVolume = 1.0;

public:
	void SaveOptions();
	void LoadOptions();
	void SyncVolume();

	void SetMasterVolume(float volume) { MasterVolume = volume; }
	void SetMusicVolume(float volume) { MusicVolume = volume; }
	void SetSFXVolume(float volume) { SFXVolume = volume; }
	void SetVoiceVolume(float volume) { VoiceVolume = volume; }

	float GetMasterVolume() const { return MasterVolume; }
	float GetMusicVolume() const { return MusicVolume; }
	float GetSFXVolume() const { return SFXVolume; }
	float GetVoiceVolume() const { return VoiceVolume; }
};

template <typename ObjClass>
static FORCEINLINE ObjClass* LoadObjFromPath(const FName& Path)
{
	if (Path == NAME_None) return NULL;
	if (Path.ToString().Contains("None")) return NULL;
	return Cast<ObjClass>(StaticLoadObject(ObjClass::StaticClass(), NULL, *Path.ToString()));
}