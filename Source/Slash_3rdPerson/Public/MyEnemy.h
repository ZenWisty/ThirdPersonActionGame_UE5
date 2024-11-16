// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/HitInterface.h"
#include "MyEnemy.generated.h"

UCLASS()
class SLASH_3RDPERSON_API AMyEnemy : public ACharacter, public IHitInterface
{
	GENERATED_BODY()

public:
	AMyEnemy();

	virtual void GetHit(const FVector& ImpactPoint) override;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
