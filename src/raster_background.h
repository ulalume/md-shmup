#pragma once

#include <genesis.h>

#define TABLE_LEN 224

typedef struct
{
  VDPPlane bg;
  fix16 x[TABLE_LEN];
  int y;
  fix16 velx[TABLE_LEN];
  int vely;
  s16 _x[TABLE_LEN];
} RasterBackground;

RasterBackground *RasterBackground_create(int paletteIndex, VDPPlane bg, const Image *image, fix16 x[TABLE_LEN], int y, fix16 velx[TABLE_LEN], int vely);
void RasterBackground_update();
void RasterBackground_destroy();