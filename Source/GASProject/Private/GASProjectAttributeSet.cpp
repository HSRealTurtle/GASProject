// Fill out your copyright notice in the Description page of Project Settings.


#include "GASProjectAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"

UGASProjectAttributeSet::UGASProjectAttributeSet()
{

}

void UGASProjectAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
		HealthChangeDelegate.Broadcast(GetHealth(), Data.EffectSpec.StackCount);
	}
	if (Data.EvaluatedData.Attribute == GetMoveSpeedAttribute())
	{
		SetMoveSpeed(FMath::Clamp(GetMoveSpeed(), 0.0f, 1200.0f));
		MoveSpeedChangeDelegate.Broadcast(GetMoveSpeed(), Data.EffectSpec.StackCount);
	}
	if (Data.EvaluatedData.Attribute == GetMoveSpeedMultiplierAttribute())
	{
		SetMoveSpeedMultiplier(FMath::Clamp(GetMoveSpeedMultiplier(), 0.1f, 2.0f));
		MoveSpeedMultiplierDelegate.Broadcast(GetMoveSpeedMultiplier(), Data.EffectSpec.StackCount);
	}
	if (Data.EvaluatedData.Attribute == GetFireBallDamageAttribute())
	{
		SetFireBallDamage(FMath::Clamp(GetFireBallDamage(), 0.0f, 1000.0f));
		FireBallDamageDelegate.Broadcast(GetFireBallDamage(), Data.EffectSpec.StackCount);
	}
	if (Data.EvaluatedData.Attribute == GetFireRingDamageAttribute())
	{
		SetFireRingDamage(FMath::Clamp(GetFireRingDamage(), 0.0f, 1000.0f));
		FireRingDamageDelegate.Broadcast(GetFireRingDamage(), Data.EffectSpec.StackCount);
	}
	if (Data.EvaluatedData.Attribute == GetIceBallDamageAttribute())
	{
		SetIceBallDamage(FMath::Clamp(GetIceBallDamage(), 0.0f, 1000.0f));
		IceBallDamageDelegate.Broadcast(GetIceBallDamage(), Data.EffectSpec.StackCount);
	}
	if (Data.EvaluatedData.Attribute == GetFrozenHealAttribute())
	{
		SetFrozenHeal(FMath::Clamp(GetFrozenHeal(), 0.0f, 1000.0f));
		FrozenHealDelegate.Broadcast(GetFrozenHeal(), Data.EffectSpec.StackCount);
	}
}

void UGASProjectAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	DOREPLIFETIME_CONDITION_NOTIFY(UGASProjectAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASProjectAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASProjectAttributeSet, MoveSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASProjectAttributeSet, MoveSpeedMultiplier, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASProjectAttributeSet, FireBallDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASProjectAttributeSet, FireRingDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASProjectAttributeSet, IceBallDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASProjectAttributeSet, FrozenHeal, COND_None, REPNOTIFY_Always);
}

void UGASProjectAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASProjectAttributeSet, Health, OldHealth);
}
void UGASProjectAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASProjectAttributeSet, MaxHealth, OldMaxHealth);
}
void UGASProjectAttributeSet::OnRep_MoveSpeed(const FGameplayAttributeData& OldMoveSpeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASProjectAttributeSet, MoveSpeed, OldMoveSpeed);
}
void UGASProjectAttributeSet::OnRep_MoveSpeedMultiplier(const FGameplayAttributeData& OldMoveSpeedMultiplier)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASProjectAttributeSet, MoveSpeedMultiplier, OldMoveSpeedMultiplier);
}
void UGASProjectAttributeSet::OnRep_FireBallDamage(const FGameplayAttributeData& OldFireBallDamage)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASProjectAttributeSet, FireBallDamage, OldFireBallDamage);
}
void UGASProjectAttributeSet::OnRep_FireRingDamage(const FGameplayAttributeData& OldFireRingDamage)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASProjectAttributeSet, FireRingDamage, OldFireRingDamage);
}
void UGASProjectAttributeSet::OnRep_IceBallDamage(const FGameplayAttributeData& OldIceBallDamage)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASProjectAttributeSet, IceBallDamage, OldIceBallDamage);
}
void UGASProjectAttributeSet::OnRep_FrozenHeal(const FGameplayAttributeData& OldFrozenHeal)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASProjectAttributeSet, FrozenHeal, OldFrozenHeal);
}
