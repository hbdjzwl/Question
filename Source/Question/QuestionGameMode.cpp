// Copyright Epic Games, Inc. All Rights Reserved.

#include "QuestionGameMode.h"
#include "QuestionCharacter.h"
#include "UObject/ConstructorHelpers.h"

AQuestionGameMode::AQuestionGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
