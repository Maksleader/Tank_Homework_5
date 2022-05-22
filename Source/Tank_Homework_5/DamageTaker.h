// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DamageTaker.generated.h"

// This class does not need to be modified.

USTRUCT(BlueprintType)
struct FDAMAGEDATA
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DamageValue=0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Point = 0;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* DamageMaker=nullptr;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AActor* DamageTaker=nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AActor* Instigator = nullptr;


};
UINTERFACE(MinimalAPI)
class UDamageTaker : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TANK_HOMEWORK_5_API IDamageTaker
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void TakeDamage(FDAMAGEDATA DamageData)=0;
};
