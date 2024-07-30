// Fill out your copyright notice in the Description page of Project Settings.


#include "FX/HyDamageFontActor.h"

#include "Components/WidgetComponent.h"
//#include "UI/NPDamageFontWidget.h"
#include "TimerManager.h"

// Sets default values
AHyDamageFontActor::AHyDamageFontActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootCom = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	SetRootComponent(RootCom);
	DamageFontWidgetCom = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetCom"));

	// DamageFont BP Class Load
	//FString DamageFontWidgetPath = TEXT("/Game/UI/Widget/HUD/DamageFont/HUD_Damage_Font.HUD_Damage_Font_C");
	//UClass* DamageFontBPClass = StaticLoadClass(UUserWidget::StaticClass(), nullptr, *DamageFontWidgetPath);
	//if (DamageFontBPClass == nullptr)
	//{
	//	ERR_V("DamageFontWidget is invalid %s", *DamageFontWidgetPath);
	//}
	//else
	//{
	//	if (DamageFontWidgetCom)
	//	{
	//		DamageFontWidgetCom->SetupAttachment(RootCom);
	//		DamageFontWidgetCom->SetWidgetClass(DamageFontBPClass);
	//		DamageFontWidgetCom->SetWidgetSpace(EWidgetSpace::Screen);
	//	}
	//}


}

// Called when the game starts or when spawned
void AHyDamageFontActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHyDamageFontActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHyDamageFontActor::SetDamage(const int32 InDamage, EDamageType InDamageType)
{
	//if (DamageFontWidgetCom)
	//{
	//	if (DamageFontWidgetCom->GetWidget())
	//	{
	//		if (UNPDamageFontWidget* DamageFontWidget = Cast<UNPDamageFontWidget>(DamageFontWidgetCom->GetWidget()))
	//		{
	//			DamageFontWidget->SetDamageFont(InDamage, InDamageType);
	//		}
	//		else
	//		{
	//			ERR_V("Casting DamageFontWidget is invalid");
	//		}
	//	}
	//	else
	//	{
	//		ERR_V("DamageFontWidgetCom Widget is null");
	//	}
	//}
	//
	//GetWorldTimerManager().SetTimer(LifespanTimerHandle, this, &AHyDamageFontActor::DestroyActor, LifeTime, false);
}

void AHyDamageFontActor::DestroyActor()
{
	// TODO Pool방식으로 변경할거면 수정
	Destroy();
}

