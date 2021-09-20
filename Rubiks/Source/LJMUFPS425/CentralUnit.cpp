// Fill out your copyright notice in the Description page of Project Settings.


#include "CentralUnit.h"
#include "Components/InputComponent.h"
#include "RoomBase.h"
#include "Rotators.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACentralUnit::ACentralUnit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoReceiveInput = EAutoReceiveInput::Player0;

	CentralUnitComponent = CreateDefaultSubobject<USceneComponent>(TEXT("CentralUnitLocation"));
	CentralUnitComponent->SetRelativeLocation(FVector(0, 0, 0));

	// Member Values Setup
	Rotations = 0; // Controls which face to rotate via switch()
	RotatorRotationValue = 0; // Defines the rotation of a Rotator, value between 0 & 90

	//Bool Setup
	ClockWise = true;
	AddTransforms = true; // Used to only allow a set of 4 values in the Transform Array
}

// Called when the game starts or when spawned
void ACentralUnit::BeginPlay()
{
	Super::BeginPlay();
	SetupRotators();

	//-------------INPUT----------------------------------
	PlayerController = GetWorld()->GetFirstPlayerController();

	if (PlayerController)
	{
		EnableInput(PlayerController);
		InputComponent->BindAction("RotateF", IE_Pressed, this, &ACentralUnit::SetupFront);
		InputComponent->BindAction("RotateB", IE_Pressed, this, &ACentralUnit::SetupBack);
		InputComponent->BindAction("RotateL", IE_Pressed, this, &ACentralUnit::SetupLeft);
		InputComponent->BindAction("RotateR", IE_Pressed, this, &ACentralUnit::SetupRight);
		InputComponent->BindAction("RotateU", IE_Pressed, this, &ACentralUnit::SetupUp);
		InputComponent->BindAction("RotateD", IE_Pressed, this, &ACentralUnit::SetupDown);
	}
}

// Called every frame
void ACentralUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	switch (Rotations)
	{
	case 0:
		break;
	case 1:
		RotateRotator(RotatorF, RotatorRotationValue, DeltaTime);
		break;
	case 2:
		RotateRotator(RotatorB, RotatorRotationValue, DeltaTime);
		break;
	case 3:
		RotateRotator(RotatorL, RotatorRotationValue, DeltaTime);
		break;
	case 4:
		RotateRotator(RotatorR, RotatorRotationValue, DeltaTime);
		break;
	case 5:
		RotateRotator(RotatorU, RotatorRotationValue, DeltaTime);
		break;
	case 6:
		RotateRotator(RotatorD, RotatorRotationValue, DeltaTime);
		break;
	}

	CompletionCheck();
}

void ACentralUnit::ResetValues()
{
	RotatingRooms.Empty();
	TransformArray.Empty();
	Rotations = 0;
	RotatorRotationValue = 0;
	AddTransforms = true;
	for (auto& Rotators : RotatorArray)
		Rotators->SetActorRotation(FQuat(0, 0, 0, 0));
}


void ACentralUnit::SetupFront()
{
	ResetValues();
	Rotations = 1;

	for (int32 ActorIndex = 0; ActorIndex < TotalRooms.Num(); ActorIndex++)
	{
		if (TotalRooms[ActorIndex]->GetActorLocation().X > this->GetActorLocation().X)
			RotatingRooms.Add(TotalRooms[ActorIndex]);
	}

	for (auto& RoomsToRotate : RotatingRooms)
		RoomsToRotate->K2_AttachToActor(RotatorF, NAME_None, EAttachmentRule::KeepWorld, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, false);
}

void ACentralUnit::SetupBack()
{
	ResetValues();
	Rotations = 2;

	for (int32 ActorIndex = 0; ActorIndex < TotalRooms.Num(); ActorIndex++)
	{
		if (TotalRooms[ActorIndex]->GetActorLocation().X < this->GetActorLocation().X)
			RotatingRooms.Add(TotalRooms[ActorIndex]);
	}

	for (auto& RoomsToRotate : RotatingRooms)
		RoomsToRotate->K2_AttachToActor(RotatorB, NAME_None, EAttachmentRule::KeepWorld, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, false);
}

void ACentralUnit::SetupLeft()
{
	ResetValues();
	Rotations = 3;

	for (int32 ActorIndex = 0; ActorIndex < TotalRooms.Num(); ActorIndex++)
	{

		if (TotalRooms[ActorIndex]->GetActorLocation().Y < this->GetActorLocation().Y)
		{
			RotatingRooms.Add(TotalRooms[ActorIndex]);
		}
	}

	for (auto& RoomsToRotate : RotatingRooms)
	{
		RoomsToRotate->K2_AttachToActor(RotatorL, NAME_None, EAttachmentRule::KeepWorld, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, false);
	}
}

void ACentralUnit::SetupRight()
{
	ResetValues();
	Rotations = 4;

	for (int32 ActorIndex = 0; ActorIndex < TotalRooms.Num(); ActorIndex++)
	{
		if (TotalRooms[ActorIndex]->GetActorLocation().Y > this->GetActorLocation().Y)
		{
			RotatingRooms.Add(TotalRooms[ActorIndex]);
		}
	}

	for (auto& RoomsToRotate : RotatingRooms)
	{
		RoomsToRotate->K2_AttachToActor(RotatorR, NAME_None, EAttachmentRule::KeepWorld, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, false);
	}
}

