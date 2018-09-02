// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"

#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SPACETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
  ATankPlayerController();
  virtual void BeginPlay() override;
  virtual void Tick(float DeltaTime) override;
  
  ATank* GetControlledTank() const;

  // Start the tank moving the barrel so that a shot would hit where the crosshair intersects the world
  void AimTowardsCrossHair();

  // Return an OUT parameter, true if hit landscare
  bool GetSightRayHitLocation(FVector& OutHitLocation) const;
  
  UPROPERTY(EditAnywhere)
  float CrossHairXLocation = 0.5f;

  UPROPERTY(EditAnywhere)
  float CrossHairYLocation = 0.42f; // this must correlate to the BP_PlayerUI White Center Dot Location
	
  bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

  bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

  UPROPERTY(EditAnywhere)
  float LineTraceRange = 1000000; // 1 kilometer in cm's
};
