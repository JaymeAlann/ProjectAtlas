// Fill out your copyright notice in the Description page of Project Settings.


#include "EveeCharacterClass.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AEveeCharacterClass::AEveeCharacterClass()
{

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(35.f, 12.0f);
	

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	TraceDistance = 430.f;

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Rotation of the character should not affect rotation of boom
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 400.f;
	CameraBoom->SocketOffset = FVector(0.f, 0.f, 75.f);
	CameraBoom->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));

	// Create a camera and attach to boom
	SideViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	SideViewCamera->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 3.f;
	GetCharacterMovement()->AirControl = 0.50f;
	GetCharacterMovement()->JumpZVelocity = 800.f;
	GetCharacterMovement()->MaxAcceleration = 1024.f;
	GetCharacterMovement()->GroundFriction = 8.f;
	GetCharacterMovement()->MaxWalkSpeed = 175.f;

	// Set Sprint Speed Multiplier
	SprintSpeedMultiplier = 2.0f;

	// Setup Interaction Box
	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));
	InteractionBox->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AEveeCharacterClass::BeginPlay()
{
	Super::BeginPlay();
	InteractionBox->OnComponentBeginOverlap.AddDynamic(this, &AEveeCharacterClass::OnBoxBeginOverlap);
	InteractionBox->OnComponentEndOverlap.AddDynamic(this, &AEveeCharacterClass::OnBoxEndOverlap);
	
}

void AEveeCharacterClass::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);
	fTimeHealthDelay = fTimeHealthDelay - DeltaTime;

	if (fTimeHealthDelay <= 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("----------------TICK---------------"));
		fTimeHealthDelay = fHealthPeriod;
	}
}

void AEveeCharacterClass::MoveRight(float Val)
{
	// add movement in the right/left direction
	AddMovementInput(FVector(0.f, -1.f, 0.f), Val);
}

void AEveeCharacterClass::MoveForward(float Val)
{
	// add movement in the forward/backward direction
	AddMovementInput(FVector(-1.f, 0.f, 0.f), Val);
}

void AEveeCharacterClass::InteractPressed()
{
	if (InteractInterface) {
		InteractInterface->Interaction();
	}
	TraceForward();
}

void AEveeCharacterClass::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
}

void AEveeCharacterClass::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
}

// Called to bind functionality to input
void AEveeCharacterClass::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// set up gameplay key bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAxis("MoveForward", this, &AEveeCharacterClass::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AEveeCharacterClass::MoveRight);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AEveeCharacterClass::Sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AEveeCharacterClass::StopSprinting);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AEveeCharacterClass::InteractPressed);


}

void AEveeCharacterClass::TraceForward_Implementation()
{
	FVector CameraLocation;
	FRotator CameraRotation;
	FHitResult HitActor;

	GetController()->GetPlayerViewPoint(CameraLocation, CameraRotation);

	FVector TraceStart = CameraLocation;
	FVector TraceEnd = TraceStart + (CameraRotation.Vector() * TraceDistance);

	FCollisionQueryParams TraceParams;
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitActor, TraceStart, TraceEnd, ECC_Visibility, TraceParams);
	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Orange, false, 5.0f);

	if (bHit)
	{
		DrawDebugBox(GetWorld(), HitActor.ImpactPoint, FVector(5, 5, 5), FColor::Orange, false, 5.0f);
	}
}

void AEveeCharacterClass::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	InteractInterface = Cast<IEveeInteractInterface>(OtherActor);

	if (InteractInterface)
	{
		InteractInterface->ShowInteractWidget();
	}
}

void AEveeCharacterClass::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (InteractInterface)
	{
		InteractInterface->HideInteractWidget();
	}
}

void AEveeCharacterClass::Sprint() 
{
	GetCharacterMovement()->MaxWalkSpeed *= SprintSpeedMultiplier;
}

void AEveeCharacterClass::StopSprinting()
{
	GetCharacterMovement()->MaxWalkSpeed /= SprintSpeedMultiplier;
}

