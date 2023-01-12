// Copyright 2023 Puny Human, Licensed under either the MIT or Apache 2.0 license.

#include "ArcInventoryExample5GameMode.h"
#include "ArcInventoryExample5Character.h"
#include "UObject/ConstructorHelpers.h"

AArcInventoryExample5GameMode::AArcInventoryExample5GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
