// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayer.h"
#include "GameFramework/Controller.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

// Sets default values
AMainPlayer::AMainPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMainPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(PlayerMappingContext, 0);
		}
	}
	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Move
		EnhancedInputComponent->BindAction(IC_Move, ETriggerEvent::Triggered, this, &AMainPlayer::Input_Move);
		EnhancedInputComponent->BindAction(IC_Look, ETriggerEvent::Triggered, this, &AMainPlayer::Input_Look);
		EnhancedInputComponent->BindAction(IC_Turn, ETriggerEvent::Triggered, this, &AMainPlayer::Input_Turn);
		
		// Jumping
		EnhancedInputComponent->BindAction(IC_Jump, ETriggerEvent::Started, this, &AMainPlayer::Input_Jump);
	}
}

void AMainPlayer::Input_Move(const FInputActionValue& MoveVal)
{
	//입력 값을 FVector 형태로
	UE_LOG(LogTemp, Warning, TEXT("Input_Move"));
	const FVector _CurrentValue = MoveVal.Get<FVector>();
	AddMovementInput(FTransform(GetControlRotation()).TransformVector(_CurrentValue));
}

void AMainPlayer::Input_Look(const FInputActionValue& LookVal)
{
	UE_LOG(LogTemp, Warning, TEXT("Input_Look"));
	const float _CurrentValue = LookVal.Get<float>() * -1;
	AddControllerPitchInput(_CurrentValue);
}

void AMainPlayer::Input_Turn(const FInputActionValue& TurnVal)
{
	UE_LOG(LogTemp, Warning, TEXT("Input_Turn"));
	const float v = TurnVal.Get<float>();
	AddControllerYawInput(v);
}

// 점프
void AMainPlayer::Input_Jump()
{
	Jump();
}

