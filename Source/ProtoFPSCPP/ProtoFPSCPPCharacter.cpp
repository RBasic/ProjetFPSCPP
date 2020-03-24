// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ProtoFPSCPPCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MotionControllerComponent.h"
#include "XRMotionControllerBase.h" // for FXRMotionControllerBase::RightHandSourceId
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "DrawDebugHelpers.h"
#include "EngineGlobals.h"
#include "RespawnCubeButton.h"
#include "Engine.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// AProtoFPSCPPCharacter

AProtoFPSCPPCharacter::AProtoFPSCPPCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	//Create PhysicsHandleComponent
	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));
}

void AProtoFPSCPPCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}
void AProtoFPSCPPCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	Start = GetFirstPersonCameraComponent()->GetComponentLocation();
	End = GetFirstPersonCameraComponent()->GetForwardVector() * RaycastDistance + GetFirstPersonCameraComponent()->GetComponentLocation();
	FCollisionQueryParams TraceParams;
	//GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, TraceParams);
	FCollisionObjectQueryParams queryParams = (ECC_TO_BITFIELD(ECC_GameTraceChannel2)|ECC_TO_BITFIELD(ECC_GameTraceChannel3));
	GetWorld()->LineTraceSingleByObjectType(Hit,Start,End,queryParams);

	if(PhysicsHandle->GetGrabbedComponent()) {
		PhysicsHandle->SetTargetLocation(End);
		GEngine->AddOnScreenDebugMessage(-1, 1.F, FColor::Red, FString::Printf(TEXT("You are hitting: %s"),
			*PhysicsHandle->GetGrabbedComponent()->GetName()));
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void AProtoFPSCPPCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AProtoFPSCPPCharacter::Interact);
	PlayerInputComponent->BindAction("Throw", IE_Pressed, this, &AProtoFPSCPPCharacter::Throw);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AProtoFPSCPPCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AProtoFPSCPPCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AProtoFPSCPPCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AProtoFPSCPPCharacter::LookUpAtRate);
}

void AProtoFPSCPPCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AProtoFPSCPPCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AProtoFPSCPPCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AProtoFPSCPPCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AProtoFPSCPPCharacter::Interact()
{
	if (Hit.GetActor()) {
		ARespawnCubeButton* temp = Cast<ARespawnCubeButton>(Hit.GetActor());
		if (temp) {
			temp->Interact();
		}
		else if (Hit.GetComponent()) {
			if (Hit.GetComponent()->GetCollisionObjectType() == ECC_GameTraceChannel3) {
				UStaticMeshComponent* temp = Cast<UStaticMeshComponent>(Hit.GetComponent());
				temp->SetVectorParameterValueOnMaterials("DiffuseColor", FVector(0, 0, 0));
			}
			else if (Hit.GetComponent()->GetCollisionObjectType() == ECC_GameTraceChannel2) {
				if (PhysicsHandle->GetGrabbedComponent()) {
					PhysicsHandle->GetGrabbedComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
					PhysicsHandle->ReleaseComponent();
				}
				else {
					DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 2.0f);
					if (Hit.GetComponent()) {
						PhysicsHandle->GrabComponentAtLocation(Hit.GetComponent(), Hit.BoneName, Hit.GetComponent()->GetCenterOfMass());
						PhysicsHandle->GetGrabbedComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
						if (GEngine) {
							GEngine->AddOnScreenDebugMessage(-1, 1.F, FColor::Red, FString::Printf(TEXT("You are hitting: %s"),
								*Hit.GetActor()->GetName()));
							GEngine->AddOnScreenDebugMessage(-1, 1.F, FColor::Red, FString::Printf(TEXT("Impact Point : %s"),
								*Hit.ImpactPoint.ToString()));
						}
					}
				}
			}
		}
	}
}

void AProtoFPSCPPCharacter::Throw()
{
	if (PhysicsHandle->GetGrabbedComponent()) {
		PhysicsHandle->GetGrabbedComponent()->AddImpulse(GetFirstPersonCameraComponent()->GetForwardVector() * ThrowPower,NAME_None,true);
		PhysicsHandle->GetGrabbedComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
		PhysicsHandle->ReleaseComponent();
	}
}
