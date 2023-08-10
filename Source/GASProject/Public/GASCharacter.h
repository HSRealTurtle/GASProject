// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayTagContainer.h"
#include "GameplayEffectTypes.h"
#include "AbilitySystemInterface.h"
#include "GasProjectAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GASCharacter.generated.h"

class UGASAbilitySystemComponent;
class UGASAttributeSet;

UCLASS()
class GASPROJECT_API AGASCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGASCharacter();
	
	//overriden from IAbilitySystemInterface
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributies")
	//int MaxHealth = 100;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	virtual void InitializeAttributes();
	virtual void GiveDefaultAbilities();

	//Add Ability System Component to Character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities", meta = (AlowPrivateAccess = "true"))
	class UGASAbilitySystemComponent* AbilitySystemComponent;

	//Add Attribute Set to Character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities", meta = (AlowPrivateAccess = "true"))
	const class UGASProjectAttributeSet* Attributes;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Abilities")
	TSubclassOf<class UGameplayEffect> DefaultAttributeEffect;

	//Add Variable for Initial Abilities
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Abilities")
	TArray<TSubclassOf<class UGameplayAbility>> DefaultAbilities;

	//*****Functions for Attribute Change Delagates*****
	UFUNCTION()
	void OnHealthChangedNative(float Health, int32 StackCount);
	UFUNCTION()
	void OnMaxHealthChangedNative(float MaxHealth, int32 StackCount);
	UFUNCTION()
	void OnMoveSpeedChangedNative(float MoveSpeed, int32 StackCount);
	UFUNCTION()
	void OnMoveSpeedMultiplierChangedNative(float MoveSpeedMultiplier, int32 StackCount);
	UFUNCTION()
	void OnFireBallDamageChangedNative(float FireBallDamage, int32 StackCount);
	UFUNCTION()
	void OnFireRingDamageChangedNative(float FireRingDamage, int32 StackCount);
	UFUNCTION()
	void OnIceBallDamageChangedNative(float IceBallDamage, int32 StackCount);
	UFUNCTION()
	void OnFrozenHealChangedNative(float FrozenHeal, int32 StackCount);

	//******Event that bind to native events********
	
	//Event Trigger On Health Change
	UFUNCTION(BlueprintImplementableEvent, Category = "Abilities")
	void OnHealthChange(float Health, int32 StackCount);

	//Event Trigger On MoveSpeed
	UFUNCTION(BlueprintImplementableEvent, Category = "Abilities")
	void OnMoveSpeedChange(float MoveSpeed, int32 StackCount);

	//Event Trigger On MoveSpeedMultiplier
	UFUNCTION(BlueprintImplementableEvent, Category = "Abilities")
	void OnMoveSpeedMultiplierChange(float MoveSpeedMultiplier, int32 StackCount);

	//Event Trigger On FireBallDamage Change
	UFUNCTION(BlueprintImplementableEvent, Category = "Abilities")
	void OnFireBallDamageChange(float FireBallDamage, int32 StackCount);

	//Event Trigger On FireRingDamage Change
	UFUNCTION(BlueprintImplementableEvent, Category = "Abilities")
	void OnFireRingDamageChange(float FireRingDamage, int32 StackCount);

	//Event Trigger On IceBallDamage Change
	UFUNCTION(BlueprintImplementableEvent, Category = "Abilities")
	void OnIceBallDamageChange(float IceBallDamage, int32 StackCount);

	//Event Trigger On FrozenHeal Change
	UFUNCTION(BlueprintImplementableEvent, Category = "Abilities")
	void OnFrozenHealChange(float FrozenHeal, int32 StackCount);

	//*******Ability Values Getter Functions**********

	//Getter for Health Value
	UFUNCTION(BlueprintPure, Category = "Abilities")
	void GetHealthValue(float& Health);
	//Getter for MaxHealth Value
	UFUNCTION(BlueprintPure, Category = "Abilities")
	void GetMaxHealthValue(float& MaxHealth);
	//Getter for MoveSpeed Value
	UFUNCTION(BlueprintPure, Category = "Abilities")
	void GetMoveSpeedValue(float& MoveSpeed);
	//Getter for MoveSpeedMultiplier Value
	UFUNCTION(BlueprintPure, Category = "Abilities")
	void GetMoveSpeedMultiplierValue(float& MoveSpeedMultiplier);
	//Getter for FireBallDamage Value
	UFUNCTION(BlueprintPure, Category = "Abilities")
	void GetFireBallDamageValue(float& FireBallDamage);
	//Getter for FireRingDamage Value
	UFUNCTION(BlueprintPure, Category = "Abilities")
	void GetFireRingDamageValue(float& FireRingDamage);
	//Getter for IceBallDamage Value
	UFUNCTION(BlueprintPure, Category = "Abilities")
	void GetIceBallDamageValue(float& IceBallDamage);
	//Getter for FrozenHeal Value
	UFUNCTION(BlueprintPure, Category = "Abilities")
	void GetFrozenHealValue(float& FrozenHeal);

	//*******Ability Values Setter Functions**********

	//Setter for Health Values
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void SetHealthValues(float NewHealth, float NewMaxHealth);
	//Setter for MoveSpeed Values
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void SetMoveSpeedValue(float NewMoveSpeed);
	//Setter for MoveSpeedMultiplier Values
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void SetMoveSpeedMultiplierValue(float NewMoveSpeedMultiplier);
	//Setter for FireBallDamage Values
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void SetFireBallDamageValues(float NewFireBallDamage);
	//Setter for FireRingDamage Values
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void SetFireRingDamageValues(float NewFireRingDamage);
	//Setter for IceDamage Values
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void SetIceBallDamageValues(float NewIceBallDamage);
	//Setter for FrozenHeal Values
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void SetFrozenHealValues(float NewFrozenHeal);
};
