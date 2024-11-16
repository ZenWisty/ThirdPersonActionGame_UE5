// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Items/Weapon.h"
#include "Components/BoxComponent.h"

AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());

	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetupAttachment(CameraBoom);
}

void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyCharacter::MoveForward(float value) {
	if (ActionState == EActionState::EAS_Attacking) return;
	if (Controller && (value != 0)) {
		/*FVector Forward = GetActorForwardVector();
		AddMovementInput(Forward, value);*/
		const FRotator ControlRotation = GetControlRotation();
		const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);

		const FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Forward, value);
	}
}

void AMyCharacter::MoveRight(float value) {
	if (ActionState == EActionState::EAS_Attacking) return;
	if (Controller && (value != 0)) {
		/*FVector Forward = GetActorRightVector();
		AddMovementInput(Forward, value);*/
		const FRotator ControlRotation = GetControlRotation();
		const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);

		const FVector Right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Right, value);
	}
}

void AMyCharacter::Turn(float value) {
	if (Controller && (value!=0.f))
		AddControllerYawInput(value);
}

void AMyCharacter::LookUp(float value) {
	if (Controller && (value!=0.f))
		AddControllerPitchInput(value);
}

void AMyCharacter::MyJump()
{
	/* ERROR: 这里的Action State 检查没有起到作用，可能源于 BindAction 的触发机制 */
	/*if (ActionState == EActionState::EAS_Attacking) return; 
	Super::Jump();*/

	if (ActionState != EActionState::EAS_Attacking) {
		Super::Jump();
	}
}

void AMyCharacter::EKeyPressed()
{
	AWeapon* OverlappingWeapon = Cast<AWeapon>(overlappingItem);
	if (OverlappingWeapon) {
		OverlappingWeapon->Equip(this->GetMesh(), FName("hand_r_socket"));
		EquipedWeapon = OverlappingWeapon;
	}

	State = ECharacterState::ECS_EquippedOneHandedWeapon;
}

void AMyCharacter::Attack()
{
	if (ActionState == EActionState::EAS_UnOccupied && State != ECharacterState::ECS_UnEquipped)
	{
		PlayAttackMontage();
		ActionState = EActionState::EAS_Attacking;
	}
}

void AMyCharacter::AttackEnd()
{
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(1, 3, FColor::Blue, FString("Attack End being called."));
	}
	ActionState = EActionState::EAS_UnOccupied;
}

void AMyCharacter::PlayAttackMontage()
{

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

	if (AnimInstance && AttackMontage) {
		AnimInstance->Montage_Play(AttackMontage);
		int32 Selection = FMath::RandRange(0, 1);
		FName SectionName = FName();
		switch (Selection)
		{
		case 0:
			SectionName = FName("Attack1");
			break;
		case 1:
			SectionName = FName("Attack2");
			break;
		default:
			break;
		}
		AnimInstance->Montage_JumpToSection(SectionName, AttackMontage);
	}
}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis(FName("MoveRight"), this, &AMyCharacter::MoveRight);
	PlayerInputComponent->BindAxis(FName("Turn"), this, &AMyCharacter::Turn);
	PlayerInputComponent->BindAxis(FName("LookUp"), this, &AMyCharacter::LookUp);

	PlayerInputComponent->BindAction(FName("Jump"), IE_Pressed, this, &AMyCharacter::MyJump);
	PlayerInputComponent->BindAction(FName("Equip"), IE_Pressed, this, &AMyCharacter::EKeyPressed);
	PlayerInputComponent->BindAction(FName("Attack"), IE_Pressed, this, &AMyCharacter::Attack);
}

void AMyCharacter::SetWeaponCollisionEnabled(ECollisionEnabled::Type CollisionEnabled)
{
	if (EquipedWeapon && EquipedWeapon->GetWeaponBox()) 
	{
		EquipedWeapon->GetWeaponBox()->SetCollisionEnabled(CollisionEnabled);
	}
}

