// Fill out your copyright notice in the Description page of Project Settings.


#include "GASCharacter.h"
#include "GASAbilitySystemComponent.h"
#include "GASProjectAttributeSet.h"
#include "..\Public\GASCharacter.h"

// Sets default values
AGASCharacter::AGASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UGASAbilitySystemComponent>("AbilitySystemComp");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	Attributes = CreateDefaultSubobject<UGASProjectAttributeSet>("Attributes");

}

UAbilitySystemComponent* AGASCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}


void AGASCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (AbilitySystemComponent)
		AbilitySystemComponent->InitAbilityActorInfo(this, this);

	InitializeAttributes();
	GiveDefaultAbilities();
}

void AGASCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	if (AbilitySystemComponent)
		AbilitySystemComponent->InitAbilityActorInfo(this, this);

	InitializeAttributes();
}

void AGASCharacter::InitializeAttributes()
{
	if (AbilitySystemComponent && DefaultAttributeEffect)
	{
		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(this);
		FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributeEffect, 1, EffectContext);

		if (SpecHandle.IsValid())
			FActiveGameplayEffectHandle GEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}
}

void AGASCharacter::GiveDefaultAbilities()
{
	if (HasAuthority() && AbilitySystemComponent)
		for (TSubclassOf<UGameplayAbility>& StartupAbility : DefaultAbilities)
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(StartupAbility.GetDefaultObject(), 1, 0));
}

// Called when the game starts or when spawned
void AGASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (AbilitySystemComponent)
	{
		if (AbilitySystemComponent->DefaultStartingData.Num() > 0 && AbilitySystemComponent->DefaultStartingData[0].Attributes != NULL && AbilitySystemComponent->DefaultStartingData[0].DefaultStartingTable != NULL)
		{
			//Link Attribute Set to Ability System Component
			Attributes = AbilitySystemComponent->GetSet<UGASProjectAttributeSet>();

			//Bindings for Attribute Change Delegates
			const_cast<UGASProjectAttributeSet*>(Attributes)->HealthChangeDelegate.AddDynamic(this, &AGASCharacter::OnHealthChangedNative);
			const_cast<UGASProjectAttributeSet*>(Attributes)->MAxHealthChangeDelegate.AddDynamic(this, &AGASCharacter::OnMaxHealthChangedNative);
			const_cast<UGASProjectAttributeSet*>(Attributes)->MoveSpeedChangeDelegate.AddDynamic(this, &AGASCharacter::OnMoveSpeedChangedNative);
			const_cast<UGASProjectAttributeSet*>(Attributes)->MoveSpeedMultiplierDelegate.AddDynamic(this, &AGASCharacter::OnMoveSpeedMultiplierChangedNative);
			const_cast<UGASProjectAttributeSet*>(Attributes)->FireBallDamageDelegate.AddDynamic(this, &AGASCharacter::OnFireBallDamageChangedNative);
			const_cast<UGASProjectAttributeSet*>(Attributes)->FireRingDamageDelegate.AddDynamic(this, &AGASCharacter::OnFireRingDamageChangedNative);
			const_cast<UGASProjectAttributeSet*>(Attributes)->IceBallDamageDelegate.AddDynamic(this, &AGASCharacter::OnIceBallDamageChangedNative);
			const_cast<UGASProjectAttributeSet*>(Attributes)->FrozenHealDelegate.AddDynamic(this, &AGASCharacter::OnFrozenHealChangedNative);

		}
	}
}

// Called every frame
void AGASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

//*****Events On Attribute Change*****
void AGASCharacter::OnHealthChangedNative(float Health, int32 StackCount)
{
	OnHealthChange(Health, StackCount);
}

void AGASCharacter::OnMaxHealthChangedNative(float MaxHealth, int32 StackCount)
{
	OnHealthChange(MaxHealth, StackCount);
}

void AGASCharacter::OnMoveSpeedChangedNative(float MoveSpeed, int32 StackCount)
{
	OnMoveSpeedChange(MoveSpeed, StackCount);
}

void AGASCharacter::OnMoveSpeedMultiplierChangedNative(float MoveSpeedMultiplier, int32 StackCount)
{
	OnMoveSpeedMultiplierChange(MoveSpeedMultiplier, StackCount);
}

void AGASCharacter::OnFireBallDamageChangedNative(float FireBallDamage, int32 StackCount)
{
	OnFireBallDamageChange(FireBallDamage, StackCount);
}

