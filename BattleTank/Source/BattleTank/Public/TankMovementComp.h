// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComp.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API UTankMovementComp : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	//Sets Forward and Backward Movement
	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendMoveForward(float Throw);
	
	
};
