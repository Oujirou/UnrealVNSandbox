// Fill out your copyright notice in the Description page of Project Settings.


#include "StoryBackground.h"
#include <Components/CanvasPanelSlot.h>

void UStoryBackground::SetBackgroundImage(FString image)
{
	UTexture2D* texture = LoadObject<UTexture2D>(nullptr, *image);
	BackgroundImage->SetBrushFromTexture(texture);
	// Set alpha to 1.0
	this->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
	BackgroundImage->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
	Cast<UCanvasPanelSlot>(Slot)->SetZOrder(0);
}

void UStoryBackground::Animate()
{
	// Play the animation "Fade" with a duration of 0.5 seconds
	PlayAnimation(FadeAnimation, 0.0f, 1, EUMGSequencePlayMode::Forward);

	// Set Z to 0
	Cast<UCanvasPanelSlot>(Slot)->SetZOrder(1);

	m_bAnimationComplete = false;

	// Set a timer to call AnimationComplete after the animation is done
	//FTimerDelegate TimerDel;
	//TimerDel.BindRaw(this, &UStoryBackground::AnimationComplete);

	//	TODO: This method breaks all backgrounds when moving fast, the animation is not completed when new textures are set.
	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle, this, &UStoryBackground::AnimationComplete, FadeAnimation->GetEndTime(), false);
}

void UStoryBackground::SendToBack()
{
	m_bAnimationComplete = true;
	Cast<UCanvasPanelSlot>(Slot)->SetZOrder(-1);
	this->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.0f));
	BackgroundImage->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.0f));
}

void UStoryBackground::AnimationComplete()
{
	m_bAnimationComplete = true;
	Cast<UCanvasPanelSlot>(Slot)->SetZOrder(-1);
	this->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.0f));
	BackgroundImage->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.0f));
}