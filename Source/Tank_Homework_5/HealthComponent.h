// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageTaker.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANK_HOMEWORK_5_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

	DECLARE_EVENT(UHealthComponent, FDieEvent);
	DECLARE_EVENT_OneParam(UHealthComponent, FHealthChanged, float);
	DECLARE_EVENT_OneParam(UHealthComponent,FEnemyKilled,float)

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	void Damage(FDAMAGEDATA DamageData );
	void AddScore(FDAMAGEDATA DamageData);

	float GetHealth() const
	{
		return CurrentHealth;
	}

	float GetDeathPoint() const
	{
		return DeathPoint;
	}


	FDieEvent OnDeath;
	FHealthChanged OnHealthChanged;
	FEnemyKilled Killed;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float MaxHealth = 10;

	
		float CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DeathPoint = 5;

	float Score = 0;



		
};
