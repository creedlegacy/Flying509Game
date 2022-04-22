// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectible.h"
#include "Components/BoxComponent.h"
#include "Flying509GameInstance.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

#define PrintString(String) GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Red,String)

// Sets default values
ACollectible::ACollectible()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	RootComponent = BoxComponent;

	
	
	



}

// Called when the game starts or when spawned
void ACollectible::BeginPlay()
{
	Super::BeginPlay();
	GameInstance = Cast<UFlying509GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ACollectible::OnOverlap);
	
	
	
}

// Called every frame
void ACollectible::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	
}

void ACollectible::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr)) {
		if (GameInstance) {
			GameInstance->SolarFlaresTotal += 1;
			PrintString(FString::Printf(TEXT("%d"), GameInstance->SolarFlaresTotal));
		}

		Destroy();
	}

}

