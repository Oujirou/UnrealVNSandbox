// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JsonHandler.h"

/**
 * 
 */
class UNREALVNSANDBOX_API BaseStoryData : public JsonHandler
{
public:
	BaseStoryData();
	virtual ~BaseStoryData() = 0;

	virtual void InitFromJson(FString path) = 0;
};
