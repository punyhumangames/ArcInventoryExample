// Copyright 2023 Puny Human, Licensed under either the MIT or Apache 2.0 license.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "InputTriggers.h"
#include "ArcInvExampleGASEnhancedInput.generated.h"

class UInputAction;
class UAbilitySystemComponent;
class UEnhancedInputComponent;

/**
 * 
 */
UCLASS()
class ARCINVENTORYEXAMPLE5_API UArcInvExampleGASEnhancedInput : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	int32 GetOrAddInputAction(class UAbilitySystemComponent* ASC, UInputAction* Action, ETriggerEvent StartTriggerEvent = ETriggerEvent::Triggered, ETriggerEvent EndTriggerEvent = ETriggerEvent::Completed);
	UFUNCTION(BlueprintCallable)
	void RemoveInputAction(class UAbilitySystemComponent* ASC, UInputAction* InBinder);
private:
	void CleanupInputActions(UAbilitySystemComponent* ActorComponent);

	TMap<UAbilitySystemComponent*, TArray<UInputAction*>> BoundInputActions;

	UPROPERTY()
		TMap<UAbilitySystemComponent*, UEnhancedInputComponent*> ASCInputComponents;
};
