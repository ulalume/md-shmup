#pragma once

#include <genesis.h>

typedef struct
{
  VDPPlane bg;
  int x;
  int y;
  int velx;
  int vely;
} SimpleBackground;

SimpleBackground *SimpleBackground_create(int paletteIndex, VDPPlane bg, const Image *image, int x, int y, int velx, int vely);
void SimpleBackground_update(SimpleBackground *b);
void SimpleBackground_destroy(SimpleBackground *b);
