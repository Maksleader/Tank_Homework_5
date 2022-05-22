// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCannon.h"
#include "DrawDebugHelpers.h"
#include "FireTrace.generated.h"

/**
 * 
 */
UCLASS()
class TANK_HOMEWORK_5_API AFireTrace : public ABaseCannon
{
	GENERATED_BODY()

public:
	virtual void Fire() override;

};