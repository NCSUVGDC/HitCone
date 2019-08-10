// Fill out your copyright notice in the Description page of Project Settings.

#include "TCPlayer.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ATCPlayer::ATCPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = mesh;

	springArm->AttachTo(RootComponent);
	springArm->TargetArmLength = 150.f;
	springArm->SetWorldRotation(FRotator(-60.f, 0.f, 0.f));

	camera->AttachTo(springArm, USpringArmComponent::SocketName);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void ATCPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATCPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//FRotator newYaw = GetActorRotation();
	//newYaw.Yaw += mouseInput.X;
	//rotAxis = FVector(cos(rotAxis.X + mouseInput.X), sin(rotAxis.Y + mouseInput.X), 0.0f);
	//SetActorRotation(newYaw);
	//UE_LOG(LogTemp, Log, TEXT("%s"), *rotAxis.ToString());
	
	FRotator newPitch = springArm->GetComponentRotation();
	newPitch.Pitch = FMath::Clamp(newPitch.Pitch + mouseInput.Y, -80.f, 0.f);
	springArm->SetWorldRotation(newPitch);

	{
		if (!CurrentVelocity.IsZero()) {
			FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime) + (rotAxis / 10);
			SetActorLocation(NewLocation);
		}
	}

}

// Called to bind functionality to input
void ATCPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MouseYaw", this, &ATCPlayer::MouseYaw);
	PlayerInputComponent->BindAxis("MousePitch", this, &ATCPlayer::MousePitch);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATCPlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATCPlayer::MoveRight);
}

void ATCPlayer::MouseYaw(float axis) {
	mouseInput.X = axis;
}

void ATCPlayer::MousePitch(float axis) {
	mouseInput.Y = axis;
}

void ATCPlayer::MoveForward(float amount) {
	CurrentVelocity.X = FMath::Clamp(amount, -1.0f, 1.0f) * 100.0f;
}

void ATCPlayer::MoveRight(float amount) {
	CurrentVelocity.Y = FMath::Clamp(amount, -1.0f, 1.0f) * 100.0f;
}