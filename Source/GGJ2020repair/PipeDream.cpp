// Fill out your copyright notice in the Description page of Project Settings.


#include "PipeDream.h"

// Sets default values
APipeDream::APipeDream()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	fuelDream = new FuelDream();
}

// Called when the game starts or when spawned
void APipeDream::BeginPlay()
{
	Super::BeginPlay();
	fuelDream->generateTestField();
	fuelDream->startFlow(3, 3, 0);
}

// Called every frame
void APipeDream::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	fuelDream->tick(DeltaTime);
}

bool APipeDream::GoalReached()
{
	return fuelDream->checkFlowReachedGoal();
}

float APipeDream::GetSegmentFillAmount(int x, int y) {
	return fuelDream->getSegment(x, y)->fill_amount;
}

int APipeDream::GetSegmentFillSide(int x, int y) {
	return fuelDream->getSegment(x, y)->fill_side;
}

int APipeDream::GetSegmentLeakSide(int x, int y) {
	return fuelDream->getSegment(x, y)->leaking_from;
}
