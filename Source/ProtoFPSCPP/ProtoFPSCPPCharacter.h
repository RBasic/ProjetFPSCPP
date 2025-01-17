// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ProtoFPSCPPCharacter.generated.h"

class UInputComponent;

UCLASS(config=Game)
class AProtoFPSCPPCharacter : public ACharacter
{
	GENERATED_BODY()

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Gameplay, meta = (AllowPrivateAccess = "true"))
	class UPhysicsHandleComponent* PhysicsHandle;

	FHitResult Hit;
	FVector Start;
	FVector End;

	class UPrimitiveComponent* highlightComp;

public:
	AProtoFPSCPPCharacter();

protected:
	virtual void BeginPlay();
	virtual void Tick(float deltaSeconds) override;

public:	
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	/** Interaction distance with raycast. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
	float RaycastDistance = 400.f;

	/** Velocity impulse applied with no mass. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Gameplay)
	float ThrowPower = 800.f;

	/** Sprint */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Movement: walking")
		float SprintSpeedMultiplier;

protected:
	

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/**Sprint */
	void Sprint();
	void StopSprinting();


protected:
	/** Player interaction with mouse button or F */
	void Interact();
	void Throw();
	
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	/** Returns FirstPersonCameraComponent subobject */
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
	bool release();

};

