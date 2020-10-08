// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"



//ENUM HERE FOR AIMING STATE
UENUM()
enum class EFiringState : uint8
{
	Locked,
	Aiming,
	Reload,

};


class UTankBarrel; //Forward Declartion
class UTurret;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties

	void AimAt(FVector OutHitLocation);
	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();
	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* BarrelToSet, UTurret* TurretToSet);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reload;

private:
	UTankAimingComponent();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	UTankBarrel* Barrel = nullptr;
	UTurret* Turret = nullptr;
	void MoveBarrelTowards(FVector AimDirection);

	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 40000;
	float ReloadTimeInSeconds = 3;
	double LastFireTime = 0;

};
