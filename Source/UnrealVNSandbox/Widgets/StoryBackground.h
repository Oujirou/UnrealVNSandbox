// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "StoryBackground.generated.h"

/**
 * 
 */
UCLASS()
class UNREALVNSANDBOX_API UStoryBackground : public UUserWidget
{
	GENERATED_BODY()

	bool m_bAnimationComplete = true;

	void AnimationComplete();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	UImage* BackgroundImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	UWidgetAnimation* FadeAnimation;

	void SetBackgroundImage(FString image);

	void Animate();
	
	void SendToBack();

	bool IsAnimationComplete() const { return m_bAnimationComplete; }

	UImage* GetBackgroundImage() const { return BackgroundImage; }
};
