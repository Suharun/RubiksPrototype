// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LJMUFPS425Character.h"
#include "Components/BoxComponent.h"
#include "ObjectinteractInterface.h"
#include "InteractableObject.generated.h"

UCLASS()
class LJMUFPS425_API AInteractableObject : public AActor, public IObjectinteractInterface
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		class UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleDefaultsOnly, Category = Collision)
		class UBoxComponent* PuT;
public:	
	// Sets default values for this actor's properties
	AInteractableObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	//Interface functions
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
		void AttachToPlayer();
	virtual void AttachToPlayer_Implementation();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
		void DetachFromPlayer();
	virtual void DetachFromPlayer_Implementation();

	float GetValue() { return this->Value; };

	UStaticMeshComponent* GetMesh() { return this->Mesh; };

	UBoxComponent* GetBox() { return this->PuT; }

	bool GetPUState() { return this->PickUp; };
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Trigger)
		bool IsTrigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Trigger)
		bool IsHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Trigger)
		bool IsAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Trigger)
		bool IsReceiver;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Trigger)
		bool IsPickUp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Trigger)
		bool IsTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Trigger)
		float Value;

	

private:
	bool PickUp;

	ALJMUFPS425Character* PlayerRef;
};
