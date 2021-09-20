// Fill out your copyright notice in the Description page of Project Settings.


#include "Rotators.h"

// Sets default values
ARotators::ARotators()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RotatorLocation"));
	SceneComponent->SetRelativeLocation(FVector(0, 0, 0));

	RotateOnX = RotateOnY = RotateOnZ = false;
}

// Called when the game starts or when spawned
void ARotators::BeginPlay()
{	
	Super::BeginPlay();
	FQuat Rotation(0, 0, 0, 0);
	this->SetActorLocation(FVector(900, 900, 1900));
	this->SetActorRotation(Rotation);
}

// Called every frame
void ARotators::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FRotator ARotators::InputRotation(float CurrentRotation)
{
	FRotator NewRotation;
	if (RotateOnX)
	{
		NewRotation.Roll = CurrentRotation;
		NewRotation.Pitch = 0;
		NewRotation.Yaw = 0;
	}
	else if (RotateOnY)
	{
		NewRotation.Roll = 0;
		NewRotation.Pitch = CurrentRotation;
		NewRotation.Yaw = 0;
	}
	else if (RotateOnZ)
	{
		NewRotation.Yaw = CurrentRotation;
		NewRotation.Pitch = 0;
		NewRotation.Roll = 0;
	}
	return NewRotation;
}