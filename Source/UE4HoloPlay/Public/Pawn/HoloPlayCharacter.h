// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HoloPlayCharacter.generated.h"

UCLASS()
class AHoloPlayCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AHoloPlayCharacter(const FObjectInitializer& ObjectInitializer);

	//!< AActor
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	//!< APawn
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE void MoveForward(float Value) { if (Value != 0.0f) { AddMovementInput(GetActorForwardVector(), Value); } }
	FORCEINLINE void MoveRight(float Value) { if (Value != 0.0f) { AddMovementInput(GetActorRightVector(), Value); } }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Actor)
	class AHoloPlayCapture* HoloPlayCapture;
};
