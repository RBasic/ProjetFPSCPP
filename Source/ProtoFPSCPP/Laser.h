// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Laser.generated.h"

UCLASS()
class PROTOFPSCPP_API ALaser : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALaser();

	UPROPERTY(EditAnywhere, meta=(MakeEditWidget = true))
	FVector StartBegin;

	UPROPERTY(EditAnywhere, meta = (MakeEditWidget = true))
	FVector StartFinal;

	UPROPERTY(EditAnywhere, meta=(MakeEditWidget = true))
	FVector EndBegin;

	UPROPERTY(EditAnywhere, meta = (MakeEditWidget = true))
	FVector EndFinal;

	float Alpha = 0.f;

	UPROPERTY(EditAnywhere)
	float Speed = 1.f;

	UPROPERTY(EditAnywhere)
	class UParticleSystemComponent* Particles;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
