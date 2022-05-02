// Copyright Epic Games, Inc. All Rights Reserved.

#include "Flying509GameCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Runtime/Engine/Classes/Components/TimelineComponent.h"
#include "Bullet.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

//////////////////////////////////////////////////////////////////////////
// AFlying509GameCharacter

AFlying509GameCharacter::AFlying509GameCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 35.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;
	GetCharacterMovement()->MaxFlySpeed = NormalFlightSpeed;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	DefaultCameraBoom = CameraBoom->TargetArmLength; // Assign default arm length to this variable
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	DefaultFOV = FollowCamera->FieldOfView; // Assign default FOV to this variable


	DiveTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("DiveTimeline"));
	CatchTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("CatchTimeline"));
	DiveInterpFunction.BindUFunction(this, FName("DiveTimelineFloatReturn"));
	CatchInterpFunction.BindUFunction(this, FName("DiveCatchTimelineFloatReturn"));
	TimelineFinished.BindUFunction(this, FName("OnTimelineFinished")); 

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AFlying509GameCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	/*PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AFlying509GameCharacter::Shoot);*/

	PlayerInputComponent->BindAction("Boost", IE_Pressed, this, &AFlying509GameCharacter::Boost);
	PlayerInputComponent->BindAction("Boost", IE_Released, this, &AFlying509GameCharacter::StopBoost);

	PlayerInputComponent->BindAction("Dive", IE_Pressed, this, &AFlying509GameCharacter::Dive);
	PlayerInputComponent->BindAction("Dive", IE_Released, this, &AFlying509GameCharacter::DiveCatch);

	PlayerInputComponent->BindAction("Guide", IE_Pressed, this, &AFlying509GameCharacter::GuideOn);
	PlayerInputComponent->BindAction("Guide", IE_Released, this, &AFlying509GameCharacter::GuideOff);

	PlayerInputComponent->BindAction("FreeCamera", IE_Pressed, this, &AFlying509GameCharacter::FreeCamera);
	PlayerInputComponent->BindAction("FreeCamera", IE_Released, this, &AFlying509GameCharacter::FreeCamera);

	PlayerInputComponent->BindAxis("Gamepad", this, &AFlying509GameCharacter::SetGamepad);
	PlayerInputComponent->BindAxis("Mouse", this, &AFlying509GameCharacter::SetMouse);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	//PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Pitch", this, &AFlying509GameCharacter::PitchMovement);
	/*PlayerInputComponent->BindAxis("Yaw", this, &AFlying509GameCharacter::MoveRight);*/
	/*PlayerInputComponent->BindAxis("Roll", this, &AFlying509GameCharacter::RollMovement);*/
	PlayerInputComponent->BindAxis("Turn", this, &AFlying509GameCharacter::YawMovement);
	PlayerInputComponent->BindAxis("TurnGamepad", this, &AFlying509GameCharacter::YawMovementGamepad);
	PlayerInputComponent->BindAxis("TurnRate", this, &AFlying509GameCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &AFlying509GameCharacter::LookUp);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AFlying509GameCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AFlying509GameCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AFlying509GameCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AFlying509GameCharacter::OnResetVR);
}


void AFlying509GameCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	//Check if curve asset is valid
	if (diveCurve && catchCurve) {
		//Add the float curve to the timeline and connect it to the interpfunction's delegate 
		DiveTimeline->AddInterpFloat(diveCurve,DiveInterpFunction,FName("Alpha"));
		CatchTimeline->AddInterpFloat(catchCurve, CatchInterpFunction, FName("Alpha"));
		//Add our timeline finished function
		DiveTimeline->SetTimelineFinishedFunc(TimelineFinished);

		//Timeline settings
		DiveTimeline->SetLooping(false);
		DiveTimeline->SetIgnoreTimeDilation(true);
		CatchTimeline->SetLooping(false);
		CatchTimeline->SetIgnoreTimeDilation(true);
	}
	GetCharacterMovement()->MaxFlySpeed = NormalFlightSpeed;
}

// Called every frame
void AFlying509GameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	BoostLerpOut(DeltaTime);
	BoostLerpIn(DeltaTime);
	ForwardFlight();
	FallVelocityTick();
	DiveCatchSpeedAdjustment();
	DiveLerpOut(DeltaTime);
	DiveLerpIn(DeltaTime);

}

