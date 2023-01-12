// Copyright 2023 Puny Human, Licensed under either the MIT or Apache 2.0 license.


#include "ArcInvEnhancedInputSubsystem.h"
#include "ArcInvEnhancedInputBinder.h"
#include "InputAction.h"
#include "AbilitySystemComponent.h"
#include "EnhancedInputComponent.h"

int32 UArcInvEnhancedInputSubsystem::GetOrAddInputAction(UAbilitySystemComponent* ASC, UArcInvEnhancedInputBinder* InBinder)
{
	if (!IsValid(ASC))
	{
		return INDEX_NONE;
	}
	if (!IsValid(InBinder))
	{
		return INDEX_NONE;
	}
	TArray<UInputAction*>& InputActionArray = BoundInputActions.FindOrAdd(ASC);
	if (InputActionArray.Num() == 0)
	{
		//Bind to the ASC's destroyed event
		//ASC->OnComponentDeactivated.AddDynamic(this, &ThisClass::CleanupInputActions);
		//Create an enhanced input component and give this to the ASC's player controller.  Since the ActionArray is 0, that means it needs to be created.
		
		if (APlayerController* PC = ASC->AbilityActorInfo->PlayerController.Get())
		{	
			if (PC->IsLocalController())
			{
				UEnhancedInputComponent* Component = NewObject<UEnhancedInputComponent>(PC);
				Component->RegisterComponent();
				PC->PushInputComponent(Component);
				ASCInputComponents.Add(ASC, Component);
			}
		}
	}

	if (int32 FoundAction = InputActionArray.Find(InBinder->InputAction); FoundAction != INDEX_NONE)
	{
		return FoundAction;
	}
	

	//Get the InputComponent for this ASC.  It was created on the first binding, but if there are many bindings we need to reuse it
	if (ASCInputComponents.Contains(ASC))
	{
		UInputAction* InputAction = InBinder->InputAction;
		int32 ActionBindingIndex = InputActionArray.Add(InputAction);
		//The EnhancedInputComponent can be null here legitimately.  We only create these for input consuming clients
		//However, the input index _does_ need to be synchronized.  So if we don't have an input component here, still return that ID.
		if (UEnhancedInputComponent* InputComponent = ASCInputComponents[ASC])
		{	
			InputComponent->BindAction(InputAction, InBinder->StartTriggerEvent, ASC, &UAbilitySystemComponent::AbilityLocalInputPressed, ActionBindingIndex);

			InputComponent->BindAction(InputAction, InBinder->EndTriggerEvent, ASC, &UAbilitySystemComponent::AbilityLocalInputReleased, ActionBindingIndex);
			InputComponent->BindAction(InputAction, ETriggerEvent::Canceled, ASC, &UAbilitySystemComponent::AbilityLocalInputReleased, ActionBindingIndex);
			
		}
		return ActionBindingIndex;
	}

	return INDEX_NONE;
}

void UArcInvEnhancedInputSubsystem::RemoveInputAction(UAbilitySystemComponent* ASC, UArcInvEnhancedInputBinder* InBinder)
{
	if (BoundInputActions.Contains(ASC))
	{
		TArray<UInputAction*>& InputActionArray = BoundInputActions[ASC];
		InputActionArray.Remove(InBinder->InputAction);
		if (InputActionArray.Num() == 0)
		{
			CleanupInputActions(ASC);
		}
	}
}

void UArcInvEnhancedInputSubsystem::CleanupInputActions(UActorComponent* ActorComponent)
{
	//If the ASC is deactivated, purge it's bound actions
	if (UAbilitySystemComponent* ASC = Cast<UAbilitySystemComponent>(ActorComponent))
	{
		BoundInputActions.Remove(ASC);
		//If we have an Input Component we put on the player controller, destroy it now.
		if (ASCInputComponents.Contains(ASC))
		{
			if (UEnhancedInputComponent* InputComp = ASCInputComponents[ASC])
			{
				if (APlayerController* PC = Cast<APlayerController>(InputComp->GetOwner()))
				{
					PC->PopInputComponent(InputComp);
				}
				InputComp->DestroyComponent();
				ASCInputComponents.Remove(ASC);
			}
		}
	}
}
