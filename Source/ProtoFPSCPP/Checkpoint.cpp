// Fill out your copyright notice in the Description page of Project Settings.

#include "Checkpoint.h"
#include "Components/StaticMeshComponent.h"
#include "Cube.h"

// Sets default values
ACheckpoint::ACheckpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	SetRootComponent(mesh);
	mesh->SetCollisionProfileName("BlockAllDynamic");
	mesh->SetNotifyRigidBodyCollision(true);
	mesh->OnComponentHit.AddDynamic(this, &ACheckpoint::OnCompHit);
}

// Called when the game starts or when spawned
void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACheckpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACheckpoint::OnCompHit(UPrimitiveComponent* hitcomp, AActor* other, UPrimitiveComponent* othercomp, FVector normalImpulse, const FHitResult& Hit)
{
	if (other) {
		ACube* temp = Cast<ACube>(other);
		if (temp) {
			temp->respawnLocation = respawnLocation;
		}
	}
}

