// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HyAttackCollisionComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"

#include "HyGameplayTags.h"


// Sets default values for this component's properties
UHyAttackCollisionComponent::UHyAttackCollisionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHyAttackCollisionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

#if WITH_EDITOR
void UHyAttackCollisionComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	// 에디터 생성용
	// 모든 AttackColliderInfos 내부 변수 변경 시 CreateAttackColliders 호출
	//CreateAttackColliders();

}
#endif

// Called every frame
void UHyAttackCollisionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHyAttackCollisionComponent::OnComponentCreated()
{
	Super::OnComponentCreated();

}

void UHyAttackCollisionComponent::CreateAttackColliders()
{
	//for (auto& Elem : AttackColliderComponentInstMap)
	//{
	//	if (Elem.Value)
	//	{
	//		Elem.Value->DestroyComponent();
	//	}
	//}
	//AttackColliderComponentInstMap.Empty();

	//for (FNPAttackColliderInfo& ColliderInfo : AttackColliderInfos)
	//{
	//	// 여기서 생성??
	//	//ColliderInfo.ColliderClass
	//	if (AActor* Owner = GetOwner())
	//	{
	//		if (USkeletalMeshComponent* MeshComp = Owner->FindComponentByClass<USkeletalMeshComponent>())
	//		{
	//			UShapeComponent* Collider = nullptr;
	//
	//			if (ColliderInfo.ColliderClass)
	//			{
	//				FName ColliderComName = FHyTags::Get().ConvertGameplayTagToName(ColliderInfo.ColliderTag);
	//				Collider = NewObject<UShapeComponent>(Owner, ColliderInfo.ColliderClass, ColliderComName);
	//			}
	//
	//			if (Collider)
	//			{
	//				if (MeshComp->DoesSocketExist(ColliderInfo.BoneName))
	//				{
	//					Collider->SetupAttachment(MeshComp, ColliderInfo.BoneName);  // SetupAttachment 사용
	//					Collider->SetRelativeLocation(ColliderInfo.ColliderLocation);
	//					Collider->SetRelativeRotation(ColliderInfo.ColliderRotation);
	//
	//					if (UBoxComponent* BoxCollider = Cast<UBoxComponent>(Collider))
	//					{
	//						BoxCollider->SetBoxExtent(ColliderInfo.ColliderSize);
	//					}
	//					else if (USphereComponent* SphereCollider = Cast<USphereComponent>(Collider))
	//					{
	//						SphereCollider->SetSphereRadius(ColliderInfo.ColliderSize.X);
	//					}
	//					else if (UCapsuleComponent* CapsuleCollider = Cast<UCapsuleComponent>(Collider))
	//					{
	//						CapsuleCollider->SetCapsuleSize(ColliderInfo.ColliderSize.X, ColliderInfo.ColliderSize.Z);
	//					}
	//
	//					Collider->SetHiddenInGame(false);
	//					Collider->SetVisibility(true);
	//					ColliderInfo.ColliderComponent = Collider;
	//
	//					AttackColliderComponentInstMap.Add(ColliderInfo.ColliderTag, Collider);
	//				}
	//			}
	//
	//		}
	//
	//
	//	}
	//}
}

