// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableObject.h"
#include "LJMUFPS425Character.h"

// Sets default values
AInteractableObject::AInteractableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetRelativeLocation(FVector(0, 0, 0));


	PuT = CreateDefaultSubobject<UBoxComponent>(TEXT("PickUpTrigger"));
	PuT->SetupAttachment(Mesh);
	PuT->SetRelativeLocation(FVector(0, 0, 0));

	FVector Scale = Mesh->GetComponentScale();
	FVector NewScale = Scale * 3.5;
	PuT->SetRelativeScale3D(NewScale);

	PickUp = false;
}

// Called when the game starts or when spawned
void AInteractableObject::BeginPlay()
{
	Super::BeginPlay();

	Mesh->SetSimulatePhysics(true);
	APlayerController* Controller = GetWorld()->GetFirstPlayerController();
	PlayerRef = Cast<ALJMUFPS425Character>(Controller->GetPawn());
	
	if (Controller)
	{
		EnableInput(Controller);
		InputComponent->BindAction("PickUp", IE_Pressed, this, &AInteractableObject::AttachToPlayer_Implementation);
		InputComponent->BindAction("PickUp", IE_Released, this, &AInteractableObject::DetachFromPlayer_Implementation);

		InputComponent->GetActionBinding(0).bConsumeInput = false;
		InputComponent->GetActionBinding(1).bConsumeInput = false;
	}
}

// Called every frame
void AInteractableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractableObject::AttachToPlayer_Implementation()
{
	PickUp = true;
	FQuat NewRot(0, 0, 0, 0);
	//Print out the player location
	if (this->IsOverlappingActor(PlayerRef))
	{
		if (IsHealth)
		{
			this->Destroy();
			PlayerRef->SetHealth(this->GetValue());
		}
		if (IsAmmo)
		{
			this->Destroy();
			PlayerRef->AddAmmo(this->GetValue());
		}
		if (IsTrigger || IsPickUp)
		{

			// Detach from anything its attached to (in this case the Room)
			this->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
			// Disable Physics so the object doesnt fall through the ground when carried
			this->GetMesh()->SetSimulatePhysics(false);
			// Attach to the player
			this->K2_AttachToActor(PlayerRef, NAME_None, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, false);
			this->SetActorRelativeLocation(FVector(180, 0, 10));
			this->SetActorRotation(NewRot);

			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "Pick");
		}
	}
	

}

void AInteractableObject::DetachFromPlayer_Implementation()
{
	if (this->IsAttachedTo(PlayerRef))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "Drop");
		this->GetMesh()->SetSimulatePhysics(true);
		this->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		this->SetActorScale3D(FVector(1, 1, 1));
		PickUp = false;
	}
}