void AFlying509GameCharacter::SetMouse(float Value)
{
	//to detect if using mouse keyboard
	if ((Value < -0.1 || Value > 0.1) && IsGamepad) {
		IsGamepad = false;
	}
	
}

void AFlying509GameCharacter::SetGamepad(float Value)
{
	//to detect is using controllers
	if ((Value < -0.1 || Value > 0.1) && !IsGamepad) {
		IsGamepad = true;
	}
	
}

void AFlying509GameCharacter::Shoot()
{
	UE_LOG(LogTemp, Warning, TEXT("SHOOSTED"));
	FTransform SpawnTransform = GetActorTransform();
	SpawnTransform.SetLocation(FollowCamera->GetComponentRotation().Vector() * 200.f + GetActorLocation());
	FActorSpawnParameters SpawnParameters;
	GetWorld()->SpawnActor<ABullet>(BulletBP, SpawnTransform, SpawnParameters);
}


void AFlying509GameCharacter::PitchMovement(float Value)
{
	
	if (!UGameplayStatics::IsGamePaused(GetWorld())) {
		if (Value) {
			/*UE_LOG(LogTemp, Warning, TEXT("%f"), Value);*/
			if (!IsDiving) {
				if (Value < 0.f) {
					if (GetActorRotation().Pitch > MinPitchLimit) {
						AddActorLocalRotation(FRotator(Value * 1.3, 0, 0));
					}
				}
				else {
					if (GetActorRotation().Pitch < MaxPitchLimit) {
						/*if (IsDiving) {
							DiveCatch();
						}*/
						AddActorLocalRotation(FRotator(Value * 1.3, 0, 0));
					}

				}
			}
			else {
				//0.5 to avoid "micro movement" as in just to make sure the player commits to end dive
				/*if (Value > 0.5f) {
					DiveCatch();
				}*/
				
			}

		}
	}

}

void AFlying509GameCharacter::YawMovement(float Value)
{
	//**Not used for now
	/*if (Value) {

		if (Value < 0.f) {
			if (GetActorRotation().Roll > -60 ) {
				AddActorLocalRotation(FRotator(0, Value , Value));
			}
		}
		else {
			if (GetActorRotation().Roll < 60 ) {
				AddActorLocalRotation(FRotator(0, Value , Value));
			}

		}
		
	}*/

	if (!UGameplayStatics::IsGamePaused(GetWorld()) && !IsDiving && !IsGamepad) {

		if (Value) {

			AddControllerYawInput(Value);
			if (!IsFreeCam) {
				if (Value < 0.f) {
					if (GetActorRotation().Roll > MinRollLimit) {
						AddActorLocalRotation(FRotator(0, 0, Value));
					}
				}
				else {
					if (GetActorRotation().Roll < MaxRollLimit) {
						AddActorLocalRotation(FRotator(0, 0, Value));
					}

				}
			}

		}
		else {
			if (!IsFreeCam) {
				if (GetActorRotation().Roll > 1 || GetActorRotation().Roll < 1) {
					if (GetActorRotation().Roll > 1) {
						AddActorLocalRotation(FRotator(0, 0, -1));
					}
					else if (GetActorRotation().Roll < -1) {
						AddActorLocalRotation(FRotator(0, 0, 1));
					}
				}
				else {
					if (GetActorRotation().Roll > 0) {
						AddActorLocalRotation(FRotator(0, 0, -0.1));
					}
					else if (GetActorRotation().Roll < 0) {
						AddActorLocalRotation(FRotator(0, 0, 0.1));
					}
				}
			}

		}
		
	}

}

