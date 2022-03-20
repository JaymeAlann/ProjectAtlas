// Fill out your copyright notice in the Description page of Project Settings.


#include "Atlas_Elevator_Intro_Actor_BP.h"

// Sets default values
AAtlas_Elevator_Intro_Actor_BP::AAtlas_Elevator_Intro_Actor_BP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAtlas_Elevator_Intro_Actor_BP::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	
}

// Called every frame
void AAtlas_Elevator_Intro_Actor_BP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

