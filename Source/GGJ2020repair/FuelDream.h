#pragma once

//#include "CoreMinimal.h"
#include "PipeSegment.h"

#define FUEL_DREAM_FIELD_WIDTH 9
#define FUEL_DREAM_FIELD_HEIGHT 9

/*
#define LogFuelDream 0
#define Log 0
void UE_LOG(int system, int level, char* message) {
  cout << message;
}*/

/**
 *
 */
//class GGJ2020REPAIR_API FuelDream
class FuelDream
{
private:
  float fill_rate;

  bool flowing = false;
  bool leaking = false;
  bool goal_reached = false;

  PipeSegment* field[FUEL_DREAM_FIELD_WIDTH][FUEL_DREAM_FIELD_HEIGHT];

  int at_pipe_x;
  int at_pipe_y;

  int goal_x;
  int goal_y;
  int goal_side;

  char msg[500]; //TODO: remove

public:
	FuelDream();
	~FuelDream();

  void generateTestField();

  PipeSegment* getSegment(int x, int y);
  PipeSegment* getCurrentSegment();
  void placeSegment(int type, int x, int y);

  int walkFlow(PipeSegment& seg);
  void tick(float delta);

  void startFlow(int x, int y, int side);
  void leak(PipeSegment& seg, int side);
  bool checkFlowReachedGoal();
  void win();

  void log(const char* message);
};