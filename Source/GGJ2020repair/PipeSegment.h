#pragma once

//#include "CoreMinimal.h"

#define SEG_EMPTY 0
#define SEG_STRAIGHT_VERTICAL 1
#define SEG_STRAIGHT_HORIZONTAL 2
#define SEG_STRAIGHT_CROSS 3
#define SEG_CORNER_TOP_RIGHT 4
#define SEG_CORNER_TOP_LEFT 5
#define SEG_CORNER_BOTTOM_RIGHT 6
#define SEG_CORNER_BOTTOM_LEFT 7

#define SIDE_NONE -1
#define SIDE_TOP 0
#define SIDE_RIGHT 1
#define SIDE_BOTTOM 2
#define SIDE_LEFT 3


/**
 *
 */
//class GGJ2020REPAIR_API PipeSegment
class PipeSegment
{
public: // should be private but I don't want wanna deal
  int x,y;
  int type;
  int fill_side;
  float fill_amount = 0;
  bool full = false; // don't trust the float, mark it when it becomes full
  bool leaking = false;
  int leaking_from;

public:
	PipeSegment(int x, int y, int pipe_type);
	~PipeSegment();

  void reset();

  int getType();
  void setType(int pipe_type);

  bool getLeaking();
  int getLeakingSide();
  bool getFull();
  float getFillAmount();

  bool validEntrance(int side);
  int getExit();
};
