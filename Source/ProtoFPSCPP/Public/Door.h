// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimSequence.h"
#include "InteractibleInterface.h"
#include "Door.generated.h"

UCLASS(Blueprintable)
class PROTOFPSCPP_API ADoor : public AActor, public IInteractibleInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UAnimSequenceBase* ClosedAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UAnimSequenceBase* OpeningAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UAnimSequenceBase* OpenedAnimation;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	//	class USkeletalMesh* DoorMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh)
		class USkeletalMeshComponent* DoorMeshComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnOpeningFinished();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual bool Interact() override;
};
