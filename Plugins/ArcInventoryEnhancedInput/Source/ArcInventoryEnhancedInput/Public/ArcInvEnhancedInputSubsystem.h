// Copyright 2023 Puny Human, Licensed under either the MIT or Apache 2.0 license.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ArcInvEnhancedInputSubsystem.generated.h"

class UArcInvEnhancedInputBinder;

class UInputAction;
class UAbilitySystemComponent;
class UEnhancedInputComponent;

/**
 * 
 */
UCLASS()
class ARCINVENTORYENHANCEDINPUT_API UArcInvEnhancedInputSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	int32 GetOrAddInputAction(class UAbilitySystemComponent* ASC, UArcInvEnhancedInputBinder* InBinder);
	void RemoveInputAction(class UAbilitySystemComponent* ASC, UArcInvEnhancedInputBinder* InBinder);
	
private:
	UFUNCTION()
	void CleanupInputActions(UActorComponent* ActorComponent);

	TMap<UAbilitySystemComponent*,TArray<UInputAction*>> BoundInputActions;

	UPROPERTY()
	TMap<UAbilitySystemComponent*, UEnhancedInputComponent*> ASCInputComponents;
};
