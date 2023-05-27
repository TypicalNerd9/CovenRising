// Copyright Epic Games, Inc. All Rights Reserved.

#include "CovenRisingCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include <CovenRising/Private/InventoryActorComponent.h>
#include <CovenRising/Private/InteractableInterface.h>
#include "Components/DecalComponent.h"


//////////////////////////////////////////////////////////////////////////
// ACovenRisingCharacter

ACovenRisingCharacter::ACovenRisingCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
	InventoryComponent = CreateDefaultSubobject<UInventoryActorComponent>(TEXT("Inventory"));
	AddOwnedComponent(InventoryComponent);

	PreviewDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("Preview Decal"));
	PreviewDecal->SetupAttachment(RootComponent);
	PreviewDecal->SetVisibility(false);
}

void ACovenRisingCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	AddItemToInventory(FName(TEXT("shovel")), 1);
	AddItemToInventory(FName(TEXT("salt_cellar")), 1);
	AddItemToInventory(FName(TEXT("ritual_altar")), 1);
	AddItemToInventory(FName(TEXT("candle")), 10);
	AddItemToInventory(FName(TEXT("skull")), 1);
	AddItemToInventory(FName(TEXT("brazier")), 1);
	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void ACovenRisingCharacter::StopAnimation()
{
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetController()->ResetIgnoreMoveInput();
	GetController()->ResetIgnoreLookInput();
}

// Called every frame
void ACovenRisingCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACovenRisingCharacter::PlayAnimation(UAnimSequence* Animation, int Duration)
{
	
	GetController()->SetIgnoreMoveInput(true);
	GetController()->SetIgnoreLookInput(true);
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationSingleNode);
	GetMesh()->PlayAnimation(Animation, false);
	GetWorld()->GetTimerManager().SetTimer(AnimationTimer, this, &ACovenRisingCharacter::StopAnimation, Duration, false);
}

void ACovenRisingCharacter::SetHeldItemVisibility(bool Visibility)
{
	bIsHeldItemVisible = !Visibility;
	if (HeldItemActor) {
		HeldItemActor->SetActorHiddenInGame(!Visibility);
	}
}

ABaseItemActor* ACovenRisingCharacter::GetHeldItemActor()
{
	return HeldItemActor;
}

//////////////////////////////////////////////////////////////////////////
// Input

void ACovenRisingCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACovenRisingCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACovenRisingCharacter::Look);

		//Interact
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &ACovenRisingCharacter::Interact);

		//Confirm
		EnhancedInputComponent->BindAction(ConfirmAction, ETriggerEvent::Triggered, this, &ACovenRisingCharacter::Confirm);
	}

}

void ACovenRisingCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ACovenRisingCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ACovenRisingCharacter::Interact(const FInputActionValue& Value)
{
	
	FVector Location;
	FRotator Rotation;
	GetController()->GetPlayerViewPoint(Location, Rotation);
	FHitResult hit;
	bool bHit = GetWorld()->LineTraceSingleByChannel(hit, Location, Location + Rotation.Vector() * 1000, ECC_Visibility);
	if (bHit) {
		if (hit.GetActor()->Implements<UInteractableInterface>()) {
			IInteractableInterface* Interactable = Cast<IInteractableInterface>(hit.GetActor());
			if (Interactable) {
				IInteractableInterface::Execute_Interact(hit.GetActor(), this);
			}
		}
	}
}

void ACovenRisingCharacter::Confirm(const FInputActionValue& Value)
{
	if (HeldItemActor) {
		HeldItemActor->ConfirmTriggered();
	}
}




