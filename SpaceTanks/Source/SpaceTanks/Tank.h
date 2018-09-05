// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankAimingComponent.h"

#include "Tank.generated.h"

UCLASS()
class SPACETANKS_API ATank : public APawn
{
	GENERATED_BODY()

public:

  void AimAt(FVector HitLocation);

  UFUNCTION(BlueprintCallable, Category = Setup)
  void SetBarrelReference(UStaticMeshComponent* BarrelToSet);

protected:
	
  UTankAimingComponent* TankAimingComponent = nullptr;


private:
	// Sets default values for this pawn's properties
	ATank();

  // Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

  UStaticMeshComponent* Barrel;

  UPROPERTY(EditAnywhere, Category = Firing)
  float FiringSpeed = 100000; // 1000 m/s - TODO find sensible default
	
};
