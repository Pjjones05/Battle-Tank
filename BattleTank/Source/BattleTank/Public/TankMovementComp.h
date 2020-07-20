// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComp.generated.h"

/**
 * Responsible for driving the tank track
 */
class UTankTrack;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComp : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	//Sets Forward and Backward Movement
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendMoveForward(float Throw);
	
	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendTurnRight(float Throw);

	//Check best protection

private:

	/** path following: request new velocity */
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;

	
};
