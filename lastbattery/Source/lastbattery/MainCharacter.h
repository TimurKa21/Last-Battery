// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FlashLightActor.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

UCLASS()
class LASTBATTERY_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArm; 
	
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;
	
	UPROPERTY()
	AFlashLightActor* SpawnFlashLightActor;

	UPROPERTY(EditAnywhere, Category = "FlashLight")
	TSubclassOf<AFlashLightActor> FlashLightClass;
	
	UPROPERTY(EditAnywhere,Category="Movment")
	float Walking = 600.0f;

	UPROPERTY(EditAnywhere, Category="Movment")
	float Runing = 800.0f;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void ForwardBack(float Value);
	
	void LeftRight(float Value);

	void Runingg();

	void StopRunning();

	void OnToggleFlashlight();
};
