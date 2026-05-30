// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"

#include "BattaryPikup.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(GetMesh(), TEXT("headSocket"));
	CameraComponent->bUsePawnControlRotation = true;

	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;

}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (FlashLightClass)
	{
		SpawnFlashLightActor =
			GetWorld()->SpawnActor<AFlashLightActor>(
				FlashLightClass
			);
	}
	
    if (SpawnFlashLightActor)
    {
	    SpawnFlashLightActor->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("FlashSocket"));
    }
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("ForwardBack", this,&AMainCharacter::ForwardBack);
	PlayerInputComponent->BindAxis("RightLeft", this,&AMainCharacter::LeftRight);

	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AMainCharacter::Runingg);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &AMainCharacter::StopRunning);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("ToggleFlashLight", IE_Pressed, this, &AMainCharacter::OnToggleFlashlight);

	PlayerInputComponent->BindAction("Interact",IE_Pressed,this,&AMainCharacter::Interact);

}

void AMainCharacter::ForwardBack(float Value)
{
	FRotator Rotation = Controller->GetControlRotation();
	FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

	FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction, Value);
	
}

void AMainCharacter::LeftRight(float Value)
{
	FRotator Rotation = Controller->GetControlRotation();
	FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

	FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void AMainCharacter::Runingg()
{
	GetCharacterMovement()->MaxWalkSpeed = Runing;
}

void AMainCharacter::StopRunning()
{
	GetCharacterMovement()->MaxWalkSpeed = Walking;
}

void AMainCharacter::OnToggleFlashlight()
{
	if (SpawnFlashLightActor)
	{
		SpawnFlashLightActor->ToggleLight();
	}
}

void AMainCharacter::Interact()
{
	if (CurrentBattery)
	{
		CurrentBattery->PickUp();
	}
}

