// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"
#include "BattleTank.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	DriveTrack();
	ApplySidewaysForce();
	CurrentThrottle = 0;
}

void UTankTrack::ApplySidewaysForce()
{
	
	//UE_LOG(LogTemp, Warning, TEXT("Tank Tick Test"))
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity()); //Slippage Speed
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CorrectionAccel = -SlippageSpeed / DeltaTime * GetRightVector(); //Acceleration to Correct slippage
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = TankRoot->GetMass() * CorrectionAccel / 2; //Two Tracks
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}

void UTankTrack::DriveTrack()
{
	auto Name = GetName();
	//UE_LOG(LogTemp, Warning, TEXT("%s: throttle: %f"), *Name, CurrentThrottle)

	//to do CLAMP throttle value, so player can't cheat settings

	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}