// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Door.h"
#include "TimerManager.h"
#include "Animation/AnimInstance.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	DoorMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("DoorMesh");
	DoorMeshComponent->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	DoorMeshComponent->SetCollisionProfileName(TEXT("BlockAll"));
	DoorMeshComponent->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel3);
	if (ClosedAnimation)
	{
		DoorMeshComponent->GetAnimInstance()->PlaySlotAnimationAsDynamicMontage(ClosedAnimation, FName("DefaultSlot"), 0.0f, 0.f, 1.f, 1);
	}
	SetRootComponent(DoorMeshComponent);
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	DoorMeshComponent->GetAnimInstance()->PlaySlotAnimationAsDynamicMontage(ClosedAnimation, FName("DefaultSlot"), 0.0f, 0.f, 1.0f, 1);
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoor::OnOpeningFinished()
{
	DoorMeshComponent->GetAnimInstance()->PlaySlotAnimationAsDynamicMontage(OpenedAnimation, FName("DefaultSlot"), 0.0f, 0.f, 1.0f, 1);
	GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Emerald, "Open !");
}

bool ADoor::Interact()
{
	if (OpeningAnimation && OpenedAnimation)
	{
		DoorMeshComponent->SetVectorParameterValueOnMaterials("StateColor", FVector(0.f, 35.f, 0.3f));
		FTimerHandle AnimDelayHandle;
		DoorMeshComponent->GetAnimInstance()->PlaySlotAnimationAsDynamicMontage(OpeningAnimation, FName("DefaultSlot"), 0.0f, 0.f);
		GetWorldTimerManager().SetTimer(AnimDelayHandle, this, &ADoor::OnOpeningFinished, OpeningAnimation->GetPlayLength(), false);
		return true;
	}
	
	return false;
}