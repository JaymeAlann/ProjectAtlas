// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
#include "EveeInteractInterface.h"
#include "InteractableComputer.generated.h"

UCLASS()
class SIDESCROLLTEMP_API AInteractableComputer : public AActor, public IEveeInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableComputer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	bool ComputerPowerOn;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ComputerMesh;

	UPROPERTY(EditAnywhere)
	UWidgetComponent* InteractWidget;

	UPROPERTY(EditAnywhere)
	class UMaterialInstance* ComputerOnMat;

	UPROPERTY(EditAnywhere)
	class UMaterialInstance* ComputerOffMat;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interaction() override;
	virtual void ShowInteractWidget() override;
	virtual void HideInteractWidget() override;

};
