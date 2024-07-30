// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Character/HyCombatTypes.h"

#include "HyDamageFontActor.generated.h"

UCLASS()
class HY_API AHyDamageFontActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHyDamageFontActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetDamage(const int32 InDamage, EDamageType InDamageType = EDamageType::EDamage_Normal);
	void DestroyActor();

protected:
	UPROPERTY(EditAnywhere, Category = DamageFont)
	float LifeTime = 0.55f;

	TObjectPtr<class USceneComponent> RootCom;
	TObjectPtr<class UWidgetComponent> DamageFontWidgetCom;

	FTimerHandle LifespanTimerHandle;

};
