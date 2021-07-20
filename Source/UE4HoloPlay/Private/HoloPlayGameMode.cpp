// Fill out your copyright notice in the Description page of Project Settings.


#include "HoloPlayGameMode.h"

#include "Pawn/HoloPlayCharacter.h"

AHoloPlayGameMode::AHoloPlayGameMode()
{
	DefaultPawnClass = AHoloPlayCharacter::StaticClass();
}
