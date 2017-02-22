// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankAI.h"
#include "Tank.h"


void ATankAI::BeginPlay()
{
	Super::BeginPlay();

	// Check if AIController is possessing a tank and log it
	auto ControlledTank = GetAIControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController not posessing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController possessing %s"), *(ControlledTank->GetName()));
	}

	// Check if AIController find a PlayerTank tank and log it
	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController didn't foud the PlayerTank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController found PlayerTank: %s"), *(PlayerTank->GetName()));
	}
}

// Called every frame
void ATankAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetPlayerTank())
	{
		// TODO Move towards the player

		// Aim towards the player
		GetAIControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());

		// Fire if ready
	}
}

ATank* ATankAI::GetAIControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAI::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn){return nullptr;}

	return Cast<ATank>(PlayerPawn);
}