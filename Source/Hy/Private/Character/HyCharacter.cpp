// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/HyCharacter.h"

// Sets default values
AHyCharacter::AHyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

