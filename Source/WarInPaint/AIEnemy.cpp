// Fill out your copyright notice in the Description page of Project Settings.


#include "AIEnemy.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"
#include "WarInPaintGameMode.h"
#include "Net/UnrealNetwork.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

// Sets default values
AAIEnemy::AAIEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));

	PawnSensingComp->OnSeePawn.AddDynamic(this, &AAIEnemy::OnPawnSeen);

	AIState = EAIState::Searching;
}

// Called when the game starts or when spawned
void AAIEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	OriginalRotation = GetActorRotation();

	if (bPatrol)
	{
		MoveToNextPatrolPoint();
	}
}

// Called every frame
void AAIEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAIEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAIEnemy::OnPawnSeen(APawn* SeenPawn)
{
	if (SeenPawn == nullptr)
	{
		return;
	}

	DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(), 32.0f, 12, FColor::Red, false, 10.0f);

	SetAIState(EAIState::Alerted);

	if (Controller)
	{
		Controller->StopMovement();
	}

	SetAIState(EAIState::Attack);
}

void AAIEnemy::ResetOrientation()
{
	if (AIState == EAIState::Alerted)
	{
		return;
	}

	SetActorRotation(OriginalRotation);

	SetAIState(EAIState::Searching);

	if (bPatrol)
	{
		MoveToNextPatrolPoint();
	}
}

void AAIEnemy::OnRep_AIState()
{
	OnStateChanged(AIState);
}

void AAIEnemy::SetAIState(EAIState NewState)
{
	if (AIState == NewState)
	{
		return;
	}

	AIState = NewState;
	OnRep_AIState();
}
