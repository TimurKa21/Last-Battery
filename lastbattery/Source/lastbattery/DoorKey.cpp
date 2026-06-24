// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorKey.h"

#include "MainCharacter.h"
#include "Components/SphereComponent.h"


// Sets default values
ADoorKey::ADoorKey()
{
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
   &ADoorKey::OnOverlapBegin);

	Sphere->OnComponentEndOverlap.AddDynamic(
    this,
    &ADoorKey::OnOverlapEnd);
}


// Called when the game starts or when spawned
void ADoorKey::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoorKey::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ADoorKey::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMainCharacter* playerCharacter = Cast<AMainCharacter>(OtherActor);

	if (playerCharacter)
	{
		CurrentCharacter = playerCharacter;
		playerCharacter->KeyPickUp = this;
	}
}

void ADoorKey::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	AMainCharacter* playeraCharacter = Cast<AMainCharacter>(OtherActor);

	if (playeraCharacter == CurrentCharacter)
	{
		playeraCharacter->KeyPickUp = nullptr;
		CurrentCharacter = nullptr;
	}
}

void ADoorKey::KeyPickUp()
{
	if (!CurrentCharacter)
	{
		return;
	}

	CurrentCharacter->bHasKey = true;

	Destroy();
}


