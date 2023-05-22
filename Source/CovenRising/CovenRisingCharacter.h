// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "BaseItemActor.h"
#include "CovenRisingCharacter.generated.h"


UCLASS(config=Game)
class ACovenRisingCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** Open Inventory Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* OpenInventoryAction;

	/** Interact Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* InteractAction;

	/** Scroll Hotbar Slots Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* ScrollHotbarSlotsAction;
public:
	ACovenRisingCharacter();
	

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
			
	/** Called for interact input */
	void Interact(const FInputActionValue& Value);


protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Inventory)
	class UInventoryActorComponent* InventoryComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Inventory)
	ABaseItemActor* HeldItemActor;

	FTimerHandle AnimationTimer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory)
	bool bIsHeldItemVisible;

	UFUNCTION()
		void StopAnimation();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		UAnimSequence* DigAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		UAnimSequence* CleanAnimation;

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = Inventory)
	void AddItemToInventory(FName ItemId, int ItemCount);

	UFUNCTION()
	ABaseItemActor* GetHeldItemActor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void PlayAnimation(UAnimSequence* Animation, int Duration);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = Camera)
		void SwitchToFirstPerson();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = Camera)
		void SwitchToThirdPerson();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = Inventory)
		void TakeFromSlot(int SlotId, int Amount);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = Inventory)
		void TakeFromHeldItem(int Amount);

	UFUNCTION(BlueprintCallable, Category = Inventory)
		void SetHeldItemVisibility(bool Visibility);


};

