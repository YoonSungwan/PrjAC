// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimIns.h"

void UPlayerAnimIns::StartPlayMontage(UAnimMontage* Montage, float PlayRate)
{
	if(Montage)
	{
		if(!Montage_IsPlaying(Montage))
		{
			Montage_Play(Montage, PlayRate);
		}
	}
}

void UPlayerAnimIns::OnAttackMontageEnded(UAnimInstance* Montage, bool bInterrupted)
{
	UE_LOG(LogTemp, Warning, TEXT("Log : Montage Ended - %d"), bInterrupted);
}
