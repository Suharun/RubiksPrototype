// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomBase.h"

// Sets default values
ARoomBase::ARoomBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OriginPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Origin"));
	OriginPoint->SetRelativeLocation(FVector(0, 0, 0));

	Light = CreateDefaultSubobject<UPointLightComponent>(TEXT("Light"));
	Light->SetupAttachment(OriginPoint);
	Light->SetRelativeLocation(FVector(0, 0, 0));
	Light->SetLightColor(FLinearColor::Red);
	Light->SetAttenuationRadius(2000.0f);
	Light->SetIntensity(50000.0f);


	SideA = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SideA"));
	SideA->SetupAttachment(OriginPoint);
	SideA->SetRelativeLocation(FVector(0, 0, 0));
	SideB = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SideB"));
	SideB->SetupAttachment(OriginPoint);
	SideB->SetRelativeLocation(FVector(0, 0, 0));
	SideC = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SideC"));
	SideC->SetupAttachment(OriginPoint);
	SideC->SetRelativeLocation(FVector(0, 0, 0));
	SideD = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SideD"));
	SideD->SetupAttachment(OriginPoint);
	SideD->SetRelativeLocation(FVector(0, 0, 0));
	SideE = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SideE"));
	SideE->SetupAttachment(OriginPoint);
	SideE->SetRelativeLocation(FVector(0, 0, 0));
	SideF = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SideF"));
	SideF->SetupAttachment(OriginPoint);
	SideF->SetRelativeLocation(FVector(0, 0, 0));
	IsComplete = false;
}

// Called when the game starts or when spawned
void ARoomBase::BeginPlay()
{
	Super::BeginPlay();
	if (!IsPuzzle && !IsEnemy && !IsLoot && !IsTarget)
	{
		IsComplete = true;
	}

	
	for (auto tObject : LootObjects)
	{
		if (tObject != NULL)
			tObject->K2_AttachToActor(this, NAME_None, EAttachmentRule::KeepWorld, EAttachmentRule::KeepRelative, EAttachmentRule::KeepWorld, true); 
	}

	for (auto tObject : Enemies)
	{
		if (tObject != NULL)
			tObject->K2_AttachToActor(this, NAME_None, EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, false);
	}

	if (ReceiverObject != NULL)
		ReceiverObject->K2_AttachToActor(this, NAME_None, EAttachmentRule::KeepWorld, EAttachmentRule::KeepRelative, EAttachmentRule::KeepWorld, true);

	for (auto tObject : TargetObjects)
	{
		if(tObject != NULL)
			tObject->K2_AttachToActor(this, NAME_None, EAttachmentRule::KeepWorld, EAttachmentRule::KeepRelative, EAttachmentRule::KeepWorld, true);
	}
}

// Called every frame
void ARoomBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Room Type Check
	if (IsPuzzle)
		Puzzle();
	if (IsEnemy)
		Enemy();
	if (IsLoot)
		Loot();
	if (IsTarget)
		Target();

	// Completion Check
	if (IsComplete)
		Complete();
}


void ARoomBase::Puzzle()
{
	if (ReceiverObject != NULL) {
		ReceiverObject->K2_AttachToActor(this, NAME_None, EAttachmentRule::KeepWorld, EAttachmentRule::KeepRelative, EAttachmentRule::KeepWorld, true);
	}
	for (auto tObject : InteractableObjects)
	{
		if (tObject != NULL)
			if (tObject->GetPUState() == false)
			{
				tObject->K2_AttachToActor(this, NAME_None, EAttachmentRule::KeepWorld, EAttachmentRule::KeepRelative, EAttachmentRule::KeepWorld, true);
			}
	}

	for (auto check : InteractableObjects)
	{
		if (ReceiverObject != NULL) {
			if (check->IsTrigger && check->GetMesh()->IsOverlappingActor(ReceiverObject))
			{
				IsComplete = true;
				check->GetMesh()->SetVisibility(false);
			}

			if (check->IsOverlappingActor(this))
			{
				check->GetMesh()->SetSimulatePhysics(false);
			}
		}
	}
}

void ARoomBase::Enemy()
{
	TArray<AEnemyAICharacter*> Temp;

	for (auto Enemy : Enemies)
	{
		Temp.Add(Enemy);
	}

	for (auto& check : Enemies)
	{
		if (check != NULL)
		{
			if (check->isSameRotation(this))
			{
				check->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
				check->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
				check->GetCapsuleComponent()->SetEnableGravity(true);
				check->IsActive = true;
			}
			else if (check->isSameRotation(this) == false)
			{
				check->K2_AttachToActor(this, NAME_None, EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, false);
				check->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
				check->GetCapsuleComponent()->SetEnableGravity(false);
				check->IsActive = false;
			}

			if (check->IsPendingKill())
			{
				Temp.Remove(check);
			}
		}
		else if (check == NULL)
			Temp.Remove(check);
	}

	if (Temp.Num() <= 0)
		IsComplete = true;

}

void ARoomBase::Loot()
{
	//Make a temporary array that holds the same values as the actual loot array so that we can remove items from temp and check if its empty,
	// If temp is empty then all loot items have been collected (solves the problem of getting a null pointer in the for loop)
	TArray<AInteractableObject*> Temp;
	for (auto Loot : LootObjects)
	{
		Temp.Add(Loot);
	}

	for (auto Loot : LootObjects)
	{
		if (Loot != NULL)
		{
			Loot->K2_AttachToActor(this, NAME_None, EAttachmentRule::KeepWorld, EAttachmentRule::KeepRelative, EAttachmentRule::KeepWorld, true);
			if (Loot->IsPendingKill()) // Is Pending Kill checks to see if the object is dead but the memory is still allocated.
				Temp.Remove(Loot);
		}
	}

	if (Temp.Num() <= 0)
		IsComplete = true;
}

void ARoomBase::Target()
{
	TArray<AInteractableObject*> Temp;

	for (auto Targets : TargetObjects)
	{
		Temp.Add(Targets);
	}

	for (auto& check : TargetObjects)
	{
		if (check != NULL)
		{
			if (check->IsPendingKill())
			{
				Temp.Remove(check);
			}
		}
		else if (check == NULL)
		{
			Temp.Remove(check);
		}
	}

	if (Temp.Num() <= 0)
		IsComplete = true;
}