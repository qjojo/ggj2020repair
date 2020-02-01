// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <unordered_map>
#include <string>

using namespace std;

/**
 * 
 */
class GGJ2020REPAIR_API PlayerProgressFlags
{
public:
	PlayerProgressFlags();
	~PlayerProgressFlags();
	UFUNCTION(BlueprintPure, Category = "cpp exports");
	static bool GetPlayerFlag(string flag);
	UFUNCTION(BlueprintCallable, Category = "cpp exports");
	static void SetPlayerFlag(string flag, bool v);
private:
	const unordered_map<string, bool> data = {};
};