void AFlying509GameCharacter::YawMovementGamepad(float Value)
{

	if (!UGameplayStatics::IsGamePaused(GetWorld()) && !IsDiving && IsGamepad) {

		if (Value) {
			
			// find out which way is right
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get right vector 
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			// add movement in that direction
			AddMovementInput(Direction, Value * YawTurnScale);

			if (Value < 0.f) {
				if (GetActorRotation().Roll > MinRollLimit) {
					AddActorLocalRotation(FRotator(0, 0, Value));
				}
			}
			else {
				if (GetActorRotation().Roll < MaxRollLimit) {
					AddActorLocalRotation(FRotator(0, 0, Value));
				}

			}
			

		}
		else {
			if (GetActorRotation().Roll > 1 || GetActorRotation().Roll < 1) {
				if (GetActorRotation().Roll > 1) {
					AddActorLocalRotation(FRotator(0, 0, -1));
				}
				else if (GetActorRotation().Roll < -1) {
					AddActorLocalRotation(FRotator(0, 0, 1));
				}
			}
			else {
				if (GetActorRotation().Roll > 0) {
					AddActorLocalRotation(FRotator(0, 0, -0.1));
				}
				else if (GetActorRotation().Roll < 0) {
					AddActorLocalRotation(FRotator(0, 0, 0.1));
				}
			}
			

		}

	}

}



void AFlying509GameCharacter::RollMovement(float Value)
{
	if (Value) {

		AddActorLocalRotation(FRotator(0, 0, Value));

	}

}

void AFlying509GameCharacter::ForwardFlight()
{
	if (!IsFreeCam && !IsGamepad) {

		//**Forward flight follows mouse yaw movement
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(GetActorRotation().Pitch, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, 1);
	}
	else {
		//**No mouse yaw movement
		// find out which way is forward
		const FRotator PitchRotation(GetActorRotation().Pitch, 0, 0);

		// get forward vector
		/*const FVector Direction = FRotationMatrix(PitchRotation).GetUnitAxis(EAxis::X);*/
		const FVector Direction = GetActorForwardVector();
		AddMovementInput(Direction, 1);
	}
	
}

void AFlying509GameCharacter::FallVelocityTick()
{
	if (IsDiving) {
		//if flying speed is less or the same with boost speed, reset the maxzvelocity variable, so that dive speed returns back to normal
		if (GetCharacterMovement()->MaxFlySpeed <= BoostFlightSpeed) {
			MaxZVelocity = 1;
		}
		float tickVelocity = fabs(GetCharacterMovement()->Velocity.Z);
		if (tickVelocity > MaxZVelocity) {
			MaxZVelocity = tickVelocity;
		}
		
	}
}

void AFlying509GameCharacter::Boost()
{
	if (!IsDiving) {
		IsBoosting = true;
		//Assign current FOV
		CurrentFOV = FollowCamera->FieldOfView;
		CurrentCameraBoom = CameraBoom->TargetArmLength;
		CameraBoostInDuration = 0;
		CameraBoostInTimeElapsed = 0;
		CameraBoostOutDuration = 1.;

		if (OnDiveCatchSpeed) {
			GetCharacterMovement()->MaxFlySpeed += BoostFlightSpeed;
		}
		else {
			GetCharacterMovement()->MaxFlySpeed = BoostFlightSpeed;
		}
	}
	
}

void AFlying509GameCharacter::StopBoost()
{
	if (!IsDiving) {
		IsBoosting = false;
		//Assign current FOV
		CurrentFOV = FollowCamera->FieldOfView;
		CurrentCameraBoom = CameraBoom->TargetArmLength;
		CameraBoostOutDuration = 0;
		CameraBoostOutTimeElapsed = 0;
		CameraBoostInDuration = 1.;
		if (OnDiveCatchSpeed) {
			GetCharacterMovement()->MaxFlySpeed -= BoostFlightSpeed;
		}
		else {
			GetCharacterMovement()->MaxFlySpeed = NormalFlightSpeed;
		}
	}
}

void AFlying509GameCharacter::BoostLerpOut(float DeltaTime)
{
	if (CameraBoostOutDuration > 0) {
		if (CameraBoostOutTimeElapsed < CameraBoostOutDuration) {
			float alpha = CameraBoostOutTimeElapsed / CameraBoostOutDuration;
			if (alpha > 0 || alpha < 1) {
				FollowCamera->FieldOfView = FMath::Lerp(CurrentFOV, DefaultFOV + 10, alpha);
				CameraBoom->TargetArmLength = FMath::Lerp(CurrentCameraBoom, DefaultCameraBoom + 60, alpha);
				CameraBoostOutTimeElapsed += DeltaTime;
			}
			return;
		}
		
		CameraBoostOutDuration = 0;
		CameraBoostOutTimeElapsed = 0;
		
	}
}

