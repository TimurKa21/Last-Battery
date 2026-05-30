// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FlashLightActor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "BattaryPikup.generated.h"

class AMainCharacter;
UCLASS()
class LASTBATTERY_API ABattaryPikup : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABattaryPikup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* Sphere;

	UPROPERTY(EditAnywhere, Category="Battaery")
	float BatteryAmount = 25.0f;

	bool bCanPickup = false;

	UPROPERTY()
	AMainCharacter* Currentplayer; 
	
	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComp, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult& SweepResult
	);

	UFUNCTION()
	void OnOverlapEnd(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	);

	void AddEnergy(AMainCharacter* playerCharacter);

	void PickUp();
};
