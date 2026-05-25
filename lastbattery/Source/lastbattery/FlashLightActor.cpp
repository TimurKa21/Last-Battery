// Fill out your copyright notice in the Description page of Project Settings.


#include "FlashLightActor.h"

// Sets default values
AFlashLightActor::AFlashLightActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh Light");
	RootComponent = Mesh;

	SpotLight = CreateDefaultSubobject<USpotLightComponent>("Spot Light");
	SpotLight->SetupAttachment(Mesh);

	SpotLight->Intensity = 20000.0f;
	SpotLight->OuterConeAngle =  30.0f;
	bIsOn = true;
}

// Called when the game starts or when spawned
void AFlashLightActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFlashLightActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsOn)
	{
		BateryPower -= BatteryDrainSpeed * DeltaTime;
	}
		BateryPower = FMath::Clamp(BateryPower, 0.0f, 100.0f);
}

void AFlashLightActor::ToggleLight()
{
	if (BateryPower <= 0.0f)
	{
		return;
	}
	
	  bIsOn = !bIsOn;
	  SpotLight->SetVisibility(bIsOn);
}

