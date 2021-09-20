// Copyright Epic Games, Inc. All Rights Reserved.

#include "LJMUFPS425HUD.h"
#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
#include "TextureResource.h"
#include "CanvasItem.h"
#include "UObject/ConstructorHelpers.h"

ALJMUFPS425HUD::ALJMUFPS425HUD()
{
	// Set the crosshair texture
	static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshairTexObj(TEXT("/Game/FirstPerson/Textures/FirstPersonCrosshair"));
	CrosshairTex = CrosshairTexObj.Object;

	static ConstructorHelpers::FObjectFinder<UTexture2D> HealthTexObj(TEXT("/Game/Rubiks/Textures/Health_Icon"));
	HealthTex = HealthTexObj.Object;
	
	static ConstructorHelpers::FObjectFinder<UTexture2D> AmmoTexObj(TEXT("/Game/Rubiks/Textures/Ammo_Icon"));
	AmmoTex = AmmoTexObj.Object;

	AmmoValue = 0;
	HealthValue = 0;
}


void ALJMUFPS425HUD::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<ALJMUFPS425Character>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void ALJMUFPS425HUD::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AmmoValue = Player->GetAmmo();

	HealthValue = Player->GetHealth();
}

void ALJMUFPS425HUD::DrawHUD()
{
	Super::DrawHUD();

	DrawCrosshair();

	//DrawHealth();

	//DrawAmmo();
	
}

void ALJMUFPS425HUD::DrawCrosshair()
{
	// Draw very simple crosshair

	// find center of the Canvas
	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

	// offset by half the texture's dimensions so that the center of the texture aligns with the center of the Canvas
	const FVector2D CrosshairDrawPosition((Center.X),
		(Center.Y + 20.0f));

	// draw the crosshair
	FCanvasTileItem TileItem(CrosshairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(TileItem);
}

void ALJMUFPS425HUD::DrawHealth()
{
	//Draw Health

	// Find Bottom Left of Canvas
	const FVector2D BLeft(Canvas->ClipX * 0, Canvas->ClipY *0.75f);

	// Add Offset
	const FVector2D HealthDrawPosition((BLeft.X + 25), (BLeft.Y));

	const FVector2D HealthDrawSize(75, 75);

	// Draw the Healh Icon
	FCanvasTileItem TileItem(HealthDrawPosition, HealthTex->Resource, HealthDrawSize, FLinearColor::Red);
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(TileItem);

	const FVector2D TextBRight(Canvas->ClipX * 0, Canvas->ClipY * 0.75);

	const FVector2D HealthValueDrawPosition((TextBRight.X), (TextBRight.Y));
	DrawText(FString::FromInt(HealthValue), FLinearColor::Red, HealthValueDrawPosition.X, HealthValueDrawPosition.Y, GEngine->GetLargeFont(), 4);
}

void ALJMUFPS425HUD::DrawAmmo()
{
	//Draw Ammo

	// Find Bottom Right of Canvas
	const FVector2D BRight(Canvas->ClipX * 0.75, Canvas->ClipY * 0.5);

	//Add Offset
	const FVector2D AmmoDrawPosition((BRight.X + 200), (BRight.Y + 175));
	
	const FVector2D AmmoDrawSize(75, 75);
	
	// Draw the Ammo Icon
	FCanvasTileItem TileItem(AmmoDrawPosition, AmmoTex->Resource, AmmoDrawSize,FLinearColor::White);
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(TileItem);


	FVector2D TextBRight(Canvas->ClipX * 0.75, Canvas->ClipY * 0.5);

	FVector2D AmmoValueDrawPosition((TextBRight.X + 125), (TextBRight.Y + 180));
	DrawText(FString::FromInt(AmmoValue), FLinearColor::White, AmmoValueDrawPosition.X, AmmoValueDrawPosition.Y, GEngine->GetLargeFont(), 4);
}


