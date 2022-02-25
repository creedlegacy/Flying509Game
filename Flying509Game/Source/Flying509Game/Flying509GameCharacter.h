// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Runtime/Engine/Classes/Components/TimelineComponent.h"
#include "Flying509GameCharacter.generated.h"


UCLASS(config=Game)
class AFlying509GameCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	class UTimelineComponent* DiveTimeline;
	class UTimelineComponent* CatchTimeline;
public:
	AFlying509GameCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UPROPERTY(EditAnywhere, Category = "Shooting");
	TSubclassOf<class ABullet> BulletBP;

	UPROPERTY(EditAnywhere, Category = Flying);
	float MaxPitchLimit;
	UPROPERTY(EditAnywhere, Category = Flying);
	float MinPitchLimit;
	UPROPERTY(EditAnywhere, Category = Flying);
	float YawTurnScale;
	UPROPERTY(EditAnywhere, Category = Flying);
	float BoostFlightSpeed;
	UPROPERTY(EditAnywhere, Category = Flying);
	float NormalFlightSpeed;
	UPROPERTY(VisibleAnywhere, Category = Flying);
	bool IsDiving = false;
	//UPROPERTY(VisibleAnywhere, Category = Flying);
	//bool IsForward = true;

	UPROPERTY(EditAnywhere, Category = "Timeline");
	class UCurveFloat* diveCurve;
	UPROPERTY(EditAnywhere, Category = "Timeline");
	class UCurveFloat* catchCurve;

	FOnTimelineFloat DiveInterpFunction{};
	FOnTimelineFloat CatchInterpFunction{};

	FOnTimelineEvent TimelineFinished{};

	UFUNCTION()
		void DiveTimelineFloatReturn(float value);
	UFUNCTION()
		void DiveCatchTimelineFloatReturn(float value);
	UFUNCTION()
		void OnTimelineFinished();



	FRotator defaultCameraRotation;
	FVector defaultCameraLocation;


protected:
	virtual void BeginPlay() override;

	void Shoot();

	void PitchMovement(float Value);
	void YawMovement(float Value);

	void ForwardFlight();

	void Boost();
	void StopBoost();

	void Dive();
	void DiveCatch();

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

