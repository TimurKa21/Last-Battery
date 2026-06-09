// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"


// Sets default values
AOpenDoor::AOpenDoor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Frame =CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Frame"));
	RootComponent = Frame;

	MeshDoor =CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	MeshDoor->SetupAttachment(Frame);

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(Frame);

	ClosedRotation = FRotator(0.f, 0.f, 0.f);

	OpenRotation = FRotator(0.f, 90.f, 0.f);

	isOpen = false;
	bCanInteract = false;

	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	Sphere->OnComponentBeginOverlap.AddDynamic(
	this,
	&AOpenDoor::OnOverlapBegin);

	Sphere->OnComponentEndOverlap.AddDynamic(
	this,
	&AOpenDoor::OnOverlapEnd);
}

// Called when the game starts or when spawned
void AOpenDoor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AOpenDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator TargetRotation =
		isOpen
		? OpenRotation
		: ClosedRotation;

	FRotator NewRotation =
		FMath::RInterpTo(
			MeshDoor->GetRelativeRotation(),
			TargetRotation,
			DeltaTime,
			2.0f
		);

	MeshDoor->SetRelativeRotation(NewRotation);
}

void AOpenDoor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)				
{
	AMainCharacter* CharacterPlayer = Cast<AMainCharacter>(OtherActor);

	if (CharacterPlayer)
	{
		CurrentPlayer = CharacterPlayer;
		bCanInteract = true;

		CharacterPlayer->CurremtOpenDoor = this;
	}
}

void AOpenDoor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{

	AMainCharacter* CharacterPlayer = Cast<AMainCharacter>(OtherActor);

	if (CharacterPlayer == CurrentPlayer)
	{
		CharacterPlayer->CurremtOpenDoor = nullptr;

		CurrentPlayer = nullptr;
		bCanInteract = false;
	}
}

void AOpenDoor::Open()
{
	if (!bCanInteract)
	{
		return;
	}

	if (!CurrentPlayer->bHasKey)
	{
		UE_LOG(LogTemp, Warning, TEXT("Need Key"));
		return;
	}
	
	isOpen = !isOpen;
}

