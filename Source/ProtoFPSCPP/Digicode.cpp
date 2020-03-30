// Fill out your copyright notice in the Description page of Project Settings.


#include "Digicode.h"
#include "Components/TextRenderComponent.h"

// Sets default values
ADigicode::ADigicode()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	code.Init(0, 6);
	code[3] = 7;
	textCode = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRender"));
	SetRootComponent(textCode);
}

// Called when the game starts or when spawned
void ADigicode::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void ADigicode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	textCode->SetText("");
	FString temp = "";
	for (int i = 0; i < code.Num(); i++) {
		temp.Append(FString::FromInt(code[i]));
	}
	textCode->SetText(FText::FromString(temp));
}

bool ADigicode::verifCode()
{
	for (int i = 0; i < correctCode.Num(); i++) {
		if (correctCode[i] != code[i]) return false;
	}
	return true;
}

void ADigicode::changeNumber(int index, bool up)
{
	up ? code[index]++ : code[index]--;
	if(code[index] > 9) code[index] = 0;
	if (code[index] < 0) code[index] = 9;
	if (verifCode()) {
		//Gagne
	}
}

