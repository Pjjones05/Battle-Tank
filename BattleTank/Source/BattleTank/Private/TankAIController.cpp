// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "BattleTank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto PlayerTank = GetPlayerTank();

	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI cannot find PlayerTank!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Targetting: %s"), *(PlayerTank->GetName()));
	}

	if (GetPlayerTank())
	{
		//Move Towards the player
		//Aim at Player
		GetAIControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
		//Fire if ready
	}
}
ATank* ATankAIController::GetAIControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!PlayerTank) { return nullptr; }
	return Cast<ATank>(PlayerTank);


}