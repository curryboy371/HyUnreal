// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "HyGameplayTags.h"
#include "Character/HyCombatTypes.h"
#include "HyAttackCollisionComponent.generated.h"





UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HY_API UHyAttackCollisionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHyAttackCollisionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void OnComponentCreated();
	//void InitializeColliders();

	//UFUNCTION(BlueprintCallable, Category = "NP")
	//void AddAttackCollider(const BlueprintType& InAttackColliderSetup);

	void CreateAttackColliders();

	// 공격 충돌 활성화 및 비활성화 함수
	void EnableAttackCollision() {};
	void DisableAttackCollision() {};
	
public:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NP | Collider")
	//TArray<FNPAttackColliderInfo> AttackColliderInfos;
	//
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NP | Collider")
	//TMap<FGameplayTag, TObjectPtr<UShapeComponent>> AttackColliderComponentInstMap;

private:
	// 공격받은 몬스터 리스트
	TArray<AActor*> HitTargets;
};
