// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Atlas_Elevator_Intro_Actor_BP.generated.h"

UCLASS()
class SIDESCROLLTEMP_API AAtlas_Elevator_Intro_Actor_BP : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAtlas_Elevator_Intro_Actor_BP();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
