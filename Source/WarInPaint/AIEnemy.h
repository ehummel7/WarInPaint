// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AIEnemy.generated.h"




class UPawnSensingComponent;


UENUM(BlueprintType)
enum class EAIState : uint8
{

	Searching,

	Alerted,

	Attack
};


UCLASS()

class WARINPAINT_API AAIEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAIEnemy();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/* Let the guard go on patrol */
	UPROPERTY(EditInstanceOnly, Category = "AI")
		bool bPatrol;

	/* First of two patrol points to patrol between */
	UPROPERTY(EditInstanceOnly, Category = "AI", meta = (EditCondition = "bPatrol"))
		AActor* FirstPatrolPoint;

	/* Second of two patrol points to patrol between */
	UPROPERTY(EditInstanceOnly, Category = "AI", meta = (EditCondition = "bPatrol"))
		AActor* SecondPatrolPoint;

	// The current point the actor is either moving to or standing at
	AActor* CurrentPatrolPoint;

	void MoveToNextPatrolPoint();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UPawnSensingComponent* PawnSensingComp;

	UFUNCTION()
		void OnPawnSeen(APawn* SeenPawn);

	FRotator OriginalRotation;

	UFUNCTION()
		void ResetOrientation();

	FTimerHandle TimerHandle_ResetOrientation;

	UPROPERTY(ReplicatedUsing = OnRep_AIState)
		EAIState AIState;

	UFUNCTION()
		void OnRep_AIState();

	void SetAIState(EAIState NewState);

	UFUNCTION(BlueprintImplementableEvent, Category = "AI")
		void OnStateChanged(EAIState NewState);
};
