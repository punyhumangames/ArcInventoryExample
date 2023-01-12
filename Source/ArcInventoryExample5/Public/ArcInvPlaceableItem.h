// Copyright 2023 Puny Human, Licensed under either the MIT or Apache 2.0 license.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ArcInvPlaceableItem.generated.h"

class AArcItemStackWorldObject;

UCLASS()
class ARCINVENTORYEXAMPLE5_API AArcInvPlaceableItem : public AActor
{
	GENERATED_BODY()
private:
	UPROPERTY()
		UStaticMeshComponent* EditorStaticMesh;

public:
	// Sets default values for this actor's properties
	AArcInvPlaceableItem();

	UPROPERTY(EditAnywhere, Category = "Item", Instanced)
		class UArcItemGenerator* ItemGenerator;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Item")
		AArcItemStackWorldObject* SpawnedItemStack;

	UPROPERTY(EditAnywhere, Category = "Item")
		bool bSpawnItemOnBeginPlay;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintCallable, Category = "Item")
		virtual AArcItemStackWorldObject* SpawnWorldItem();

	UFUNCTION()
		virtual void OnSpawnedItemStackConsumed(AActor* Actor);


#if WITH_EDITOR
public:
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

#endif

};
