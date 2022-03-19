// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <Runtime/Engine/Classes/Components/BoxComponent.h>
#include <SideScrollTemp/EveeInteractInterface.h>
#include "EveeCharacterClass.generated.h"

UCLASS()
class SIDESCROLLTEMP_API AEveeCharacterClass : public ACharacter
{
	GENERATED_BODY()

	/** Side view camera */
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* SideViewCamera;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* CameraBoom;

private:

	IEveeInteractInterface* InteractInterface = nullptr;

	float timer = 0.0f;
	const float fHealthPeriod = 1.0f;
	float fTimeHealthDelay = fHealthPeriod;

	

public:
	// Sets default values for this character's properties
	AEveeCharacterClass();

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCamera; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Character Movement: Walking")
	float SprintSpeedMultiplier;




	void Sprint();
	void StopSprinting();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	/** Called for side to side input */
	void MoveRight(float Val);

	/** Called for deeper or closer input */
	void MoveForward(float Value);

	void InteractPressed();

	/** Handle touch inputs. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Handle touch stop event. */
	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UFUNCTION(BlueprintNativeEvent)
	void TraceForward();
	void TraceForward_Implementation();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interact")
	float TraceDistance;

	UPROPERTY(EditAnywhere, Category = "Interact")
	UBoxComponent* InteractionBox;

	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


};
