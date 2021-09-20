// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Rotators.h"
#include "RoomBase.h"
#include "GameFramework/Actor.h"
#include "CentralUnit.generated.h"

UCLASS()
class LJMUFPS425_API ACentralUnit : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USceneComponent* CentralUnitComponent;
	UPROPERTY(VisibleDefaultsOnly, Category = Input)
		class UInputComponent* Input;
	
public:	
	ACentralUnit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Get Rooms and Rotators
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Rooms)
		TArray<ARoomBase*>					TotalRooms;

	UPROPERTY(EditAnywhere, Category = Rotators)
		TArray<ARotators*>	RotatorArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TArray<ARoomBase*>					RotatingRooms;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PRotators)
		TSubclassOf<class ARotators>	Rotator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TransformArray)
		TArray<FTransform> TransformArray;



	// Private Functions

private:
	void ResetValues();

	void SetupRotators();

	void SetupFront();
	void SetupBack();
	void SetupLeft();
	void SetupRight();
	void SetupUp();
	void SetupDown();

	void RotateRotator(ARotators* pRotator, float pRotation, float pDeltaTime);

	void CompletionCheck();


	// Private Member Variables
private:

	bool ClockWise;
	bool AddTransforms;

	//Used for the switch case
	int Rotations; // 0 - 6 (None - Front - Back - Left - Right - Up - Down

	ARotators* RotatorF;
	ARotators* RotatorB;
	ARotators* RotatorL;
	ARotators* RotatorR;
	ARotators* RotatorU;
	ARotators* RotatorD;

	float RotatorRotationValue;

	APlayerController* PlayerController;


};
