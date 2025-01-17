// Fill out your copyright notice in the Description page of Project Settings.

#include "Cube.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ProtoFPSCPPCharacter.h"
#include "EngineGlobals.h"
#include "Engine.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Math/UnrealMathUtility.h"
#include "ConstructorHelpers.h"




// Sets default values
ACube::ACube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UStaticMesh>meshRef(TEXT("/Game/Geometry/Meshes/1M_Cube"));
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	SetRootComponent(mesh);
	mesh->SetStaticMesh(meshRef.Object);
	mesh->SetSimulatePhysics(true);
	mesh->SetNotifyRigidBodyCollision(true);
	mesh->SetCollisionObjectType(ECC_GameTraceChannel2);

	static ConstructorHelpers::FObjectFinder<UMaterialInstance>mat(TEXT("/Game/Materials/CubeMaterialDisintegrate_Inst"));
	mesh->SetMaterial(0,mat.Object);

	respawnLocation = GetActorLocation();
}

// Called when the game starts or when spawned
void ACube::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<AProtoFPSCPPCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
	
}

// Called every frame
void ACube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (respawn && Alpha <= 1) {
		Alpha += DeltaTime * Speed;
		mesh->SetScalarParameterValueOnMaterials("Amount", Alpha);
	}
	else if( Alpha > 1 )
	{		
		Alpha = 0;
		respawnCube();
		
	}
}
void ACube::respawnCube()
{
	if (respawn) {
		respawn = false;
		mesh->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Ignore);
		mesh->SetAllPhysicsLinearVelocity(FVector::ZeroVector);
		mesh->SetAllPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
		SetActorLocation(respawnLocation, true, nullptr, ETeleportType::ResetPhysics);
		mesh->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
		mesh->SetScalarParameterValueOnMaterials("Amount", Alpha);
		
	}
}

void ACube::OnConstruction(const FTransform& Transform)
{
	mesh->SetWorldScale3D(FVector(scale, scale, scale));
}




