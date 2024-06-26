// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/HyPlayerCharacter.h"
#include "HyPlayerCharacter.h"

AHyPlayerCharacter::AHyPlayerCharacter()
{
}

FString AHyPlayerCharacter::GetPlayerName()
{
	FString strID = FString::Printf(TEXT("%lld"), ObjectID);

	return strID;
}
