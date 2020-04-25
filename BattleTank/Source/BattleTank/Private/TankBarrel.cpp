// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void UTankBarrel::Elevate(float DegreesPerSecond)
{
	UE_LOG(LogTemp, Warning, TEXT("Barrel-Elevated() called at speed %f"), DegreesPerSecond);
}

void UTankBarrel::Elevation(float MinDegrees, float MaxDegrees)
{

}

