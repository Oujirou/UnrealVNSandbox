// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class UNREALVNSANDBOX_API JsonHandler
{
protected:
	TSharedPtr<FJsonObject> LoadJsonData(FString path);
public:
	JsonHandler();
	~JsonHandler();
};
