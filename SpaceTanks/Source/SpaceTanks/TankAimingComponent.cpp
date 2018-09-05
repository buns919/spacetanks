// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	// in the Tank BP, BeginPlay calls SetBarrelReference and sets the BP's barrel from the static mesh Barrel object
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTankAimingComponent::AimAt(FVector HitLocation, float FiringSpeed) {
  auto OurTankName = GetOwner()->GetName();

  if (!Barrel) {
    UE_LOG(LogTemp, Error, TEXT("No barrel reference on: %s"), *OurTankName);
    return;
  }

  if (!FiringSpeed) {
    UE_LOG(LogTemp, Error, TEXT("No firing speed found on: %s"), *OurTankName);
    return;
  }

  FVector BarrelLocation = Barrel->GetComponentLocation();
  if (BarrelLocation == FVector(0)) {
    UE_LOG(LogTemp, Error, TEXT("Unable to retrieve BarrelLocation from Barrel->GetComponentLocation(): %s"), *OurTankName);
    return;
  }

  FVector OutFiringVelocity;
  FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile")); // Socket set in Content/Tank/tank_fbx_barrel
  FCollisionResponseParams OutResponseParam;
  TArray<AActor> OutActorsToIgnore;

  // calculate the OutLaunchVelocity
  if (UGameplayStatics::SuggestProjectileVelocity(
    this,
    OutFiringVelocity, // OUT
    StartLocation,
    HitLocation,
    FiringSpeed,
    false,
    0,
    0,
    ESuggestProjVelocityTraceOption::TraceFullPath // or ESuggestProjVelocityTraceOption::DoNotTrace
  )) {
    
    FVector AimDirection = OutFiringVelocity.GetSafeNormal();
    UE_LOG(LogTemp, Warning, TEXT("---%s Barrel Aim Direction: %s"), *OurTankName, *AimDirection.ToString());

  }



  //UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s, from BarrelLocation: %s"), *OurTankName, *HitLocation.ToString(), *BarrelLocation.ToString());
  //UE_LOG(LogTemp, Warning, TEXT("FiringSpeed: %f"), FiringSpeed);
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent * BarrelToSet) {
  Barrel = BarrelToSet;
}
