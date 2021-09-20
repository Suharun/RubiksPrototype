// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/PointLightComponent.h"
#include "EnemyAICharacter.h"
#include "InteractableObject.h"
#include "RoomBase.generated.h"

UCLASS()
class LJMUFPS425_API ARoomBase : public AActor
{
	GENERATED_BODY()
		UPROPERTY(VisibleDefaultsOnly, Category = SceneComponent)
		class USceneComponent* OriginPoint;

	UPROPERTY(VisibleDefaultsOnly, Category = Lighting)
		class UPointLightComponent* Light;

	UPROPERTY(VisibleDefaultsOnly, Category = Structure)
		class UStaticMeshComponent* SideA;
	UPROPERTY(VisibleDefaultsOnly, Category = Structure)
		class UStaticMeshComponent* SideB;
	UPROPERTY(VisibleDefaultsOnly, Category = Structure)
		class UStaticMeshComponent* SideC;
	UPROPERTY(VisibleDefaultsOnly, Category = Structure)
		class UStaticMeshComponent* SideD;
	UPROPERTY(VisibleDefaultsOnly, Category = Structure)
		class UStaticMeshComponent* SideE;
	UPROPERTY(VisibleDefaultsOnly, Category = Structure)
		class UStaticMeshComponent* SideF;

public:	
	// Sets default values for this actor's properties
	ARoomBase();

	void Complete() {
		Light->SetLightColor(FLinearColor::Blue);
		IsComplete;
	}

	// Required for the Central Unit to check that the game is finished when all rooms are completed.
	bool GetIsComplete() { return this->IsComplete; }

	void Puzzle();

	void Enemy();

	void Loot();

	void Target();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RoomType)
		bool IsPuzzle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RoomType)
		bool IsEnemy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RoomType)
		bool IsLoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RoomType)
		bool IsTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemies)
		TArray<AEnemyAICharacter*> Enemies;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Puzzle)
		TArray<AInteractableObject*> InteractableObjects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Puzzle)
		AInteractableObject* ReceiverObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Loot)
		TArray<AInteractableObject*> LootObjects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Target)
		TArray<AInteractableObject*> TargetObjects;
private:
	bool IsComplete;
};
