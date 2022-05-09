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

	/** Timeline component used for diving */
	class UTimelineComponent* DiveTimeline;
	/** Timeline component used for dive catch */
	class UTimelineComponent* CatchTimeline;


	/** Time to transition camera distance when boosting, used for lerping */
	float CameraBoostOutDuration = 0;
	/** Time used to compare with boost out duration to see how much time have elapsed, used for lerping */
	float CameraBoostOutTimeElapsed = 0;

	/** Time to transition camera distance from boost to normal, used for lerping */
	float CameraBoostInDuration = 0;
	/** Time used to compare with boost in duration to see how much time have elapsed, used for lerping */
	float CameraBoostInTimeElapsed = 0;

	/** Time to transition camera distance when diving, used for lerping */
	float CameraDiveOutDuration = 0;
	/** Time used to compare with dive out duration to see how much time have elapsed, used for lerping */
	float CameraDiveOutTimeElapsed = 0;

	/** Time to transition camera distance when diving to normal, used for lerping */
	float CameraDiveInDuration = 0;
	/** Time used to compare with dive in duration to see how much time have elapsed, used for lerping */
	float CameraDiveInTimeElapsed = 0;


	/** variables for cameraboom arm length */
	float DefaultCameraBoom;
	float CurrentCameraBoom;

	/** variables for FOV manipulation */
	float DefaultFOV;
	float CurrentFOV;

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

	/*UPROPERTY(EditAnywhere, Category = "Shooting");
	TSubclassOf<class ABullet> BulletBP;*/


	/** Maximum limit of pitch rotation for the character (Maximum rotation of character facing vertically up) */
	UPROPERTY(EditAnywhere, Category = Flying);
	float MaxPitchLimit;

	/** Minimum limit of pitch rotation for the character (Minium rotation of character facing vertically down)*/
	UPROPERTY(EditAnywhere, Category = Flying);
	float MinPitchLimit;

	/** Maximum limit of roll rotation for the character (Barrel Roll)*/
	UPROPERTY(EditAnywhere, Category = Flying);
	float MaxRollLimit;

	/** Minimum limit of roll rotation for the character (Barrel Roll)*/
	UPROPERTY(EditAnywhere, Category = Flying);
	float MinRollLimit;

	/** Scale multiplier of yaw rotation movement (Higher means yaw rotation is faster)*/
	UPROPERTY(EditAnywhere, Category = Flying);
	float YawTurnScale;

	/** Flight speed set when the boost button is held */
	UPROPERTY(EditAnywhere, Category = Flying);
	float BoostFlightSpeed;

	/** Flight speed set when no button is held */
	UPROPERTY(EditAnywhere, Category = Flying);
	float NormalFlightSpeed;

	/** Used as the value to decrement the flight speed per tick after diving to return to normal speeds */
	UPROPERTY(EditAnywhere, Category = Flying);
	float SpeedDecrementAdjuster = 1.6;

	/** Is player diving */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Flying);
	bool IsDiving = false;

	/** Is player boosting */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Flying);
	bool IsBoosting = false;

	/** Boolean to detech if gamepad is being used or not */
	bool IsGamepad = false;

	/** Velocity when the character is diving/falling on the z axis, used to multiply flight speed after dive catching */
	float MaxZVelocity = 1;

	/** Boolean to tell when the player is still on the speed reached from diving and catching himself */
	bool OnDiveCatchSpeed = false;

	/** Is player in freecam mode/button held */
	bool IsFreeCam = false;

	/** Saves current camera rotation to return to after free cam is turned off */
	FRotator CurrentCameraRotate = FRotator(0);

	/** Boolean to tell whether guide is activated or not */
	UPROPERTY(BlueprintReadWrite);
	bool ShowGuide = false;



	/** Curve to be used with dive timeline */
	UPROPERTY(EditAnywhere, Category = "Timeline");
	class UCurveFloat* diveCurve;

	/** Curve to be used with dive catch timeline */
	UPROPERTY(EditAnywhere, Category = "Timeline");
	class UCurveFloat* catchCurve;

	/** Declare delegate function to be binded with DiveTimelineFloatReturn() */
	FOnTimelineFloat DiveInterpFunction{};
	/** Declare delegate function to be binded with DiveCatchTimelineFloatReturn() */
	FOnTimelineFloat CatchInterpFunction{};

	/** Do lerp according to timeline, alter camera and actor rotation into dive position (transition effect) */
	UFUNCTION()
		void DiveTimelineFloatReturn(float value);
	/** Do lerp according to timeline, alter camera and actor rotation into dive catch position (transition effect) */
	UFUNCTION()
		void DiveCatchTimelineFloatReturn(float value);
	
	/** Used to adjust controller's control rotation (mouse position), used mostly in dive and catch lerp transition */
	FRotator CurrentControlRotation;
	/** Used to adjust the current actor's rotation, used mostly in dive and catch lerp transition */
	FRotator CurrentActorRotation;



	/** New dynamic material instance for the wings to be changed in game */
	class UMaterialInstanceDynamic* WingsDynamicMaterial;

	float WingGlowIntensity = 0;

	/** Updates designated dynamic material on game time */
	void UpdateDynamicMaterial(); 

protected:
	virtual void BeginPlay() override;

	/*void Shoot();*/

	/** Manages pitch movement of player */
	void PitchMovement(float Value);

	/** Manages yaw movement of player, mouse keyboard */
	void YawMovement(float Value);
	/** Manages yaw movement of player, gamepad */
	void YawMovementGamepad(float Value);

	/** Manages roll movement of player */
	void RollMovement(float Value);

	/** Continuous forward flight if nothing is pressed */
	void ForwardFlight();

	/** Set MaxZVelocity according to z axis fall velocity, to be used to multiply flight speed after dive catch */
	void FallVelocityTick();

	/** Boost player, duh */
	void Boost();
	/** Stop Boosting player, duh */
	void StopBoost();

	/** Lerp camera arm distance and FOV to create transition effect when boosting */
	void BoostLerpOut(float DeltaTime);
	/** Lerp to normal after boost */
	void BoostLerpIn(float DeltaTime);

	/** Do Dive, duh */
	void Dive();
	/** Action after dive button is let go, catching the players after dive */
	void DiveCatch();
	/** Adjust the flight speed after dive catching to return it slowly to normal speeds by tick */
	void DiveCatchSpeedAdjustment();
	/** Lerp camera arm distance and FOV to create transition effect when diving */
	void DiveLerpOut(float DeltaTime);
	/** Lerp to normal after dive */
	void DiveLerpIn(float DeltaTime);

	/** Show guide beam thing for collectibles */
	void Guide();

	/** Set camera to be freely rotateable on mouse keyboard (not flying according to mouse position) */
	void FreeCamera();

	/** Change inputs */
	void SetMouse(float Value);
	void SetGamepad(float Value);

	/** Creates dynamic instance material to be updated in game */
	void CreateDynamicMaterial();


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

	void LookUp(float Value);

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

