// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/StaticMeshComponent.h"
#include "Laser.h"
#include "DrawDebugHelpers.h"


// Sets default values
ALaser::ALaser()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	startMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("startMesh"));
	SetRootComponent(startMesh);
}

// Called when the game starts or when spawned
void ALaser::BeginPlay()
{
	Super::BeginPlay();
	Start = startMesh->GetComponentLocation();
	End = startMesh->GetComponentLocation() + startMesh->GetForwardVector() * distance; 
	DrawDebugLine(GetWorld(), Start, End,FColor::Red,true);
}

// Called every frame
void ALaser::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

