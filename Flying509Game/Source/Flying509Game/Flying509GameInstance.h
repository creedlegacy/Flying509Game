// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Flying509GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class FLYING509GAME_API UFlying509GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	int SolarFlaresTotal = 0;
	
};
