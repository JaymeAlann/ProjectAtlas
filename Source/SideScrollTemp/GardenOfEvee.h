// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GardenOfEvee.generated.h"

/**
 * 
 */
UCLASS(minimalapi)
class AGardenOfEvee : public AGameMode
{
	GENERATED_BODY()

public:
	AGardenOfEvee();
	virtual ~AGardenOfEvee() = default;
	
};
