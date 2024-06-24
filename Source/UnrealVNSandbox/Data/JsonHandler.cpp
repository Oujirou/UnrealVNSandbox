// Fill out your copyright notice in the Description page of Project Settings.


#include "JsonHandler.h"

JsonHandler::JsonHandler()
{
}

JsonHandler::~JsonHandler()
{
}

// Implement the LoadJsonData function
TSharedPtr<FJsonObject> JsonHandler::LoadJsonData(FString path)
{
	// Create a variable to hold the data
	FString JsonString;
	// Read the file into the JsonString variable
	FFileHelper::LoadFileToString(JsonString, *path);
	// If JsonString is empty, return nullptr
	if (JsonString.IsEmpty())
		return nullptr;
	// Create a variable to hold the data as a JSON object
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	// Create a variable to hold the data as a JSON reader
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonString);
	// Deserialize the JSON data
	FJsonSerializer::Deserialize(JsonReader, JsonObject);
	// Return the JSON object
	return JsonObject;
}