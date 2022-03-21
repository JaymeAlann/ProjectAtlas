// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableComputer.h"

// Sets default values
AInteractableComputer::AInteractableComputer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));

	ComputerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CoomputerMesh"));
	ComputerMesh->SetupAttachment(RootComponent);

	CPLightPro = CreateDefaultSubobject< URectLightComponent>(TEXT("ComputerReflectionLight"));
	CPLightPro->SetupAttachment(RootComponent);
	CPLightPro->SetSourceWidth(59.0f);
	CPLightPro->SetSourceHeight(34.44f);
	CPLightPro->SetAttenuationRadius(140.0f);
	CPLightPro->SetIntensity(1000.0f);
	CPLightPro->SetBarnDoorAngle(40.0f);
	CPLightPro->SetBarnDoorLength(20.0f);
	CPLightPro->SetLightColor(FLinearColor(0.171441,0.42869,0.361307,1));

	InteractWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractionWidget"));
	InteractWidget->SetupAttachment(RootComponent);
	InteractWidget->SetVisibility(false);

	ComputerPowerOn = true;

	ComputerOffMat = CreateDefaultSubobject <UMaterialInstance>(TEXT("ComputerOffMaterial"));
	ComputerOnMat = CreateDefaultSubobject <UMaterialInstance>(TEXT("ComputerOnMaterial"));
	
}

// Called when the game starts or when spawned
void AInteractableComputer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractableComputer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractableComputer::Interaction()
{
	if (ComputerPowerOn)
	{
		ComputerMesh->SetMaterial(0, ComputerOffMat);
		CPLightPro->SetLightColor(FLinearColor(1, 0.22216, 0.321932, 1));
		ComputerPowerOn = false;
	}
	else {
		ComputerMesh->SetMaterial(0, ComputerOnMat);
		CPLightPro->SetLightColor(FLinearColor(0.171441, 0.42869, 0.361307, 1));
		ComputerPowerOn = true;
	}
	UE_LOG(LogTemp, Warning, TEXT("Computer Interacted"));

}

void AInteractableComputer::ShowInteractWidget()
{
	InteractWidget->SetVisibility(true);
}

void AInteractableComputer::HideInteractWidget()
{
	InteractWidget->SetVisibility(false);
}


