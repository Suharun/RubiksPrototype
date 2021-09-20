// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Math/Rotator.h"
#include "Rotators.generated.h"

UCLASS()
class LJMUFPS425_API ARotators : public AActor
{
	GENERATED_BODY()
		UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USceneComponent* SceneComponent;
public:	
	// Sets default values for this actor's properties
	ARotators();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	FRotator InputRotation(float CurrentRotation);


	bool RotateOnX;
	bool RotateOnY;
	bool RotateOnZ;

};
