// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"

// Called when the game starts or when spawned
void APawnTurret::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);

	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if(!PlayerPawn || ReturnDistanceToPlayer() > FireRange)
	{
		return;
	}

	RotateTurretFunction(PlayerPawn->GetActorLocation());
}


void APawnTurret::CheckFireCondition()
{
	if(!PlayerPawn || !PlayerPawn->GetIsPlayerAlive())
	{
		return;
	}

	if(ReturnDistanceToPlayer() <= FireRange)
	{
		Fire();
	}
}

float APawnTurret::ReturnDistanceToPlayer() 
{
	if(!PlayerPawn)
	{
		return 0.0f;
	}

	float distance = FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
	return distance;
}

void APawnTurret::HandleDestruction()
{
	//call base handle destruction
	Super::HandleDestruction();

	Destroy();
}