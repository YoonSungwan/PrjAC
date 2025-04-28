// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimIns.generated.h"

/**
 * 
 */
UCLASS()
class PRJ_AC_API UPlayerAnimIns : public UAnimInstance
{
	GENERATED_BODY()

public:
	// 몽타주 플레이
	UFUNCTION()
	void StartPlayMontage(UAnimMontage* Montage, float PlayRate = 1.0f);

	// 몽타주 재생 끝나고
	UFUNCTION()
	void OnAttackMontageEnded(UAnimInstance* AnimIns, bool bInterrupted);
};
