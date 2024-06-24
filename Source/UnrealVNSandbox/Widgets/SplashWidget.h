// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "../Config/Options.h"

#include "SplashWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALVNSANDBOX_API USplashWidget : public UUserWidget
{
	GENERATED_BODY()
	
	Options OptionsInstance;

public:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void LoadOptions() { OptionsInstance.LoadOptions(); }
};
