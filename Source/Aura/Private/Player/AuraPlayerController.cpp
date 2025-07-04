// Copyright Nixzxin


#include "Player/AuraPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);
	if (!Hit.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = Hit.GetActor();

	/**
	 * Line trace from cursor scenarios
	 * A. LasterActor is null ThisActor is null
	 *	- Do Nothing
	 * B. LasterActor is null ThisActor is valid
	 *	- Highlight this actor
	 * C. LastActor is valid ThisActor is null
	 *	- Unhighlight lastActor
	 * D. LastActor is valid ThisActor is valid, lastActor == ThisActor
	 *  - Do nothing
	 * E. LastActor is valid ThisActor is valid, lastActor != ThisActor 
	 *	- Unhighlight LastActor, Highlight ThisActor
	 * 
	 */
	if (LastActor == nullptr)
	{
		if (ThisActor != nullptr)
		{
			//case B
			ThisActor -> HighlightActor();
		}
		else
		{
			//case a, both null
		}
	}
	else //Last actor is valid
	{
		if (ThisActor == nullptr)
		{
			//case c
			LastActor -> UnHighlightActor();
		}
		else
		{
			if (LastActor != ThisActor)
			{
				//case E
				LastActor -> UnHighlightActor();
				ThisActor -> HighlightActor();
			}
			else
			{
				//Case D, do nothing
			}
		}
	}

}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);
	UEnhancedInputLocalPlayerSubsystem* Subsystems = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (Subsystems)
	{
		Subsystems->AddMappingContext(AuraContext,0);
	}
	
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0,Rotation.Yaw,0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}

}
