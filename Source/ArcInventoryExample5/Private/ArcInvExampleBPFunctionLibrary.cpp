// Copyright 2023 Puny Human, Licensed under either the MIT or Apache 2.0 license.


#include "ArcInvExampleBPFunctionLibrary.h"

UObject* UArcInvExampleBPFunctionLibrary::CreateObject(TSubclassOf<UObject> Class, UObject* Outer)
{
	return ::NewObject<UObject>(Outer, Class);
}
