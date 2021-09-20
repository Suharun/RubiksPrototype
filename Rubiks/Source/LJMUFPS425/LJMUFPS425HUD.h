// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 
#include "LJMUFPS425Character.h"
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "LJMUFPS425HUD.generated.h"

UCLASS()
class ALJMUFPS425HUD : public AHUD
{
	GENERATED_BODY()

public:
	ALJMUFPS425HUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void DrawCrosshair();

	void DrawHealth();

	void DrawAmmo();

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

	class UTexture2D* HealthTex;

	class UTexture2D* AmmoTex;

	class ALJMUFPS425Character* Player;

	int AmmoValue;

	int HealthValue;

};

