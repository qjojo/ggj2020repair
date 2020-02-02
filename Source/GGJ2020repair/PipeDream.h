// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "FuelDream.h"

#include "PipeDream.generated.h"


UCLASS()
class GGJ2020REPAIR_API APipeDream : public AActor
{
	GENERATED_BODY()

	FuelDream* fuelDream;

public:
	// Sets default values for this actor's properties
	APipeDream();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure)
	static int TestUMethod(int a) {
		return a + 2;
	}

	UFUNCTION(BlueprintCallable)
	bool GoalReached();

	UFUNCTION(BlueprintCallable)
	void PlaceSegment(int type, int x, int y);

	UFUNCTION(BlueprintCallable)
	int GetSegmentType(int x, int y);

	UFUNCTION(BlueprintCallable)
	float GetSegmentFillAmount(int x, int y);

	UFUNCTION(BlueprintCallable)
	int GetSegmentFillSide(int x, int y);

	UFUNCTION(BlueprintCallable)
	int GetSegmentLeakSide(int x, int y);
};
