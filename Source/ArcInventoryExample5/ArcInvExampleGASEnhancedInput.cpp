// Copyright 2023 Puny Human, Licensed under either the MIT or Apache 2.0 license.


#include "ArcInvExampleGASEnhancedInput.h"
#include "InputAction.h"
#include "AbilitySystemComponent.h"
#include "EnhancedInputComponent.h"

const int32 InputIndexOffset = 0xFFFF0000;

int32 UArcInvExampleGASEnhancedInput::GetOrAddInputAction(UAbilitySystemComponent* ASC, UInputAction* Action, ETriggerEvent StartTriggerEvent, ETriggerEvent EndTriggerEvent)
{
	if (!IsValid(ASC))
	{
		return INDEX_NONE;
	}
	if (!IsValid(Action))
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

	if (int32 FoundAction = InputActionArray.Find(Action); FoundAction != INDEX_NONE)
	{
		return FoundAction + InputIndexOffset; //Offset this into the upper bound of the integer, so that way we don't collide with any other bindings
	}


	//Get the InputComponent for this ASC.  It was created on the first binding, but if there are many bindings we need to reuse it
	if (ASCInputComponents.Contains(ASC))
	{
		UInputAction* InputAction = Action;
		int32 ActionBindingIndex = InputActionArray.Add(InputAction) + InputIndexOffset;
		//The EnhancedInputComponent can be null here legitimately.  We only create these for input consuming clients
		//However, the input index _does_ need to be synchronized.  So if we don't have an input component here, still return that ID.
		if (UEnhancedInputComponent* InputComponent = ASCInputComponents[ASC])
		{
			InputComponent->BindAction(InputAction, StartTriggerEvent, ASC, &UAbilitySystemComponent::AbilityLocalInputPressed, ActionBindingIndex);

			InputComponent->BindAction(InputAction, EndTriggerEvent, ASC, &UAbilitySystemComponent::AbilityLocalInputReleased, ActionBindingIndex);
			InputComponent->BindAction(InputAction, ETriggerEvent::Canceled, ASC, &UAbilitySystemComponent::AbilityLocalInputReleased, ActionBindingIndex);

		}
		return ActionBindingIndex; //Offset this into the upper bound of the integer, so that way we don't collide with any other bindings
	}

	return INDEX_NONE;
}

void UArcInvExampleGASEnhancedInput::RemoveInputAction(UAbilitySystemComponent* ASC, UInputAction* Action)
{
	if (BoundInputActions.Contains(ASC))
	{
		TArray<UInputAction*>& InputActionArray = BoundInputActions[ASC];
		InputActionArray.Remove(Action);
		if (InputActionArray.Num() == 0)
		{
			CleanupInputActions(ASC);
		}
	}
}

void UArcInvExampleGASEnhancedInput::CleanupInputActions(UAbilitySystemComponent* ActorComponent)
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
