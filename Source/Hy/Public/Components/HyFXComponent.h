// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FX/HyFXTypes.h"
#include "Character/HyCombatTypes.h"

#include "HyTypes.h"

#include "HyFXComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HY_API UHyFXComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHyFXComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = HY)
	void PlayAttachedFX(const FHyActionEffect& effect, class ACharacter* instigator);

	UFUNCTION(BlueprintCallable, Category = HY)
	void StopFXAttached(const FHyActionEffect& effect, class ACharacter* instigator);

	UFUNCTION(BlueprintCallable, Category = HY)
	void SpawnDamageText(const int32 InDamage, EDamageType InDamageType = EDamageType::EDamage_Normal);

protected:
	UPROPERTY(BlueprintReadOnly, Category = EffectCom)
	TObjectPtr<class ACharacter> CharacterOwner;
	

private:
	TMap<FGuid, FAttachedComponents> ActiveFXMap;

};