void AFlying509GameCharacter::BoostLerpIn(float DeltaTime)
{
	if (CameraBoostInDuration > 0) {
		if (CameraBoostInTimeElapsed < CameraBoostInDuration) {
			float alpha = CameraBoostInTimeElapsed / CameraBoostInDuration;
			if (alpha > 0 || alpha < 1) {
				FollowCamera->FieldOfView = FMath::Lerp(CurrentFOV, DefaultFOV, alpha);
				CameraBoom->TargetArmLength = FMath::Lerp(CurrentCameraBoom, DefaultCameraBoom, alpha);
				CameraBoostInTimeElapsed += DeltaTime;
			}
			return;
		}
	
		CameraBoostInDuration = 0;
		CameraBoostInTimeElapsed = 0;
		

	}
}

void AFlying509GameCharacter::Dive()
{
	IsDiving = true;

	GetCharacterMovement()->MovementMode = MOVE_Falling;
	CurrentControlRotation = Controller->GetControlRotation();
	CurrentActorRotation = GetActorRotation();
	DiveTimeline->PlayFromStart();

	CurrentFOV = FollowCamera->FieldOfView;
	CurrentCameraBoom = CameraBoom->TargetArmLength;
	CameraDiveInDuration = 0;
	CameraDiveInTimeElapsed = 0;
	CameraDiveOutDuration = 2.;
	/*SetActorRelativeRotation(FRotator(-90, GetActorRotation().Yaw, GetActorRotation().Roll));*/
	/*CameraBoom->bUsePawnControlRotation = false;*/
	/*FollowCamera->SetRelativeRotation(FRotator(0, 0, 0));
	FollowCamera->SetRelativeLocation(FVector(defaultCameraLocation.X, 0, 0));*/

}

void AFlying509GameCharacter::DiveCatch()
{
	IsDiving = false;
	GetCharacterMovement()->MovementMode = MOVE_Flying;
	CurrentControlRotation = Controller->GetControlRotation();
	CurrentActorRotation = GetActorRotation();
	CatchTimeline->PlayFromStart();

	GetCharacterMovement()->MaxFlySpeed = NormalFlightSpeed * (round(MaxZVelocity) / 200);
	OnDiveCatchSpeed = true;

	CurrentFOV = FollowCamera->FieldOfView;
	CurrentCameraBoom = CameraBoom->TargetArmLength;
	CameraDiveOutDuration = 0;
	CameraDiveOutTimeElapsed = 0;
	CameraDiveInDuration = 1.;
	

	//AddActorLocalRotation(FMath::RInterpTo(FRotator(-90,NULL,NULL), FRotator(60, NULL, NULL), FApp::GetDeltaTime(), 10.0));
	/*CameraBoom->bUsePawnControlRotation = true;*/
	/*FollowCamera->SetRelativeRotation(defaultCameraRotation);
	FollowCamera->SetRelativeLocation(defaultCameraLocation);*/
}

void AFlying509GameCharacter::DiveTimelineFloatReturn(float value)
{
	CatchTimeline->Stop();
	
	SetActorRotation(FMath::Lerp(CurrentActorRotation, FRotator(-90, CurrentControlRotation.Yaw, CurrentControlRotation.Roll), value));
	Controller->SetControlRotation(FMath::Lerp(CurrentControlRotation, FRotator(-90, CurrentControlRotation.Yaw, CurrentControlRotation.Roll), value));
}

void AFlying509GameCharacter::DiveCatchTimelineFloatReturn(float value)
{
	DiveTimeline->Stop();
	if (CurrentActorRotation.Pitch > -80) {
		SetActorRotation(FMath::Lerp(CurrentActorRotation, FRotator(0, CurrentControlRotation.Yaw, CurrentControlRotation.Roll), value));
		Controller->SetControlRotation(FMath::Lerp(CurrentControlRotation, FRotator(0, CurrentControlRotation.Yaw, CurrentControlRotation.Roll), value));
	}
	else {
	
		SetActorRotation(FMath::Lerp(CurrentControlRotation, FRotator(50, CurrentControlRotation.Yaw, CurrentControlRotation.Roll), value));
		Controller->SetControlRotation(FMath::Lerp(CurrentControlRotation, FRotator(35, CurrentControlRotation.Yaw, CurrentControlRotation.Roll), value));
	}
	
}

