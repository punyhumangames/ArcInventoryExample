// Copyright 2023 Puny Human, Licensed under either the MIT or Apache 2.0 license.


#include "ArcInvPlaceableItem.h"
#include "EngineMinimal.h"
#include "ArcInventory.h"
#include "Modular/Fragments/ArcItemFragment_StaticMesh.h"
#include "ArcInventoryDeveloperSettings.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "Modular/ArcItemStackModular.h"

// Sets default values
AArcInvPlaceableItem::AArcInvPlaceableItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
#if WITH_EDITOR
	EditorStaticMesh = CreateEditorOnlyDefaultSubobject<UStaticMeshComponent>(TEXT("EditorVis"));
	if (IsValid(EditorStaticMesh))
	{
		EditorStaticMesh->SetupAttachment(RootComponent);
		EditorStaticMesh->bIsEditorOnly = true;
		EditorStaticMesh->bHiddenInGame = true;
		EditorStaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
#endif

}

// Called when the game starts or when spawned
void AArcInvPlaceableItem::BeginPlay()
{
	Super::BeginPlay();

	if (bSpawnItemOnBeginPlay)
	{
		SpawnWorldItem();
	}
	
}

AArcItemStackWorldObject* AArcInvPlaceableItem::SpawnWorldItem()
{
	if (GetLocalRole() != ROLE_Authority)
	{
		return nullptr;
	}

	if (IsValid(SpawnedItemStack))
	{
		return SpawnedItemStack;
	}

	if (!IsValid(ItemGenerator))
	{
		return nullptr;
	}

	FTransform Transform = GetActorTransform();
	FArcItemGeneratorContext Context;
	UArcItemStackBase* ItemStack = ItemGenerator->GenerateItemStack(Context);

	AArcItemStackWorldObject* StackObject = GetWorld()->SpawnActorDeferred<AArcItemStackWorldObject>(GetDefault<UArcInventoryDeveloperSettings>()->ItemStackWorldObjectClass, Transform);
	if (IsValid(StackObject))
	{
		StackObject->SetInventoryStack(ItemStack);
		UGameplayStatics::FinishSpawningActor(StackObject, Transform);
		SpawnedItemStack = StackObject;
		return StackObject;
	}


	return SpawnedItemStack;
}

void AArcInvPlaceableItem::OnSpawnedItemStackConsumed(AActor* Actor)
{
	if (Actor == SpawnedItemStack)
	{
		SpawnedItemStack->OnDestroyed.RemoveDynamic(this, &ThisClass::OnSpawnedItemStackConsumed);
		SpawnedItemStack = nullptr;
	}
}

#if WITH_EDITOR
void AArcInvPlaceableItem::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	if (PropertyChangedEvent.Property && PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED(AArcInvPlaceableItem, ItemGenerator) && IsValid(ItemGenerator))
	{
		FArcItemGeneratorContext Context;
		UArcItemStackBase* ItemStack = ItemGenerator->GenerateItemStack(Context);

		if(UArcItemStackModular* MIS = Cast<UArcItemStackModular>(ItemStack))
		{
			if (IsValid(EditorStaticMesh))
			{
				if (UArcItemFragment_StaticMesh* SMFragment = MIS->FindFirstFragment<UArcItemFragment_StaticMesh>([](UArcItemFragment_StaticMesh* Fragment) -> bool {
					return Fragment->FragmentTags.HasTag(FArcInvWorldItemMeshTag);
					}))
				{
					TSoftObjectPtr<UStaticMesh> Mesh = SMFragment->Mesh;
					UAssetManager::GetStreamableManager().RequestAsyncLoad(SMFragment->Mesh.ToSoftObjectPath(), FStreamableDelegate::CreateWeakLambda(this, [this, Mesh]
					{
						if(Mesh.IsValid())
						{
							EditorStaticMesh->SetStaticMesh(Mesh.Get());
						}
					}));
				}
			}
		}
	}
}
#endif



