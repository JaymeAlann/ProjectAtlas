// Fill out your copyright notice in the Description page of Project Settings.


#include "RotatingFanBlades.h"
#include "Components/SceneComponent.h"
#include "Kismet/KismetMathLibrary.h"



// Sets default values
ARotatingFanBlades::ARotatingFanBlades()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Blades = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BLADES"));
	Blades->SetupAttachment(RootComponent);

}

void ARotatingFanBlades::setRotateSpeed(float RotationSpeed)
{
	RotateSpeed = RotationSpeed;
}

// Called when the game starts or when spawned
void ARotatingFanBlades::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARotatingFanBlades::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation(FRotator(0, 0, RotateSpeed), false, 0, ETeleportType::None);
	
}

