// Fill out your copyright notice in the Description page of Project Settings.

#include "Cube.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ACube::ACube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	SetRootComponent(mesh);
	mesh->SetSimulatePhysics(true);
	mesh->SetNotifyRigidBodyCollision(true);
	mesh->SetCollisionObjectType(ECC_GameTraceChannel2);

	respawnLocation = GetActorLocation();
}

// Called when the game starts or when spawned
void ACube::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACube::respawnCube()
{
	mesh->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Ignore);
	SetActorLocation(respawnLocation,true,nullptr,ETeleportType::ResetPhysics);
	mesh->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
}

