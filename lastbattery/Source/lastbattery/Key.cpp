// Fill out your copyright notice in the Description page of Project Settings.


#include "Key.h"

#include "MainCharacter.h"
#include "OpenDoor.h"


// Sets default values
AKey::AKey()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(Mesh);

	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	
	Sphere->OnComponentBeginOverlap.AddDynamic(
	this,
	&AKey::OnOverlapBegin);

	Sphere->OnComponentEndOverlap.AddDynamic(
	this,
	&AKey::OnOverlapEnd);
}

// Called when the game starts or when spawned
void AKey::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AKey::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AKey::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMainCharacter* playerCharacter = Cast<AMainCharacter>(OtherActor);

	if (playerCharacter)
	{
		CurrentCharacter = playerCharacter;
		playerCharacter->KeyPickUp = this;
	}
}

void AKey::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	AMainCharacter* playeraCharacter = Cast<AMainCharacter>(OtherActor);

	if (playeraCharacter == CurrentCharacter)
	{
		playeraCharacter->KeyPickUp = nullptr;
		CurrentCharacter = nullptr;
	}
}

void AKey::KeyPickUp()
{
	if (!CurrentCharacter)
	{
		return;
	}

	CurrentCharacter->bHasKey = true;

	Destroy();
}

