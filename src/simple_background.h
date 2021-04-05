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

SimpleBackground *Background_create(int pallette, VDPPlane bg, Image *image, int x, int y, int velx, int vely);
void Background_update(SimpleBackground *b);
void Background_destroy(SimpleBackground *b);

#endif // _SIMPLE_BACKGROUND_H_