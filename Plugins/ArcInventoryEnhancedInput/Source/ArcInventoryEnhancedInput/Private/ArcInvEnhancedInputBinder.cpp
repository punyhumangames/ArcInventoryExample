// Copyright 2023 Puny Human, Licensed under either the MIT or Apache 2.0 license.


#include "ArcInvEnhancedInputBinder.h"
#include "AbilitySystemComponent.h"
#include "ArcInvEnhancedInputSubsystem.h"
#include "InputAction.h"

UArcInvEnhancedInputBinder::UArcInvEnhancedInputBinder()
{
	BoundInputId = INDEX_NONE;
	StartTriggerEvent = ETriggerEvent::Triggered;
	EndTriggerEvent = ETriggerEvent::Completed;
}

void UArcInvEnhancedInputBinder::InitInputBindings_Implementation(UAbilitySystemComponent* ASC, UArcItemStackModular* ItemStack)
{
	UWorld* World = GEngine->GetWorldFromContextObject(ASC, EGetWorldErrorMode::LogAndReturnNull);

	if (!IsValid(World))
	{
		return;
	}
	if (!IsValid(InputAction))
	{
		return;
	}	

	if (auto* SubSys = World->GetGameInstance()->GetSubsystem<UArcInvEnhancedInputSubsystem>())
	{
		BoundInputId = SubSys->GetOrAddInputAction(ASC, this);
	}
}

void UArcInvEnhancedInputBinder::DeInitInputBindings_Implementation(UAbilitySystemComponent* ASC, UArcItemStackModular* ItemStack)
{
	UWorld* World = GEngine->GetWorldFromContextObject(ASC, EGetWorldErrorMode::LogAndReturnNull);
	if (!IsValid(World))
	{
		return;
	}
	if (!IsValid(InputAction))
	{
		return;
	}
	if (auto* SubSys = World->GetGameInstance()->GetSubsystem<UArcInvEnhancedInputSubsystem>())
	{
		SubSys->RemoveInputAction(ASC, this);
		BoundInputId = INDEX_NONE;
	}
}

int32 UArcInvEnhancedInputBinder::GetInputBinding_Implementation(UAbilitySystemComponent* ASC, TSubclassOf<UGameplayAbility> AbilityToGrant)
{
	return BoundInputId;
}
