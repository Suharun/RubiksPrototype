// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LJMUFPS425Character.h"
#include "Components/CapsuleComponent.h"
#include "EnemyAICharacter.generated.h"

UCLASS()
class LJMUFPS425_API AEnemyAICharacter : public ACharacter
{
	GENERATED_BODY()

		UPROPERTY(VisibleDefaultsOnly, Category = Collision)
		class UCapsuleComponent* MeshCapsule;

public:
	// Sets default values for this character's properties
	AEnemyAICharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool isInRange(ALJMUFPS425Character* pPlayerRef, float pRange);
	bool isSameRotation(AActor* pRoom);

	void MoveToTarget(ALJMUFPS425Character* pPlayerRef, float pMovementSpeed);

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles strafing movement, left and right */
	void MoveRight(float Val);

	

public:
	bool IsActive;


private:
	ALJMUFPS425Character* PlayerRef;

	float MovementSpeed;
	float AIRange;

	FVector MovementVector;

	
};

