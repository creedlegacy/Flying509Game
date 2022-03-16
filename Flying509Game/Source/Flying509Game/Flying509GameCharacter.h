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

	bool IsGamepad = false;

	UPROPERTY(EditAnywhere, Category = Flying);
	float MaxPitchLimit;
	UPROPERTY(EditAnywhere, Category = Flying);
	float MinPitchLimit;
	UPROPERTY(EditAnywhere, Category = Flying);
	float MaxRollLimit;
	UPROPERTY(EditAnywhere, Category = Flying);
	float MinRollLimit;
	UPROPERTY(EditAnywhere, Category = Flying);
	float YawTurnScale;
	UPROPERTY(EditAnywhere, Category = Flying);
	float BoostFlightSpeed;
	UPROPERTY(EditAnywhere, Category = Flying);
	float NormalFlightSpeed;


	bool IsDiving = false;
	bool IsBoosting = false;
	bool IsFreeCam = false;

	// Velocity when the character is diving/falling
	float MaxZVelocity = 1;
	// Boolean to tell when the player is still on the speed reached from diving and catching himself
	bool OnDiveCatchSpeed = false;

	FRotator CurrentCameraRotate = FRotator(0);

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

	//variables for cameraboom arm length
	float DefaultCameraBoom;
	float CurrentCameraBoom;

	float CameraBoostOutDuration = 0;
	float CameraBoostOutTimeElapsed = 0;

	float CameraBoostInDuration = 0;
	float CameraBoostInTimeElapsed = 0;

	float CameraDiveOutDuration = 0;
	float CameraDiveOutTimeElapsed = 0;

	float CameraDiveInDuration = 0;
	float CameraDiveInTimeElapsed = 0;

protected:
	virtual void BeginPlay() override;

	void Shoot();

	void PitchMovement(float Value);
	void YawMovement(float Value);
	void YawMovementGamepad(float Value);
	void RollMovement(float Value);

	void ForwardFlight();

	void FallVelocityTick();

	void Boost();
	void StopBoost();
	void BoostLerpOut(float DeltaTime);
	void BoostLerpIn(float DeltaTime);

	void Dive();
	void DiveCatch();
	void DiveCatchSpeedAdjustment();
	void DiveLerpOut(float DeltaTime);
	void DiveLerpIn(float DeltaTime);

	void FreeCamera();

	void SetMouse(float Value);
	void SetGamepad(float Value);


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

