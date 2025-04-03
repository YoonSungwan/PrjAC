// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "MainPlayer.generated.h"

struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
//DECLARE_LOG_CATEGORY_EXTERN(CustomLog_MainPlayer, Log, All);

UCLASS()
class PRJ_AC_API AMainPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditAnywhere, Category="Input Param", meta=(AllowPrivateAccess))
	UInputMappingContext* PlayerMappingContext;

	UPROPERTY(EditAnywhere, Category="Input Param", meta=(AllowPrivateAccess))
	UInputAction* IC_Jump;

	UPROPERTY(EditAnywhere, Category="Input Param", meta=(AllowPrivateAccess))
	UInputAction* IC_Move;
	
	UPROPERTY(EditAnywhere, Category="Input Param", meta=(AllowPrivateAccess))
	UInputAction* IC_Look;

	UPROPERTY(EditAnywhere, Category="Input Param", meta=(AllowPrivateAccess))
	UInputAction* IC_Turn;

	UPROPERTY(EditAnywhere, Category="Input Param", meta=(AllowPrivateAccess))
	UInputAction* IC_DefaultAttack;

	UPROPERTY(EditAnywhere, Category="Input Param", meta=(AllowPrivateAccess))
	UInputAction* IC_Dash;

	// 캐릭터 이동
	UFUNCTION()
	void Input_Move(const FInputActionValue& MoveVal);

	//
	UFUNCTION()
	void Input_Look(const FInputActionValue& LookVal);

	// 캐릭터 회전
	UFUNCTION()
	void Input_Turn(const FInputActionValue& TurnVal);

	// 캐릭터 점프
	UFUNCTION()
	void Input_Jump();
};
