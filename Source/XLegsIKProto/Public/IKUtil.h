// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Kismet/KismetMathLibrary.h"
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Components/SceneComponent.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "IKUtil.generated.h"

/**
 * 
 */
UCLASS()
class XLEGSIKPROTO_API UIKUtil : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "IKUtil")
	static FVector TraceGround(UObject* Target, const FVector& From, float RaycastMaxDistance);

	UFUNCTION(BlueprintCallable, Category = "IKUtil")
	static FRotator BodyRotateIK(UObject* Target, ACharacter* Character, float DistanceFromCenterFront, float DistanceFromCenterBack);

	UFUNCTION(BlueprintCallable, Category = "IKUtil")
	static float BodyHipsIK(UObject* Target, ACharacter* Character, FRotator BodyRotate, float SizeOfLeg);

	UFUNCTION(BlueprintCallable, Category = "IKUtil")
	static void FootByGroupIK(UObject* Target, ACharacter* Actor, const TArray<FName> &ListSocketName, float DistanceMaxGround, TArray<float> &IKLegs, float &HipDeplacement);


	
};
