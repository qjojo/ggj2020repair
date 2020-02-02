// by Corey B

#include "FuelDream.h"

#include <iostream>

FuelDream::FuelDream() {
  fill_rate = 0.25;

  for (int i = 0; i < FUEL_DREAM_FIELD_WIDTH; i++) {
    for (int j = 0; j < FUEL_DREAM_FIELD_HEIGHT; j++) {
      field[i][j] = new PipeSegment(i, j, 0);
      //std::cout << i << ' ' << j << ' ' << field[i][j]->x << ' ' << field[i][j]->y << std::endl;
    }
  }

  /*goal_x = 3;
  goal_y = 0;
  goal_side = 0;*/
  goal_x = 7;
  goal_y = 6;
  goal_side = 1;
}

void FuelDream::generateTestField() {
  placeSegment(SEG_STRAIGHT_HORIZONTAL, 7, 6);
  placeSegment(SEG_CORNER_TOP_RIGHT, 6, 6);
  placeSegment(SEG_CORNER_BOTTOM_LEFT, 6, 5);
  placeSegment(SEG_CORNER_BOTTOM_RIGHT, 5, 5);
  placeSegment(SEG_STRAIGHT_VERTICAL, 5, 6);
  placeSegment(SEG_CORNER_TOP_LEFT, 5, 7);

  placeSegment(SEG_CORNER_TOP_RIGHT, 4, 7);
  placeSegment(SEG_STRAIGHT_VERTICAL, 4, 6);
  placeSegment(SEG_STRAIGHT_VERTICAL, 4, 5);
  placeSegment(SEG_STRAIGHT_VERTICAL, 4, 4);

  placeSegment(SEG_STRAIGHT_CROSS, 4, 3);
  placeSegment(SEG_CORNER_BOTTOM_RIGHT, 4, 2);
  placeSegment(SEG_CORNER_BOTTOM_LEFT, 5, 2);
  placeSegment(SEG_CORNER_TOP_LEFT, 5, 3);
  // back into the cross 4,3

  placeSegment(SEG_CORNER_TOP_RIGHT, 3, 3);
  placeSegment(SEG_STRAIGHT_VERTICAL, 3, 2);
  placeSegment(SEG_STRAIGHT_VERTICAL, 3, 1);
  placeSegment(SEG_STRAIGHT_VERTICAL, 3, 0);
}

PipeSegment* FuelDream::getSegment(int x, int y) {
  if ((x < 0 || x > FUEL_DREAM_FIELD_WIDTH - 1) || (y < 0 || y > FUEL_DREAM_FIELD_HEIGHT - 1)) {
    return new PipeSegment(x, y, 0);
  }
  return field[x][y];
}

PipeSegment* FuelDream::getCurrentSegment() {
  return getSegment(at_pipe_x, at_pipe_y);
}

void FuelDream::placeSegment(int type, int x, int y) {
  PipeSegment& seg = *(field[x][y]);
  seg.reset();
  seg.setType(type);
}

int FuelDream::walkFlow(PipeSegment& seg) {
  if (seg.fill_amount < 1.0) return -1;

  int exit_side = seg.getExit();

  if (checkFlowReachedGoal()) {
    win();
    return -1;
  }

  int entrance = SIDE_NONE;

  switch(exit_side) {
    case SIDE_NONE:
      //uh-oh
      log("exit_side is SIDE_NONE");
      break;

    case SIDE_TOP:
      at_pipe_y -= 1;
      entrance = SIDE_BOTTOM;
      break;

    case SIDE_RIGHT:
      at_pipe_x += 1;
      entrance = SIDE_LEFT;
      break;

    case SIDE_BOTTOM:
      at_pipe_y += 1;
      entrance = SIDE_TOP;
      break;

    case SIDE_LEFT:
      at_pipe_x -= 1;
      entrance = SIDE_RIGHT;
      break;
  }

  return entrance;
}

void FuelDream::tick(float delta) {
  if (flowing && !leaking) {
    float tick_fill = delta * fill_rate;
    PipeSegment* seg = getSegment(at_pipe_x, at_pipe_y);
    seg->fill_amount = seg->fill_amount + tick_fill;

    while (seg->fill_amount > 1.0f) {
      sprintf(msg, "segment filled: %d,%d .. %d,%d", seg->x, seg->y, at_pipe_x, at_pipe_y);
      log(msg);
      float overflow = seg->fill_amount - 1.0f; // extra fill for next piece
      seg->fill_amount = 1.0f;
      seg->full = true;

      int entrance_side = walkFlow(*seg);

      PipeSegment* next_seg = getCurrentSegment();

      if (next_seg->getType() == SEG_EMPTY) {
        leak(*seg, seg->getExit());
      }
      else {
        next_seg->fill_side = entrance_side;
        next_seg->fill_amount = overflow;
      }

      seg = next_seg;
    }

    sprintf(msg, "finished tick at: %d,%d - type %d, fill_amount %lf", at_pipe_x, at_pipe_y, seg->type, seg->fill_amount);
    log(msg);
  }
}

void FuelDream::startFlow(int x, int y, int fill_side) {
  flowing = true;
  at_pipe_x = x;
  at_pipe_y = y;

  PipeSegment& seg = *getSegment(x, y);
  seg.fill_side = fill_side;
  log("Flow started");
}

void FuelDream::leak(PipeSegment& seg, int side) {
  sprintf(msg, "leaking at: %d,%d side %d - type %d", at_pipe_x, at_pipe_y, side, seg.type);
  log(msg);

  //PipeSegment seg = getSegment(x, y);
  seg.leaking = true;
  seg.leaking_from = side;

  leaking = true;
}

bool FuelDream::checkFlowReachedGoal() {
  if (leaking) return false;
  if (goal_reached) return true;

  if (at_pipe_x == goal_x && at_pipe_y == goal_y) {
    PipeSegment& seg = *getCurrentSegment();
    if (seg.full && (seg.getExit() == goal_side)) {
      return true;
    }
  }

  return false;
}

void FuelDream::win() {
  log("goal reached");
  flowing = false;
  goal_reached = true;
}



void FuelDream::log(const char* message) {
  //UE_LOG(LogFuelDream, Log, TEXT(message));
  std::cout << message << std::endl;
}


/*int main(int argc, char** argv) {
  FuelDream& game = *(new FuelDream());
  game.generateTestField();
  //game.startFlow(7, 6, 1);
  game.startFlow(3, 3, 0);

  for (int i = 0; i < 1000; i++) {
    game.tick(0.21);
  }

  return 0;
}*/