void AGASCharacter::OnFireRingDamageChangedNative(float FireRingDamage, int32 StackCount)
{
	OnFireRingDamageChange(FireRingDamage, StackCount);
}

void AGASCharacter::OnIceBallDamageChangedNative(float IceBallDamage, int32 StackCount)
{
	OnIceBallDamageChange(IceBallDamage, StackCount);
}

void AGASCharacter::OnFrozenHealChangedNative(float FrozenHeal, int32 StackCount)
{
	OnFrozenHealChange(FrozenHeal, StackCount);
}

//*****Getting*****
void AGASCharacter::GetHealthValue(float& Health)
{
	if (Attributes)
	{
		Health = Attributes->GetHealth();
	}
}

void AGASCharacter::GetMaxHealthValue(float& MaxHealth)
{
	if (Attributes)
	{
		MaxHealth = Attributes->GetMaxHealth();
	}
}

void AGASCharacter::GetMoveSpeedValue(float& MoveSpeed)
{
	if (Attributes)
	{
		MoveSpeed = Attributes->GetMoveSpeed();
	}
}

void AGASCharacter::GetMoveSpeedMultiplierValue(float& MoveSpeedMultiplier)
{
	if (Attributes)
	{
		MoveSpeedMultiplier = Attributes->GetMoveSpeedMultiplier();
	}
}

void AGASCharacter::GetFireBallDamageValue(float& FireBallDamage)
{
	if (Attributes)
	{
		FireBallDamage = Attributes->GetFireBallDamage();
	}
}

void AGASCharacter::GetFireRingDamageValue(float& FireRingDamage)
{
	if (Attributes)
	{
		FireRingDamage = Attributes->GetFireRingDamage();
	}
}

void AGASCharacter::GetIceBallDamageValue(float& IceBallDamage)
{
	if (Attributes)
	{
		IceBallDamage = Attributes->GetIceBallDamage();
	}
}

void AGASCharacter::GetFrozenHealValue(float& FrozenHeal)
{
	if (Attributes)
	{
		FrozenHeal = Attributes->GetFrozenHeal();
	}
}

//*****Setting*****
void AGASCharacter::SetHealthValues(float NewHealth, float NewMaxHealth)
{
	if (Attributes)
	{
		AbilitySystemComponent->ApplyModToAttribute(Attributes->GetHealthAttribute(), EGameplayModOp::Override, NewHealth);
		AbilitySystemComponent->ApplyModToAttribute(Attributes->GetMaxHealthAttribute(), EGameplayModOp::Override, NewMaxHealth);
	}
}

void AGASCharacter::SetMoveSpeedValue(float NewMoveSpeed)
{
	if (Attributes)
	{
		AbilitySystemComponent->ApplyModToAttribute(Attributes->GetMoveSpeedAttribute(), EGameplayModOp::Override, NewMoveSpeed);
	}
}

void AGASCharacter::SetMoveSpeedMultiplierValue(float NewMoveSpeedMultiplier)
{
	if (Attributes)
	{
		AbilitySystemComponent->ApplyModToAttribute(Attributes->GetMoveSpeedMultiplierAttribute(), EGameplayModOp::Override, NewMoveSpeedMultiplier);
	}
}

void AGASCharacter::SetFireBallDamageValues(float NewFireBallDamage)
{
	if (Attributes)
	{
		AbilitySystemComponent->ApplyModToAttribute(Attributes->GetFireBallDamageAttribute(), EGameplayModOp::Override, NewFireBallDamage);
	}
}

void AGASCharacter::SetFireRingDamageValues(float NewFireRingDamage)
{
	if (Attributes)
	{
		AbilitySystemComponent->ApplyModToAttribute(Attributes->GetFireRingDamageAttribute(), EGameplayModOp::Override, NewFireRingDamage);
	}
}

void AGASCharacter::SetIceBallDamageValues(float NewIceBallDamage)
{
	if (Attributes)
	{
		AbilitySystemComponent->ApplyModToAttribute(Attributes->GetIceBallDamageAttribute(), EGameplayModOp::Override, NewIceBallDamage);
	}
}

void AGASCharacter::SetFrozenHealValues(float NewFrozenHeal)
{
	if (Attributes)
	{
		AbilitySystemComponent->ApplyModToAttribute(Attributes->GetFrozenHealAttribute(), EGameplayModOp::Override, NewFrozenHeal);
	}
}

