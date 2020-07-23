// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComp.h"
#include "TankTrack.h"
#include "Tank.h"


void UTankMovementComp::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	
	{
		LeftTrack = LeftTrackToSet;
		RightTrack = RightTrackToSet;
	}
}

void UTankMovementComp::IntendMoveForward(float Throw)

{
	if (!ensure(LeftTrack && RightTrack)) { return; }
	//UE_LOG(LogTemp, Warning, TEXT("Intend move forward throw: %f"), Throw);
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);

}

void UTankMovementComp::IntendTurnRight(float Throw)

{
	if (!ensure(LeftTrack && RightTrack)) { return; }
	//UE_LOG(LogTemp, Warning, TEXT("Intend move forward throw: %f"), Throw);
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
	
}

void UTankMovementComp::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	//No need to call Super, replacing funtionality 
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	auto ForwardThrow =	FVector::DotProduct(TankForward, AIForwardIntention);
	IntendMoveForward(ForwardThrow);

	auto RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	IntendTurnRight(RightThrow);

	//UE_LOG(LogTemp,Warning,TEXT("%s vectoring to %s"), *TankName, *MoveVelocityString)

}

