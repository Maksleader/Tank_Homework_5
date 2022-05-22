// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "BasePawn.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	
	// ...
}

void UHealthComponent::Damage(FDAMAGEDATA DamageData)
{
	float PrevValue = CurrentHealth;

	CurrentHealth -= DamageData.DamageValue;
	if(CurrentHealth<0)
	{
		CurrentHealth = 0;
	}

	if(!FMath::IsNearlyEqual(PrevValue,CurrentHealth))
	{
		if(OnHealthChanged.IsBound())
		{
			OnHealthChanged.Broadcast(CurrentHealth);
		}
	}


	if(FMath::IsNearlyZero(CurrentHealth))
	{
		
		if(OnDeath.IsBound())
		{
			OnDeath.Broadcast(); 
		}

	}

	
}

void UHealthComponent::AddScore(FDAMAGEDATA DamageData)
{
	auto enemy = Cast<ABasePawn>(DamageData.DamageTaker);

	if (FMath::IsNearlyZero(enemy->HealthComponent->GetHealth()))
	{
		Score += DamageData.Point;
		if (Killed.IsBound())
		{
			Killed.Broadcast(Score);
		}
	}
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
	
}



