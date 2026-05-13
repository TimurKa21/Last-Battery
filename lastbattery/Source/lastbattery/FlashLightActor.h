// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SpotLightComponent.h"
#include "GameFramework/Actor.h"
#include "FlashLightActor.generated.h"

UCLASS()
class LASTBATTERY_API AFlashLightActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFlashLightActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Light")
	USpotLightComponent* SpotLight;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	void ToggleLight();

private:
	bool bIsOn;

};
