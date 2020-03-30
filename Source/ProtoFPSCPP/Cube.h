// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cube.generated.h"

UCLASS()
class PROTOFPSCPP_API ACube : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACube();

	UPROPERTY(VisibleAnywhere)
	FVector respawnLocation;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* mesh;

	class 	AProtoFPSCPPCharacter* Player;

	float Alpha = 0.f;

	UPROPERTY(EditAnywhere)
	float Speed = 1.f;

	UPROPERTY(EditAnywhere)
	float scale = 1.f;

	bool respawn = false;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void respawnCube();
	virtual void OnConstruction(const FTransform& Transform) override;

	
};
