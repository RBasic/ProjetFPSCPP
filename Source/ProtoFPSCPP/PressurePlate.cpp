// Fill out your copyright notice in the Description page of Project Settings.

#include "PressurePlate.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "ConstructorHelpers.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Engine/StaticMesh.h"
#include "Components/PrimitiveComponent.h"

// Sets default values
APressurePlate::APressurePlate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>meshRef(TEXT("/Game/Geometry/Meshes/1M_Cube"));
	SetRootComponent(mesh);
	mesh->SetStaticMesh(meshRef.Object);
	static ConstructorHelpers::FObjectFinder<UMaterialInstance>mat(TEXT("/Game/Materials/Mat_Pillar"));
	mesh->SetMaterial(0, mat.Object);
	box = CreateDefaultSubobject<UBoxComponent>(TEXT("box"));
	box->SetupAttachment(mesh);
	box->SetBoxExtent(mesh->GetStaticMesh()->GetBoundingBox().GetExtent());
	box->SetRelativeLocation(FVector(0.f, 0.f, 20.f));
	box->OnComponentBeginOverlap.AddDynamic(this, &APressurePlate::BoxBeginOverlap);


}

// Called when the game starts or when spawned
void APressurePlate::BeginPlay()
{
	Super::BeginPlay();
	FVector ActorLocation = GetActorLocation();
	
}

// Called every frame
void APressurePlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (overlap && mesh->GetRelativeTransform().GetLocation().Z < -20.f) {
		FVector ActorLocation = mesh->GetRelativeTransform().GetLocation();
		mesh->SetRelativeLocation(GetActorLocation()-FVector(0.f, 0.f, -1.f*DeltaTime));
	}
}

void APressurePlate::BoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	overlap = true;
}



