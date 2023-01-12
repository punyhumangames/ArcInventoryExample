// Copyright 2023 Puny Human, Licensed under either the MIT or Apache 2.0 license.

#pragma once

#include "CoreMinimal.h"
#include "Input/ArcInvInputBinder.h"
#include "ArcInvEnhancedInputBinder.generated.h"

class UInputAction;
enum class ETriggerEvent : uint8;

/**
 * 
 */
UCLASS()
class ARCINVENTORYENHANCEDINPUT_API UArcInvEnhancedInputBinder : public UArcInvInputBinder
{
	GENERATED_BODY()
public:
	UArcInvEnhancedInputBinder();

	void InitInputBindings_Implementation(UAbilitySystemComponent* ASC, UArcItemStackModular* ItemStack) override;

	void DeInitInputBindings_Implementation(UAbilitySystemComponent* ASC, UArcItemStackModular* ItemStack) override;

	int32 GetInputBinding_Implementation(UAbilitySystemComponent* ASC, TSubclassOf<UGameplayAbility> AbilityToGrant) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	UInputAction* InputAction;

	//Which Enhanced Input Trigger event to use to count as "Input Pressed" for the ASC.  
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", AdvancedDisplay)
	ETriggerEvent StartTriggerEvent;

	//Which Enhanced Input Trigger Event to use to count as "Input Released" for the ASC.  "Canceled" is always an input release.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", AdvancedDisplay)
	ETriggerEvent EndTriggerEvent;

	int32 BoundInputId;
};
