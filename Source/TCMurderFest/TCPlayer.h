// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "TCPlayer.generated.h"

UCLASS()
class TCMURDERFEST_API ATCPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATCPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MouseYaw(float axis);
	void MousePitch(float axis);

	void MoveForward(float amount);
	void MoveRight(float amount);

	//Vector
	FVector2D mouseInput;

	UPROPERTY(EditAnywhere)
		USpringArmComponent* springArm;
	UCameraComponent* camera;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* mesh;

	UPROPERTY(EditAnywhere)
		USceneComponent* OurVisibleComponent;

	FVector CurrentVelocity;
	FVector rotAxis = FVector(0.0f, 0.0f, 0.0f);
};
