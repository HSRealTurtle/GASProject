// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GASAbilitySystemComponent.h"
#include "GASProjectAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

struct FGameplayEffectModCallbackData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAttrChangeDelegate, float, Attr, int32, StackcCount);

UCLASS()
class GASPROJECT_API UGASProjectAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:

	UGASProjectAttributeSet();
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	//*****Identifing Attributes*****
	
	//Attribute for Health
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UGASProjectAttributeSet, Health)

	//Attribute for MaxHealth
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UGASProjectAttributeSet, MaxHealth)

	//Attribute for MoveSpeed
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MoveSpeed;
	ATTRIBUTE_ACCESSORS(UGASProjectAttributeSet, MoveSpeed)

	//Attribute for MoveSpeedMultiplier
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MoveSpeedMultiplier;
	ATTRIBUTE_ACCESSORS(UGASProjectAttributeSet, MoveSpeedMultiplier)

	//Attribute for FireDamage
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData FireDamage;
	ATTRIBUTE_ACCESSORS(UGASProjectAttributeSet, FireDamage)

	//Attribute for IceDamage
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData IceDamage;
	ATTRIBUTE_ACCESSORS(UGASProjectAttributeSet, IceDamage)

	//*****Delegates for attribute changes*****
	FAttrChangeDelegate HealthChangeDelegate;
	FAttrChangeDelegate MAxHealthChangeDelegate;
	FAttrChangeDelegate MoveSpeedChangeDelegate;
	FAttrChangeDelegate MoveSpeedMultiplierDelegate;
	FAttrChangeDelegate FireDamageDelegate;
	FAttrChangeDelegate IceDamageDelegate;

	//*****Replication Functions for Attributes*****
	UFUNCTION()
		virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);
	UFUNCTION()
		virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);
	UFUNCTION()
		virtual void OnRep_MoveSpeed(const FGameplayAttributeData& OldMoveSpeed);
	UFUNCTION()
		virtual void OnRep_MoveSpeedMultiplier(const FGameplayAttributeData& OldMoveSpeedMultiplier);
	UFUNCTION()
		virtual void OnRep_FireDamage(const FGameplayAttributeData& OldFireDamage);
	UFUNCTION()
		virtual void OnRep_IceDamage(const FGameplayAttributeData& OldIceDamage);
};
