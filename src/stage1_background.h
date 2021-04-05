#ifndef _STAGE1_BACKGROUND_H_
#define _STAGE1_BACKGROUND_H_

#include <genesis.h>

typedef struct
{
  VDPPlane bg;
  int x;
  int y;
  int velx;
  int vely;
  Map *map;
} Stage1Background;

Stage1Background *Stage1Background_create(int paletteIndex, const Palette *palette, VDPPlane bg, const MapDefinition *mapDef, int x, int y, int velx, int vely);
void Stage1Background_update(Stage1Background *b);
void Stage1Background_destroy(Stage1Background *b);

#endif // _STAGE1_BACKGROUND_H_