#include "Action/HyAction_Evade.h"

#include "Character/HyCharacter.h"

void UHyAction_Evade::OnActionStarted_Implementation(const FString& contextString)
{
	Super::OnActionStarted_Implementation(contextString);

	if (CharacterOwner)
	{
		//CharacterOwner->SetEvading(true);

		// dash direction 설정
		//CharacterOwner->SwichMovementMode(EMoveMode::EEvade);
	}
}

void UHyAction_Evade::OnTick_Implementation(float DeltaTime)
{
	Super::OnTick_Implementation(DeltaTime);
	//float DashDistance = CharacterOwner->GetDashDistance();
	//
	//FVector CurrentLocation = CharacterOwner->GetActorLocation();



	// 시작 위치로부터 현재 위치까지의 벡터
	//FVector ToCurrent = CurrentLocation - StartLocation;
	//
	//// Dot Product를 사용하여 위치가 목적지를 지나쳤는지 확인
	//if (FVector::DotProduct(DashDirection, ToCurrent) > 0)
	//{
	//	float DistanceToDestination = FVector::Dist(DestLocation, StartLocation);
	//	float DistanceToCurrent = FVector::Dist(CurrentLocation, StartLocation);
	//
	//	if (DistanceToCurrent > DistanceToDestination)
	//	{
	//		bIsAtDestination = true;
	//		return;
	//	}
	//}

}

void UHyAction_Evade::OnActionEnded_Implementation()
{
	Super::OnActionEnded_Implementation();
	if (CharacterOwner)
	{
		//CharacterOwner->SetEvading(false);
	}
}
