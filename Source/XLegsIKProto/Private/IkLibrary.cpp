// Fill out your copyright notice in the Description page of Project Settings.


#include "IkLibrary.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"

/*
void TraceGround(FVector From, float LengthRayCast, FVector &HitLocation, float &Distance)
{
	FVector Start = From - FVector(0, 0, LengthRayCast);
	FVector End = From + FVector(0, 0, LengthRayCast);

	FHitResult Hit;
	
	FCollisionQueryParams TraceParams;

	UWorld w;
	
	
	w.UWorld::GetWorld()->UWorld::LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, TraceParams);

	HitLocation = Hit.Location;
	
	DrawDebugLine(w.UWorld::GetWorld(),Start, End, FColor::Red, false, 2.0f);

}
*/