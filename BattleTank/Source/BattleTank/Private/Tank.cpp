// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankAimingComponent.h"
#include "TankMovementComp.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();//NEEDED FOR BP BEGIN PLAY
	//UE_LOG(LogTemp, Warning, TEXT("DONKEY: Tank.cpp"));
}

// Called to bind functionality to input

void ATank::AimAt(FVector OutHitLocation)
{
	if (!TankAimingComponent) { return; }
	TankAimingComponent->AimAt(OutHitLocation, LaunchSpeed);
}

void ATank::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (Barrel && isReloaded) 
	{
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		if (!Projectile) 
		{
			//UE_LOG(LogTemp, Error, TEXT("Reset Projectile in Tank Blueprint parameters."))
			return; }
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}