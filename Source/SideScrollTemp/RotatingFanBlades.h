// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotatingFanBlades.generated.h"

UCLASS()
class SIDESCROLLTEMP_API ARotatingFanBlades : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARotatingFanBlades();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Blades;

	UFUNCTION()
		void setRotateSpeed(float RotationSpeed);


protected:
	UPROPERTY(EditAnywhere)
	float RotateSpeed = 1.5f;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