void AFlying509GameCharacter::OnTimelineFinished()
{
}

void AFlying509GameCharacter::DiveCatchSpeedAdjustment()
{
	if (OnDiveCatchSpeed) {
		GetCharacterMovement()->MaxFlySpeed = GetCharacterMovement()->MaxFlySpeed - SpeedDecrementAdjuster;
		float tempSpeed = IsBoosting ? BoostFlightSpeed : NormalFlightSpeed;
		if (GetCharacterMovement()->MaxFlySpeed <= tempSpeed) {
			OnDiveCatchSpeed = false;
		}
	}
}

void AFlying509GameCharacter::DiveLerpOut(float DeltaTime)
{
	if (CameraDiveOutDuration > 0 && CurrentCameraBoom) {
		if (CameraDiveOutTimeElapsed < CameraDiveOutDuration) {
			float alpha = CameraDiveOutTimeElapsed / CameraDiveOutDuration;
			if (alpha > 0 || alpha < 1) {
				/*GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%f"), alpha));*/
				FollowCamera->FieldOfView = FMath::Lerp(CurrentFOV, DefaultFOV + 15, alpha);
				CameraBoom->TargetArmLength = FMath::Lerp(CurrentCameraBoom, DefaultCameraBoom + 200, alpha);
				CameraDiveOutTimeElapsed += DeltaTime;
			}
			return;
		}

		CameraDiveOutDuration = 0;
		CameraDiveOutTimeElapsed = 0;

	}
}

void AFlying509GameCharacter::DiveLerpIn(float DeltaTime)
{
	if (CameraDiveInDuration > 0 && CurrentCameraBoom) {
		if (CameraDiveInTimeElapsed < CameraDiveInDuration) {
			float alpha = CameraDiveInTimeElapsed / CameraDiveInDuration;
			if (alpha > 0 || alpha < 1) {
				FollowCamera->FieldOfView = FMath::Lerp(CurrentFOV, DefaultFOV, alpha);
				CameraBoom->TargetArmLength = FMath::Lerp(CurrentCameraBoom, DefaultCameraBoom, alpha);
				CameraDiveInTimeElapsed += DeltaTime;
			}
			return;
		}

		CameraDiveInDuration = 0;
		CameraDiveInTimeElapsed = 0;

	}
}

void AFlying509GameCharacter::GuideOn()
{
	ShowGuide = true;
}

void AFlying509GameCharacter::GuideOff()
{
	ShowGuide = false;
}

void AFlying509GameCharacter::FreeCamera()
{
	if (!IsFreeCam) {
		CurrentCameraRotate = Controller->GetControlRotation();
	}
	else {
		Controller->SetControlRotation(CurrentCameraRotate);
		/*UE_LOG(LogTemp, Warning, TEXT("%f"), CurrentCameraRotate.Yaw);*/
	}
	
	IsFreeCam = !IsFreeCam;
}


void AFlying509GameCharacter::OnResetVR()
{
	// If Flying509Game is added to a project via 'Add Feature' in the Unreal Editor the dependency on HeadMountedDisplay in Flying509Game.Build.cs is not automatically propagated
	// and a linker error will result.
	// You will need to either:
	//		Add "HeadMountedDisplay" to [YourProject].Build.cs PublicDependencyModuleNames in order to build successfully (appropriate if supporting VR).
	// or:
	//		Comment or delete the call to ResetOrientationAndPosition below (appropriate if not supporting VR)
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AFlying509GameCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void AFlying509GameCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void AFlying509GameCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	if (!IsDiving) AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AFlying509GameCharacter::LookUp(float Value)
{
	if(!IsDiving) APawn::AddControllerPitchInput(Value);
}

void AFlying509GameCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	if (!IsDiving) AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AFlying509GameCharacter::MoveForward(float Value)
{
	
	if ((Controller != nullptr) && (Value != 0.0f))
	{

		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AFlying509GameCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value * YawTurnScale);
	}
}

