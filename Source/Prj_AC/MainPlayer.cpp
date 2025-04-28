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

	bUseControllerRotationYaw = false;  // 컨트롤러 회전 무시
	GetCharacterMovement()->bOrientRotationToMovement = true;
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

void AMainPlayer::Input_Move(const FInputActionValue& Value)
{
	// 입력 값
	const FVector2D MovementVector = Value.Get<FVector2D>();

	// 캐릭터 로컬 방향 기준으로 변환
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation = FRotator(0, Rotation.Yaw, 0);

	// 행렬을 통해 X, Y축
	const FRotationMatrix RotationMatrix(YawRotation);
	const FVector ForwardLocalVector = RotationMatrix.GetUnitAxis(EAxis::X);
	const FVector RightLocalVector = RotationMatrix.GetUnitAxis(EAxis::Y);

	// 이동
	AddMovementInput(ForwardLocalVector, MovementVector.Y);
	AddMovementInput(RightLocalVector, MovementVector.X);
}

void AMainPlayer::Input_Look(const FInputActionValue& Value)
{
	float MouseLookValue = Value.Get<float>() * -1;
	AddControllerPitchInput(MouseLookValue);
}

void AMainPlayer::Input_Turn(const FInputActionValue& Value)
{
	const float MouseTurnValue = Value.Get<float>();
	AddControllerYawInput(MouseTurnValue);
}

// 점프
void AMainPlayer::Input_Jump()
{
	Jump();
}

