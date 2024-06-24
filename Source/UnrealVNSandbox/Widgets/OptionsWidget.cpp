// Fill out your copyright notice in the Description page of Project Settings.


#include "OptionsWidget.h"

void UOptionsWidget::SetSliders(USlider* MasterVolume, USlider* MusicVolume, USlider* SFXVolume, USlider* VoiceVolume)
{
	OptionsInstance.LoadOptions();

	SliderMasterVolume = MasterVolume;
	SliderMusicVolume = MusicVolume;
	SliderSFXVolume = SFXVolume;
	SliderVoiceVolume = VoiceVolume;

	DelegateBinder("Master", SliderMasterVolume);
	DelegateBinder("Music", SliderMusicVolume);
	DelegateBinder("SFX", SliderSFXVolume);
	DelegateBinder("Voice", SliderVoiceVolume);

	SliderMasterVolume->SetValue(OptionsInstance.GetMasterVolume());
	SliderMusicVolume->SetValue(OptionsInstance.GetMusicVolume());
	SliderSFXVolume->SetValue(OptionsInstance.GetSFXVolume());
	SliderVoiceVolume->SetValue(OptionsInstance.GetVoiceVolume());
}

// Implement the SaveOptions function
void UOptionsWidget::SaveOptions()
{
	OptionsInstance.SetMasterVolume(SliderMasterVolume->GetValue());
	OptionsInstance.SetMusicVolume(SliderMusicVolume->GetValue());
	OptionsInstance.SetSFXVolume(SliderSFXVolume->GetValue());
	OptionsInstance.SetVoiceVolume(SliderVoiceVolume->GetValue());

	OptionsInstance.SaveOptions();
}

void UOptionsWidget::DelegateBinder(FString method, USlider* slider)
{
	FString methodBeginName = "On" + method + "CaptureBegin";
	FScriptDelegate BeginDelegate;
	BeginDelegate.BindUFunction(this, *methodBeginName);
	slider->OnControllerCaptureBegin.AddUnique(BeginDelegate);
	slider->OnMouseCaptureBegin.AddUnique(BeginDelegate);

	FString methodEndName = "On" + method + "CaptureEnd";
	FScriptDelegate EndDelegate;
	EndDelegate.BindUFunction(this, *methodEndName);
	slider->OnControllerCaptureEnd.AddUnique(EndDelegate);
	slider->OnMouseCaptureEnd.AddUnique(EndDelegate);
}

void UOptionsWidget::OnMasterCaptureBegin()
{
	FString soundUrl = "/Game/Assets/Audio/Music_Test";
	SoundTestMusic = LoadObjFromPath<USoundWave>(FName(*soundUrl));
	SoundTestMusic->bLooping = true;
	SoundTest = UGameplayStatics::SpawnSound2D(GetWorld(), SoundTestMusic);
}

void UOptionsWidget::OnMasterCaptureEnd()
{
	if (SoundTest)
	{
		SoundTest->Stop();
		SoundTest = NULL;
	}
}

void UOptionsWidget::OnMusicCaptureBegin()
{
	FString soundUrl = "/Game/Assets/Audio/Music_Test";
	SoundTestMusic = LoadObjFromPath<USoundWave>(FName(*soundUrl));
	SoundTestMusic->bLooping = true;
	SoundTest = UGameplayStatics::SpawnSound2D(GetWorld(), SoundTestMusic);
}

void UOptionsWidget::OnMusicCaptureEnd()
{
	if (SoundTest)
	{
		SoundTest->Stop();
		SoundTest = NULL;
	}
}

void UOptionsWidget::OnSFXCaptureBegin()
{
	FString soundUrl = "/Game/Assets/Audio/SFX_Test";
	SoundTestMusic = LoadObjFromPath<USoundWave>(FName(*soundUrl));
	SoundTestMusic->bLooping = true;
	SoundTest = UGameplayStatics::SpawnSound2D(GetWorld(), SoundTestMusic);
}

void UOptionsWidget::OnSFXCaptureEnd()
{
	if (SoundTest)
	{
		SoundTest->Stop();
		SoundTest = NULL;
	}
}

void UOptionsWidget::OnVoiceCaptureBegin()
{
	UE_LOG(LogTemp, Warning, TEXT("Voice Volume Capture Begin"));
}

void UOptionsWidget::OnVoiceCaptureEnd()
{
	UE_LOG(LogTemp, Warning, TEXT("Voice Volume Capture End"));
}