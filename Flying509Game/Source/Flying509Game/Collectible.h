// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Flying509GameInstance.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Collectible.generated.h"


UCLASS()
class FLYING509GAME_API ACollectible : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACollectible();

	/*UPROPERTY(EditAnywhere, Category = "Components");
	class UStaticMeshComponent* CollectibleMesh;*/

	UPROPERTY(EditAnywhere, Category = "Components");
	class UParticleSystemComponent* CollectibleParticle;

	UPROPERTY(EditAnywhere, Category = "Components");
	class USphereComponent* SphereComponent;

	UFlying509GameInstance* GameInstance;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
