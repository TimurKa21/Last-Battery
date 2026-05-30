// Fill out your copyright notice in the Description page of Project Settings.


#include "BattaryPikup.h"

#include "MainCharacter.h"


// Sets default values
ABattaryPikup::ABattaryPikup()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->InitSphereRadius(150.0f);
	Sphere->SetupAttachment(Mesh);
	
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	Sphere->OnComponentBeginOverlap.AddDynamic(
	this,
	&ABattaryPikup::OnOverlapBegin);

	Sphere->OnComponentEndOverlap.AddDynamic(
	this,
	&ABattaryPikup::OnOverlapEnd);
	
}

// Called when the game starts or when spawned
void ABattaryPikup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABattaryPikup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABattaryPikup::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMainCharacter* PlayerCharacter =
		Cast<AMainCharacter>(OtherActor);

	if (PlayerCharacter)
	{
		Currentplayer = PlayerCharacter;
		bCanPickup = true;

		PlayerCharacter->CurrentBattery = this;
	}
}

void ABattaryPikup::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AMainCharacter* PlayerCharacter =
		Cast<AMainCharacter>(OtherActor);

	if (PlayerCharacter == Currentplayer)
	{
		PlayerCharacter->CurrentBattery = nullptr;

		Currentplayer = nullptr;
		bCanPickup = false;
	}
}

void ABattaryPikup::AddEnergy(AMainCharacter* PlayerCharacter)
{
	if (!PlayerCharacter)
	{
		return;
	}

	AFlashLightActor* Flashlight =
		PlayerCharacter->GetFlashlight();

	if (Flashlight)
	{
		Flashlight->BateryPower += BatteryAmount;

		Flashlight->BateryPower =
			FMath::Clamp(
				Flashlight->BateryPower,
				0.0f,
				100.0f
			);

		Destroy();
	}
}

void ABattaryPikup::PickUp()
{
	if (bCanPickup && Currentplayer)
	{
		AddEnergy(Currentplayer);
	}
} 
