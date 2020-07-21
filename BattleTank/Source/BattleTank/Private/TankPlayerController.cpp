// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"
#include "BattleTank.h"




void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	//UE_LOG(LogTemp, Warning, TEXT("DONKEY: TankPlayerController.CPP"));
	if (!ControlledTank)
	{
		//UE_LOG(LogTemp, Warning, TEXT("PlayerController Not Possesing a tank!"));
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing: %s"), *(ControlledTank->GetName()));
	}
	
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

		FVector OutHitLocation; //out paramter
		if (GetSightRayHitLocation(OutHitLocation))
		{
			GetControlledTank()->AimAt(OutHitLocation);
		}
	//Get World location of linetrace through crosshair
	//If Hit the landscape
		//Tell Controlled tank to aim barrel

}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const //Get World location of linetrace through crosshair, ture if hits landscape
{
	//Find Crosshair Position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	//UE_LOG(LogTemp, Warning, TEXT("Screen Location: %s"), *ScreenLocation.ToString());
	

	//"De-project" Screen Position of Crosshair to world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		//Line trace along lookdirection, and see what is hit (to max range)
		
		GetLookVectorHitLocation(LookDirection, OutHitLocation);
	
	}

	
	return true;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if(GetWorld()-> LineTraceSingleByChannel(HitResult,StartLocation,EndLocation,ECollisionChannel::ECC_Visibility))
	{
			OutHitLocation = HitResult.Location;
			return true;
	}
	OutHitLocation = FVector(0);
	return false; //Line trace didn't succeed
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection);
	
}