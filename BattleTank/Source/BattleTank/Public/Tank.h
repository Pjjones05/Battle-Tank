// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"


class UTankBarrel;
class UTurret;
class UTankAimingComponent;
class AProjectile;

//Hold Barrel's Properties and Elevate Methods
UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTurret* TurretToSet);

	void AimAt(FVector OutHitLocation);

	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();

	
protected:
	UTankAimingComponent* TankAimingComponent = nullptr;

private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 4000; // CHANGE TO REAL VALUE

	UPROPERTY(EditDefaultsOnly, Category = Firing) //Could Crash Game in 4.18
	float ReloadTimeInSeconds = 3;

	

	UTankBarrel* Barrel = nullptr;
	
	double LastFireTime = 0;
};