void ACentralUnit::SetupUp()
{
	ResetValues();
	Rotations = 5;

	for (int32 ActorIndex = 0; ActorIndex < TotalRooms.Num(); ActorIndex++)
	{
		if (TotalRooms[ActorIndex]->GetActorLocation().Z > this->GetActorLocation().Z)
		{
			RotatingRooms.Add(TotalRooms[ActorIndex]);
		}
	}

	for (auto& RoomsToRotate : RotatingRooms)
	{
		RoomsToRotate->K2_AttachToActor(RotatorU, NAME_None, EAttachmentRule::KeepWorld, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, false);
	}

}

void ACentralUnit::SetupDown()
{
	ResetValues();
	Rotations = 6;

	for (int32 ActorIndex = 0; ActorIndex < TotalRooms.Num(); ActorIndex++)
	{
		if (TotalRooms[ActorIndex]->GetActorLocation().Z < this->GetActorLocation().Z)
		{
			RotatingRooms.Add(TotalRooms[ActorIndex]);
		}
	}

	for (auto& RoomsToRotate : RotatingRooms)
	{
		RoomsToRotate->K2_AttachToActor(RotatorD, NAME_None, EAttachmentRule::KeepWorld, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, false);
	}

}

void ACentralUnit::RotateRotator(ARotators* pRotator, float pRotation, float pDeltaTime)
{
	bool Completed = false;
	float Rotation = pRotation;
	FRotator RotatorAxisRotation;

	if (ClockWise)
		Rotation += 10 * pDeltaTime;

	else if (!ClockWise && Rotation >= -90)
		Rotation -= 10 * pDeltaTime;

	if (Rotation >= 90.0f)
	{
		Rotation = 90.0f;
		Completed = true;
	}
	if (Rotation <= -90)
	{
		Rotation = -90.0f;
		Completed = true;
	}

	RotatorAxisRotation = pRotator->InputRotation(Rotation);
	pRotator->SetActorRotation(RotatorAxisRotation);

	if (Completed && AddTransforms)
	{
		for (auto& RotatingRoom : RotatingRooms)
			TransformArray.Add(RotatingRoom->GetActorTransform());
		for (auto& Rooms : TotalRooms)
			Rooms->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		for (int32 Index = 0; Index < RotatingRooms.Num(); Index++)
			RotatingRooms[Index]->SetActorTransform(TransformArray[Index]);

		AddTransforms = false;
	}

	RotatorRotationValue = Rotation;
}

void ACentralUnit::CompletionCheck()
{
	// all the rooms have been completed and the game is thus won.

	//SIDE NOTE: This win condition can be complexified by checking if the rooms are in the correct
	// position in accordance to the principle of a completed rubik's cube.
	TArray<ARoomBase*> Temp;

	for (auto Room : TotalRooms)
	{
		if (Room->GetIsComplete() == true)
			Temp.Add(Room);
	}

	if (Temp.Num() >= TotalRooms.Num())
	{
		UGameplayStatics::OpenLevel(this->GetWorld(), "Win");
	}	
}

void ACentralUnit::SetupRotators()
{
	UWorld* const World = GetWorld();

	FActorSpawnParameters SpawnParamsF;
	FActorSpawnParameters SpawnParamsB;
	FActorSpawnParameters SpawnParamsL;
	FActorSpawnParameters SpawnParamsR;
	FActorSpawnParameters SpawnParamsU;
	FActorSpawnParameters SpawnParamsD;

	SpawnParamsF.Name = "RotatorF";
	SpawnParamsB.Name = "RotatorB";
	SpawnParamsL.Name = "RotatorL";
	SpawnParamsR.Name = "RotatorR";
	SpawnParamsU.Name = "RotatorU";
	SpawnParamsD.Name = "RotatorD";

	RotatorF = World->SpawnActor<ARotators>(Rotator, SpawnParamsF);
	RotatorB = World->SpawnActor<ARotators>(Rotator, SpawnParamsB);
	RotatorL = World->SpawnActor<ARotators>(Rotator, SpawnParamsL);
	RotatorR = World->SpawnActor<ARotators>(Rotator, SpawnParamsR);
	RotatorU = World->SpawnActor<ARotators>(Rotator, SpawnParamsU);
	RotatorD = World->SpawnActor<ARotators>(Rotator, SpawnParamsD);

	RotatorF->RotateOnX = RotatorB->RotateOnX = true;
	RotatorL->RotateOnY = RotatorR->RotateOnY = true;
	RotatorU->RotateOnZ = RotatorD->RotateOnZ = true;

	RotatorArray.Add(RotatorF);
	RotatorArray.Add(RotatorB);
	RotatorArray.Add(RotatorL);
	RotatorArray.Add(RotatorR);
	RotatorArray.Add(RotatorU);
	RotatorArray.Add(RotatorD);
}

