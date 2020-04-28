// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	// -1 is max downward movement and +1 is max up speed
	void Elevate(float RelativeSpeed);
	
	
	
private:
	UPROPERTY(EditAnywhere)
	float MaxDegreesPerScond = 5; //change to sensible value 
	UPROPERTY(EditAnywhere)
	float MaxDegrees = 45;
	UPROPERTY(EditAnywhere)
	float MinDegrees = 0;

};
