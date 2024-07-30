#include "Action/HyAction_AI_DamagedBase.h"


void UHyAction_AI_DamagedBase::OnActionStarted_Implementation(const FString& contextString)
{
	Super::OnActionStarted_Implementation(contextString);
}

void UHyAction_AI_DamagedBase::OnActionTransition_Implementation(UHyActionBase* previousState)
{
	Super::OnActionTransition_Implementation(previousState);

}

void UHyAction_AI_DamagedBase::OnTick_Implementation(float DeltaTime)
{
	Super::OnTick_Implementation(DeltaTime);

}

void UHyAction_AI_DamagedBase::OnActionEnded_Implementation()
{
	Super::OnActionEnded_Implementation();
}
