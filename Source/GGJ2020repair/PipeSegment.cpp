// by Corey B

#include "PipeSegment.h"

PipeSegment::PipeSegment(int x, int y, int pipe_type) {
  reset();
  this->x = x;
  this->y = y;
  this->type = pipe_type;
}

void PipeSegment::reset() {
  type = 0;
  fill_side = -1;
  fill_amount = 0;
  full = false;
  leaking = false;
  leaking_from = -1;
}

int PipeSegment::getType() {
  return type;
}

void PipeSegment::setType(int pipe_type) {
  this->type = pipe_type;
}

bool PipeSegment::getLeaking() {
  return leaking;
}

int PipeSegment::getLeakingSide() {
  return leaking_from;
}

float PipeSegment::getFillAmount() {
  return fill_amount;
}

bool PipeSegment::validEntrance(int side) {
  switch(type) {
    case SEG_EMPTY:
      return false;

    case SEG_STRAIGHT_VERTICAL:
      return side == SIDE_TOP || side == SIDE_BOTTOM;

    case SEG_STRAIGHT_HORIZONTAL:
      return side == SIDE_LEFT || side == SIDE_RIGHT;

    case SEG_STRAIGHT_CROSS:
      return true;

    case SEG_CORNER_TOP_RIGHT:
      return side == SIDE_TOP || side == SIDE_RIGHT;

    case SEG_CORNER_TOP_LEFT:
      return side == SIDE_TOP || side == SIDE_LEFT;

    case SEG_CORNER_BOTTOM_RIGHT:
      return side == SIDE_BOTTOM || side == SIDE_RIGHT;

    case SEG_CORNER_BOTTOM_LEFT:
      return side == SIDE_BOTTOM || side == SIDE_LEFT;

    default:
      return false;
  }
}

int PipeSegment::getExit() {
  switch(type) {
    case SEG_EMPTY:
      return SIDE_NONE;

    case SEG_STRAIGHT_VERTICAL:
      if (fill_side == SIDE_TOP) {
        return SIDE_BOTTOM;
      }
      return SIDE_TOP;

    case SEG_STRAIGHT_HORIZONTAL:
      if (fill_side == SIDE_LEFT) {
        return SIDE_RIGHT;
      }
      return SIDE_LEFT;

    case SEG_STRAIGHT_CROSS:
      switch (fill_side) {
        case SIDE_TOP:
          return SIDE_BOTTOM;
        case SIDE_RIGHT:
          return SIDE_LEFT;
        case SIDE_BOTTOM:
          return SIDE_TOP;
        case SIDE_LEFT:
          return SIDE_RIGHT;
      }
      return SIDE_NONE;

    case SEG_CORNER_TOP_RIGHT:
      if (fill_side == SIDE_TOP) {
        return SIDE_RIGHT;
      }
      return SIDE_TOP;

    case SEG_CORNER_TOP_LEFT:
      if (fill_side == SIDE_LEFT) {
        return SIDE_TOP;
      }
      return SIDE_LEFT;

    case SEG_CORNER_BOTTOM_RIGHT:
      if (fill_side == SIDE_BOTTOM) {
        return SIDE_RIGHT;
      }
      return SIDE_BOTTOM;

    case SEG_CORNER_BOTTOM_LEFT:
      if (fill_side == SIDE_LEFT) {
        return SIDE_BOTTOM;
      }
      return SIDE_LEFT;

    default:
      return SIDE_NONE;
  }
}