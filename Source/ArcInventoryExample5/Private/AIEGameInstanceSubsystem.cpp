// Copyright 2023 Puny Human, Licensed under either the MIT or Apache 2.0 license.


#include "AIEGameInstanceSubsystem.h"
#include "AbilitySystemGlobals.h"

void UAIEGameInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UAbilitySystemGlobals::Get().InitGlobalData();
}
