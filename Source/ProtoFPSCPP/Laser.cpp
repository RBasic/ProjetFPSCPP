// Fill out your copyright notice in the Description page of Project Settings.
#include "Laser.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "DrawDebugHelpers.h"
#include "ConstructorHelpers.h"
#include "Cube.h"
#include "ProtoFPSCPPCharacter.h"


// Sets default values
ALaser::ALaser()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Particles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));
	SetRootComponent(Particles);

	static ConstructorHelpers::FObjectFinder<UParticleSystem>ParticlesRef(TEXT("/Game/Particles/P_beam"));
	Particles->SetTemplate(ParticlesRef.Object);
}

// Called when the game starts or when spawned
void ALaser::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ALaser::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Alpha += DeltaTime * Speed;
	if (Alpha >= 1) {
		Speed *= -1;
		Alpha = 1;
	}
	else if (Alpha <= 0) { 
		Speed *= -1; 
		Alpha = 0;
	}
	FVector currentStart = FMath::Lerp(GetActorLocation() + StartBegin, GetActorLocation() + StartFinal, Alpha);
	FVector currentEnd = FMath::Lerp(GetActorLocation() + EndBegin, GetActorLocation() + EndFinal, Alpha);
	//DrawDebugLine(GetWorld(), currentStart, currentEnd, FColor::Red, false);
	if (Particles) {
		Particles->SetBeamSourcePoint(0, currentStart, 0);
		Particles->SetBeamTargetPoint(0, currentEnd, 0);
		FHitResult hit;
		FCollisionObjectQueryParams QueryParams;
		DrawDebugLine(GetWorld(), currentStart, currentEnd, FColor::Green, true);
		if (GetWorld()->LineTraceSingleByObjectType(hit, currentStart, currentEnd, QueryParams)) {
			if (hit.GetActor())
			{
				ACube* temp = Cast<ACube>(hit.GetActor());
				if (temp) {
					temp->Player->release();
					temp->respawn = true;
				}			
			}
		}


	}
}