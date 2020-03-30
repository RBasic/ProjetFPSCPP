// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Digicode.generated.h"

UCLASS()
class PROTOFPSCPP_API ADigicode : public AActor
{
	GENERATED_BODY()

	TArray<int> code;

	UPROPERTY(EditAnywhere)
	TArray<int> correctCode;

	UPROPERTY(EditAnywhere)
	class UTextRenderComponent* textCode;

	UPROPERTY(EditAnywhere)
	class UStaticMesh* arrowMesh;

	UPROPERTY(EditAnywhere)
	TArray<UStaticMeshComponent*> arrows;


public:	
	// Sets default values for this actor's properties
	ADigicode();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	bool verifCode();
	void changeNumber(int index, bool up);
};
