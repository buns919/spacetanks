// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


ATankPlayerController::ATankPlayerController() {
  // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;
}

void ATankPlayerController::BeginPlay() {
  Super::BeginPlay();

  // ATank*
  auto ControlledTank = GetControlledTank();

  if (ControlledTank) {
    UE_LOG(LogTemp, Warning, TEXT("ATankPlayerController::GetControlledTank(): Tank found - %s"), *(ControlledTank->GetName()));
  }
  else {
    UE_LOG(LogTemp, Error, TEXT("ATankPlayerController::GetControlledTank() - Tank not found"));
  }
}

void ATankPlayerController::Tick(float DeltaTime) {
  Super::Tick(DeltaTime);

  AimTowardsCrossHair();
}

ATank* ATankPlayerController::GetControlledTank() const {
  return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrossHair() {
  if (!GetControlledTank()) {
    UE_LOG(LogTemp, Warning, TEXT("ATankPlayerController::AimTowardsCrossHair() ControlledTank missing"));
    return;
  }

  FVector OutHitLocation; // OUT param
  if (GetSightRayHitLocation(OutHitLocation)) { // Has a side effect is going to line trace
    UE_LOG(LogTemp, Warning, TEXT("HitLocation direction: %s"), *OutHitLocation.ToString());
    
    // tell controlled tank to aim at this point

  }


  
}

// Get world location from linetrace through crosshair, true if it hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
  // Find the crosshair position in pixel coordinates
  int32 ViewportSizeX, ViewportSizeY;
  GetViewportSize(ViewportSizeX, ViewportSizeY);
  FVector LookDirection;
  FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

  // Get Look Direction
  // "de-project" screen position of the crosshair to a world direction
  if (GetLookDirection(ScreenLocation, LookDirection)) {
    //UE_LOG(LogTemp, Warning, TEXT("LookDirection: %s"), *LookDirection.ToString());

    // linereace along that look direction, and see what we hit (up to a max range)
    GetLookVectorHitLocation(LookDirection, OutHitLocation);
  }

  return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const {
  FVector CameraWorldLocation; // this can be discarded, it is only needed to call DeprojectScreenPositionToWorld
  return DeprojectScreenPositionToWorld(
    ScreenLocation.X,
    ScreenLocation.Y,
    CameraWorldLocation,
    LookDirection
  );
  
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const {
  // Ray cast out to reach distance
  FHitResult HitResult;
  FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

  FVector StartLocation = PlayerCameraManager->GetCameraLocation();
  FVector EndLocation = StartLocation + (LookDirection * LineTraceRange);

  // if line trace succeeds
  if (GetWorld()->LineTraceSingleByChannel(
    HitResult, // OUT
    StartLocation, // FVector
    EndLocation, // FVector
    ECollisionChannel::ECC_Visibility
  )) {
    // set hit location
    HitLocation = HitResult.Location;
    return true;
  }
  else {
    HitLocation = FVector(0);
    return false;
  }
}
