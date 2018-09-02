// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay() {
  Super::BeginPlay();

  ATank* Tank = GetControlledTank();

  if (Tank) {
    UE_LOG(LogTemp, Warning, TEXT("ATankAIController::GetControlledTank(): Tank found - %s"), *(Tank->GetName()));
  }
  else {
    UE_LOG(LogTemp, Error, TEXT("ATankAIController::GetControlledTank() - Tank not found from %s"), *(GetPawn()->GetName()));
  }


  ATank* PlayerControlledTank = GetPlayerTank();

  if (PlayerControlledTank) {
    UE_LOG(LogTemp, Warning, TEXT("ATankAIController %s ::GetPlayerTank(): Tank found - %s"), *(Tank->GetName()), *(PlayerControlledTank->GetName()));
  }
  else {
    UE_LOG(LogTemp, Error, TEXT("ATankAIController %s ::GetPlayerTank() - Player Controlled Tank not found."), *(Tank->GetName()));
  }
}

ATank* ATankAIController::GetControlledTank() const {
  return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
  auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

  if (!PlayerPawn) { return nullptr; }
  return Cast<ATank>(PlayerPawn);
}


