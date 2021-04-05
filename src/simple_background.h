#ifndef _SIMPLE_BACKGROUND_H_
#define _SIMPLE_BACKGROUND_H_

#include <genesis.h>

typedef struct
{
  VDPPlane bg;
  int x;
  int y;
  int velx;
  int vely;
} SimpleBackground;

SimpleBackground *SimpleBackground_create(int pallette, VDPPlane bg, const Image *image, int x, int y, int velx, int vely);
void SimpleBackground_update(SimpleBackground *b);
void SimpleBackground_destroy(SimpleBackground *b);

#endif // _SIMPLE_BACKGROUND_H_