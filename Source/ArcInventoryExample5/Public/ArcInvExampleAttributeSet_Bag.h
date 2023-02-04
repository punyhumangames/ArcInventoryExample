// Copyright 2023 Puny Human, Licensed under either the MIT or Apache 2.0 license.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "ArcInvExampleAttributeSet_Bag.generated.h"

/**
 * 
 */
UCLASS()
class ARCINVENTORYEXAMPLE5_API UArcInvExampleAttributeSet_Bag : public UAttributeSet
{
	GENERATED_BODY()
public:
	UArcInvExampleAttributeSet_Bag(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Attributes)
	float BagSize;
	
};
