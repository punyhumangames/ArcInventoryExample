// Copyright 2023 Puny Human, Licensed under either the MIT or Apache 2.0 license.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ArcInvExampleBPFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class ARCINVENTORYEXAMPLE5_API UArcInvExampleBPFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
		
	UFUNCTION(BlueprintCallable, meta=(DeterminesOutputType=Class))
	static UObject* CreateObject(TSubclassOf<UObject> Class, UObject* Outer);
	
};
