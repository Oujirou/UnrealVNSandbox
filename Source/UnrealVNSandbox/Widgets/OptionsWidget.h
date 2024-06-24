// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "../Config/Options.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

#include "OptionsWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALVNSANDBOX_API UOptionsWidget : public UUserWidget
{
	GENERATED_BODY()

	USlider* SliderMasterVolume;
	USlider* SliderMusicVolume;
	USlider* SliderSFXVolume;
	USlider* SliderVoiceVolume;

	USoundWave* SoundTestMusic;
	USoundWave* SoundTestSFX;
	USoundWave* SoundTestVoice;

	UAudioComponent* SoundTest;
	
	Options OptionsInstance;

public:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetSliders(USlider* MasterVolume, USlider* MusicVolume, USlider* SFXVolume, USlider* VoiceVolume);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SaveOptions();

	void DelegateBinder(FString method, USlider* slider);

	UFUNCTION()
	void OnMasterCaptureBegin();
	UFUNCTION()
	void OnMasterCaptureEnd();
	UFUNCTION()
	void OnMusicCaptureBegin();
	UFUNCTION()
	void OnMusicCaptureEnd();
	UFUNCTION()
	void OnSFXCaptureBegin();
	UFUNCTION()
	void OnSFXCaptureEnd();
	UFUNCTION()
	void OnVoiceCaptureBegin();
	UFUNCTION()
	void OnVoiceCaptureEnd();
};
