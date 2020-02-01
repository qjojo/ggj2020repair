// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerProgressFlags.h"

PlayerProgressFlags::PlayerProgressFlags()
{
	data = unordered_map<string, bool>();
}

PlayerProgressFlags::~PlayerProgressFlags()
{
}

void PlayerProgressFlags::setFlag(string flag, bool v) {
	data.insert({ flag, v });
}

bool PlayerProgressFlags::getFlag(string flag) {
	return data.at(flag);
}