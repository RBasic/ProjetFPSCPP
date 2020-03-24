// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/StaticMeshComponent.h"
#include "RespawnCubeButton.h"

// Sets default values
ARespawnCubeButton::ARespawnCubeButton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	SetRootComponent(mesh);
}

// Called when the game starts or when spawned
void ARespawnCubeButton::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ARespawnCubeButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARespawnCubeButton::Interact() {
	if (cubeRef) {
		cubeRef->SetActorLocation(respawnLocation);
	}
}
