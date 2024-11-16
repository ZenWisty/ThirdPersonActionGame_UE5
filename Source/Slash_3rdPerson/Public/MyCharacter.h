// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Character/MyCharacterTypes.h"
#include "MyCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class AItem;
class UAnimMontage;
class AWeapon;

UCLASS()
class SLASH_3RDPERSON_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMyCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void SetWeaponCollisionEnabled(ECollisionEnabled::Type CollisionEnabled);

	FORCEINLINE void SetOverlappingItem(AItem* Item) { overlappingItem = Item; };
	FORCEINLINE ECharacterState GetCharacterState() const { return State; };

protected:
	virtual void BeginPlay() override;

	/**
	* call back for input
	*/
	void MoveForward(float value);
	void MoveRight(float value);
	void Turn(float value);
	void LookUp(float value);
	void MyJump();
	void EKeyPressed();
	void Attack();

	/**
	* Anim montage function
	*/
	void PlayAttackMontage();

	UFUNCTION(BlueprintCallable)
	void AttackEnd();

private:	
	
	ECharacterState State = ECharacterState::ECS_UnEquipped;
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EActionState ActionState = EActionState::EAS_UnOccupied;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* ViewCamera;

	UPROPERTY(VisibleAnywhere)
	AItem* overlappingItem;

	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* AttackMontage = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	AWeapon* EquipedWeapon = nullptr;
};
