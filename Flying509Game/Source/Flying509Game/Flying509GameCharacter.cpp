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

//////////////////////////////////////////////////////////////////////////
// AFlying509GameCharacter

AFlying509GameCharacter::AFlying509GameCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
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
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	//Default camera position
	defaultCameraRotation = FollowCamera->GetRelativeRotation();
	defaultCameraLocation = FollowCamera->GetRelativeLocation();

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

	PlayerInputComponent->BindAxis("Pitch", this, &AFlying509GameCharacter::PitchMovement);
	/*PlayerInputComponent->BindAxis("Yaw", this, &AFlying509GameCharacter::MoveRight);*/
	/*PlayerInputComponent->BindAxis("Roll", this, &AFlying509GameCharacter::RollMovement);*/

	PlayerInputComponent->BindAction("Boost", IE_Pressed, this, &AFlying509GameCharacter::Boost);
	PlayerInputComponent->BindAction("Boost", IE_Released, this, &AFlying509GameCharacter::StopBoost);

	PlayerInputComponent->BindAction("Dive", IE_Pressed, this, &AFlying509GameCharacter::Dive);
	/*PlayerInputComponent->BindAction("Dive", IE_Released, this, &AFlying509GameCharacter::DiveCatch);*/

	PlayerInputComponent->BindAction("FreeCamera", IE_Pressed, this, &AFlying509GameCharacter::FreeCamera);
	PlayerInputComponent->BindAction("FreeCamera", IE_Released, this, &AFlying509GameCharacter::FreeCamera);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	//PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Turn", this, &AFlying509GameCharacter::YawMovement);
	PlayerInputComponent->BindAxis("TurnRate", this, &AFlying509GameCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
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
		CatchTimeline->AddInterpFloat(diveCurve, CatchInterpFunction, FName("Alpha"));
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
	ForwardFlight();
	FallVelocityTick();
	DiveCatchSpeedAdjustment();
}


void AFlying509GameCharacter::Shoot()
{
	UE_LOG(LogTemp, Warning, TEXT("SHOOSTED"));
	FTransform SpawnTransform = GetActorTransform();
	SpawnTransform.SetLocation(FollowCamera->GetComponentRotation().Vector() * 200.f + GetActorLocation());
	FActorSpawnParameters SpawnParameters;
	GetWorld()->SpawnActor<ABullet>(BulletBP, SpawnTransform, SpawnParameters);
}

void AFlying509GameCharacter::DiveTimelineFloatReturn(float value)
{
	const FRotator Rotation = Controller->GetControlRotation();
	SetActorRotation(FMath::Lerp(GetActorRotation(), FRotator(-90, Rotation.Yaw, Rotation.Roll), value));
	Controller->SetControlRotation(FMath::Lerp(Controller->GetControlRotation(), FRotator(-90, Rotation.Yaw, Rotation.Roll), value));
	//FMath::RInterpTo(GetActorRotation(), FRotator(-90, 0, 0), FApp::GetDeltaTime(), 0.01)
}

void AFlying509GameCharacter::DiveCatchTimelineFloatReturn(float value)
{
	const FRotator Rotation = GetActorRotation();
	SetActorRotation(FMath::Lerp(Rotation, FRotator(-50, Rotation.Yaw, Rotation.Roll), value));
}

void AFlying509GameCharacter::OnTimelineFinished()
{
}

void AFlying509GameCharacter::PitchMovement(float Value)
{
	if (Value) {
		
		if (Value < 0.f) {
			if (GetActorRotation().Pitch > MinPitchLimit) {
				AddActorLocalRotation(FRotator(Value, 0, 0));
			}
		}
		else {
			if (GetActorRotation().Pitch < MaxPitchLimit) {
				if (IsDiving) {
					DiveCatch();
				}
				AddActorLocalRotation(FRotator(Value, 0, 0));
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
	if(!IsDiving){
		if (Value) {

			AddControllerYawInput(Value);

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
	if (!IsFreeCam) {
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
		
		float tickVelocity = fabs(GetCharacterMovement()->Velocity.Z);
		if (tickVelocity > MaxZVelocity) {
			MaxZVelocity = tickVelocity;
		}
		
	}
}

void AFlying509GameCharacter::Boost()
{
	IsBoosting = true;
	if (OnDiveCatchSpeed) {
		GetCharacterMovement()->MaxFlySpeed += BoostFlightSpeed;
	}
	else {
		GetCharacterMovement()->MaxFlySpeed = BoostFlightSpeed;
	}
	
}

void AFlying509GameCharacter::StopBoost()
{
	IsBoosting = false;
	if (OnDiveCatchSpeed) {
		GetCharacterMovement()->MaxFlySpeed -= BoostFlightSpeed;
	}
	else {
		GetCharacterMovement()->MaxFlySpeed = NormalFlightSpeed;
	}
	
}

void AFlying509GameCharacter::Dive()
{
	IsDiving = true;
	GetCharacterMovement()->MovementMode = MOVE_Falling;
	DiveTimeline->PlayFromStart();
	/*SetActorRelativeRotation(FRotator(-90, GetActorRotation().Yaw, GetActorRotation().Roll));*/
	/*CameraBoom->bUsePawnControlRotation = false;*/
	/*FollowCamera->SetRelativeRotation(FRotator(0, 0, 0));
	FollowCamera->SetRelativeLocation(FVector(defaultCameraLocation.X, 0, 0));*/

}

void AFlying509GameCharacter::DiveCatch()
{
	IsDiving = false;
	GetCharacterMovement()->MovementMode = MOVE_Flying;
	GetCharacterMovement()->MaxFlySpeed = NormalFlightSpeed * (round(MaxZVelocity) / 200);
	OnDiveCatchSpeed = true;
	
	//CatchTimeline->PlayFromStart();
	//AddActorLocalRotation(FMath::RInterpTo(FRotator(-90,NULL,NULL), FRotator(60, NULL, NULL), FApp::GetDeltaTime(), 10.0));
	/*CameraBoom->bUsePawnControlRotation = true;*/
	/*FollowCamera->SetRelativeRotation(defaultCameraRotation);
	FollowCamera->SetRelativeLocation(defaultCameraLocation);*/
}

void AFlying509GameCharacter::DiveCatchSpeedAdjustment()
{
	if (OnDiveCatchSpeed) {
		GetCharacterMovement()->MaxFlySpeed = GetCharacterMovement()->MaxFlySpeed - 1;
		UE_LOG(LogTemp, Warning, TEXT("%f"), GetCharacterMovement()->MaxFlySpeed);
		float tempSpeed = IsBoosting ? BoostFlightSpeed : NormalFlightSpeed;
		if (GetCharacterMovement()->MaxFlySpeed <= tempSpeed) {
			OnDiveCatchSpeed = false;
		}
	}
}

void AFlying509GameCharacter::FreeCamera()
{
	if (!IsFreeCam) {
		CurrentCameraRotate = Controller->GetControlRotation();
	}
	else {
		Controller->SetControlRotation(CurrentCameraRotate);
		UE_LOG(LogTemp, Warning, TEXT("%f"), CurrentCameraRotate.Yaw);
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
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AFlying509GameCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
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

