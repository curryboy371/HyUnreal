// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HyFXComponent.h"
#include "FX/HyFXDispatcher.h"
#include "Game/HyGameInstance.h"


#include "GameFramework/Character.h"
#include "Components/AudioComponent.h"
#include "NiagaraComponent.h"

//#include "UI/NPDamageFontWidget.h"
#include "FX/HyDamageFontActor.h"
#include "Character/HyCharacter.h"
#include "Components/CapsuleComponent.h"



// Sets default values for this component's properties
UHyFXComponent::UHyFXComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


	// DamageFont BP Class Load
	//FString DamageFontWidgetPath = TEXT("/Game/UI/Widget/HUD/DamageFont/Damage_Font.Damage_Font_C");
	//DamageFontBPClass = StaticLoadClass(UUserWidget::StaticClass(), nullptr, *DamageFontWidgetPath);
	//if (DamageFontBPClass == nullptr)
	//{
	//	ERR_V("DamageFontWidget is invalid %s", *DamageFontWidgetPath);
	//}
}


// Called when the game starts
void UHyFXComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	CharacterOwner = Cast<AHyCharacter>(GetOwner());
}


// Called every frame
void UHyFXComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHyFXComponent::PlayAttachedFX(const FHyActionEffect& effect, ACharacter* instigator)
{
	UHyGameInstance* HyGameInstance = Cast<UHyGameInstance>(GWorld->GetGameInstance());
	if (HyGameInstance)
	{
		if (TObjectPtr<UHyFXDispatcher> FXDispatcher = HyGameInstance->GetFXDispatcher())
		{
			FAttachedComponents attComp = FXDispatcher->SpawnFXAttached(effect, instigator);

			ActiveFXMap.Add(effect.GetGuid(), attComp);

		}
	}


}

void UHyFXComponent::StopFXAttached(const FHyActionEffect& effect, ACharacter* instigator)
{
	if (ActiveFXMap.Contains(effect.GetGuid()))
	{
		FAttachedComponents attComp = ActiveFXMap.FindChecked(effect.GetGuid());
		if (attComp.AudioComp)
		{
			attComp.AudioComp->Deactivate();
			attComp.AudioComp = nullptr;
		}

		if (attComp.NiagaraComp)
		{
			attComp.NiagaraComp->Deactivate();
			attComp.NiagaraComp = nullptr;
		}


		if (attComp.CascadeComp)
		{
			attComp.CascadeComp->Deactivate();
			attComp.CascadeComp = nullptr;
		}

		ActiveFXMap.Remove(effect.GetGuid());
	}
	else
	{
		WAR_V("invalid fx");
	}
}

void UHyFXComponent::SpawnDamageText(const int32 InDamage, EDamageType InDamageType/* = EDamageType::EDamage_Normal*/)
{
	if (CharacterOwner && CharacterOwner->GetCapsuleComponent())
	{
		AHyDamageFontActor* DamageFont = GetWorld()->SpawnActor<AHyDamageFontActor>(AHyDamageFontActor::StaticClass(), CharacterOwner->GetTransform());
		if (DamageFont)
		{
			float CapsuleHeight = CharacterOwner->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
			FVector NewLocation = CharacterOwner->GetActorLocation() + FVector(0.0f, 0.0f, CapsuleHeight);
			DamageFont->SetActorLocation(NewLocation);
			DamageFont->SetDamage(InDamage, InDamageType);
		}
	}
	else
	{
		ERR_V("CharacterOwner is invaild");
	}

	// 2d 위젯 직접 viewport에 출력하는 방식
	// 투영 과정에서 좌표가 너무 틀어져서 widgetcomponent screen에 출력하는 방식으로 변경하였음
	//UNPDamageFontWidget* DamageFont = CreateWidget<UNPDamageFontWidget>(GetWorld(), DamageFontBPClass);
	//if (DamageFont)
	//{
	//	// Location 3D > 2D 
	//	FVector2D ScreenPosition;
	//
	//	if (UGameplayStatics::ProjectWorldToScreen(GetWorld()->GetFirstPlayerController(), InWorldLocation, ScreenPosition, true))
	//	{
	//		DamageFont->SetPositionInViewport(ScreenPosition);
	//
	//		DamageFont->SetDamageFont(InDamage, InDamageType);
	//		DamageFont->AddToViewport();
	//	}
	//}
}
