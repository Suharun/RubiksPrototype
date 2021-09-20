// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAICharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AEnemyAICharacter::AEnemyAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	MovementSpeed = 3.5f;
	AIRange = 750.0f;
	MovementVector = FVector(0, 0, 0);
}

// Called when the game starts or when spawned
void AEnemyAICharacter::BeginPlay()
{
	Super::BeginPlay();
	PlayerRef = Cast<ALJMUFPS425Character>(GetWorld()->GetFirstPlayerController()->GetPawn());
	this->GetMesh()->SetEnableGravity(false);
}

// Called every frame
void AEnemyAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsActive)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "Active");		
		if (isInRange(PlayerRef, AIRange))
		{
			MoveToTarget(PlayerRef, MovementSpeed);
		}
		else if (!isInRange(PlayerRef, AIRange))
			MovementVector = FVector(0, 0, 0);


	}
	else if (!IsActive)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "unactive");
		
	}

	
}

// Called to bind functionality to input
void AEnemyAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool AEnemyAICharacter::isInRange(ALJMUFPS425Character* pPlayerRef, float pRange)
{
	FVector PlayerLocation = pPlayerRef->GetActorLocation();
	FVector MinRange = FVector(this->GetActorLocation().X - pRange, this->GetActorLocation().Y - pRange, this->GetActorLocation().Z - pRange);
	FVector MaxRange = FVector(this->GetActorLocation().X + pRange, this->GetActorLocation().Y + pRange, this->GetActorLocation().Z + pRange);

	if (PlayerLocation.X >= MinRange.X && PlayerLocation.X <= MaxRange.X
		&& PlayerLocation.Y >= MinRange.Y && PlayerLocation.Y <= MaxRange.Y
		&& PlayerLocation.Z >= MinRange.Z && PlayerLocation.Z <= MaxRange.Z)
		return true;
	else
		return false;
}


void AEnemyAICharacter::MoveToTarget(ALJMUFPS425Character* pPlayerRef, float pMovementSpeed)
{
	/*MovementVector = this->GetActorLocation() - pPlayerTarget->GetActorLocation();
	MovementVector.Normalize();
	MovementVector.Z = 0;*/

	//this->SetActorLocation(this->GetActorLocation() - (Distance * pMovementSpeed));
	//MoveForward(MovementVector.X);
	//MoveRight(MovementVector.Y);

	//The Player is constantly rotated to look at the player so he only needs to move "Forwards"

	MoveRight(1);

	// Set the Rotation
	FVector RotationTargetLocation = pPlayerRef->GetActorLocation();
	RotationTargetLocation.Z = 0;

	FVector thisRotLocation = this->GetActorLocation();
	thisRotLocation.Z = 0;

	FRotator newRot = UKismetMathLibrary::FindLookAtRotation(thisRotLocation, RotationTargetLocation);

	newRot.Yaw = newRot.Yaw - 90;

	this->SetActorRotation(newRot);
}

void AEnemyAICharacter::MoveForward(float Val)
{
	if (Val != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Val);
	}
}

void AEnemyAICharacter::MoveRight(float Val)
{
	if (Val != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Val);
	}
}

bool AEnemyAICharacter::isSameRotation(AActor* pPlayerTarget)
{
	if (this->GetActorRotation().Pitch + 5 >= pPlayerTarget->GetActorRotation().Pitch && this->GetActorRotation().Pitch - 5 <= pPlayerTarget->GetActorRotation().Pitch 
		&& this->GetActorRotation().Roll + 5 >= pPlayerTarget->GetActorRotation().Roll && this->GetActorRotation().Roll - 5 <= pPlayerTarget->GetActorRotation().Roll)
		return true;
	else
		return false;
}


