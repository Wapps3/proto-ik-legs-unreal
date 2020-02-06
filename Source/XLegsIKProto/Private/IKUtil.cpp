#include "IKUtil.h"

#include "DrawDebugHelpers.h"


FVector UIKUtil::TraceGround(UObject* Target, const FVector& From, float RaycastMaxDistance)
{
	UWorld* World = Target->GetWorld();
	if (World)
	{

		FVector Start = From + FVector(0, 0, RaycastMaxDistance);
		FVector End = From - FVector(0, 0, RaycastMaxDistance);

		FHitResult Hit;


		FCollisionQueryParams TraceParams;

		DrawDebugLine(Target->GetWorld(), Start, End, FColor::Red, false, 0.5f, 0, 2);

		if (World->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, TraceParams))
		{
			return Hit.Location;
			
		}
		else
		{
			return From;
		}
	}
	
	return From;
}

void UIKUtil::FootByGroupIK(UObject* Target, ACharacter* Character,const TArray<FName> &ListSocketName,float DistanceMaxGround, TArray<float> &IKLegs, float &HipDeplacement)
{
	float ZPositionOfActor;

	TArray<float> DistFromGround;
	
	ZPositionOfActor = Character->GetActorLocation().Z - Character->GetDefaultHalfHeight();
	
	
	int index = 0;
	for (FName NameSocket : ListSocketName)
	{
		FVector PosSocket =  Character->GetMesh()->GetSocketLocation(NameSocket);

		DistFromGround.Push(TraceGround(Target, PosSocket, 100.0f).Z);
		IKLegs.Push(0);

		index++;
	}
	
	float min = INFINITY;
	
	for (float Element : DistFromGround)
	{
		if (Element < min)
			min = Element;
	}

	HipDeplacement = min - ZPositionOfActor;
	HipDeplacement = abs(HipDeplacement);
	
	for(int i = 0; i < IKLegs.Num() ; i++)
	{
		IKLegs[i] = abs(DistFromGround[i] - ZPositionOfActor) / DistanceMaxGround;
	}

}

FRotator UIKUtil::BodyRotateIK(UObject* Target, ACharacter* Character, float DistanceFromCenterFront, float DistanceFromCenterBack)
{
	FVector ForwardVector = Character->GetActorForwardVector();

	FVector ActorLocation = Character->GetActorLocation();

	float ZPositionOfActor;

	ZPositionOfActor = Character->GetActorLocation().Z - Character->GetDefaultHalfHeight();

	
	float XFrontPoint = ForwardVector.X * DistanceFromCenterFront + ActorLocation.X;
	float YFrontPoint = ForwardVector.Y * DistanceFromCenterFront + ActorLocation.Y;
	float ZFrontPoint = ForwardVector.Z * DistanceFromCenterFront + ZPositionOfActor;

	FVector FrontPoint = FVector(XFrontPoint,YFrontPoint,ZFrontPoint);

	float XBackPoint = ForwardVector.X * DistanceFromCenterBack + ActorLocation.X;
	float YBackPoint = ForwardVector.Y * DistanceFromCenterBack + ActorLocation.Y;
	float ZBackPoint = ForwardVector.Z * DistanceFromCenterBack + ZPositionOfActor;

	FVector BackPoint = FVector(XBackPoint, YBackPoint, ZBackPoint);


	//DrawDebugLine(Target->GetWorld(), FrontPoint, BackPoint, FColor::Red, false, 0.5f, 0, 10);

	FVector AngleVector = TraceGround(Target, FrontPoint, 200.0f) - TraceGround(Target, BackPoint, 100.0f);

	return UKismetMathLibrary::FindLookAtRotation(AngleVector,ForwardVector);
}


float UIKUtil::BodyHipsIK(UObject* Target, ACharacter* Character, FRotator BodyRotate, float SizeOfLeg)
{
	float ZPositionOfActor;

	FVector ActorLocation = Character->GetActorLocation();
	
	ZPositionOfActor = Character->GetActorLocation().Z - Character->GetDefaultHalfHeight();

	FVector NearGround = TraceGround(Target, FVector(ActorLocation.X, ActorLocation.Y, ZPositionOfActor), 100.0f);

	float DistanceFromGround = abs(NearGround.Z - ZPositionOfActor);

	if(BodyRotate.Pitch < 1.0f)
	{
		return -DistanceFromGround;
	}
	else
	{
		return DistanceFromGround + SizeOfLeg;
	}
	
	
}
