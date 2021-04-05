
#include "simple_background.h"

SimpleBackground *Background_create(int pallette, VDPPlane bg, Image *image, int x, int y, int velx, int vely)
{
  VDP_loadTileSet(image->tileset, 1, DMA);

  int i = 0;
  int thex = 0;
  int they = 0;
  int val = 1;
  for (i = 0; i < 1280; i++)
  {
    thex = i % 40;
    they = i / 40;

    val = (random() % (10 - 1 + 1)) + 1;
    if (val > 3)
      val = 1;

    VDP_setTileMapXY(bg, TILE_ATTR_FULL(pallette, 0, 0, 0, val), thex, they);
  }
  SimpleBackground *b = (SimpleBackground *)MEM_alloc(sizeof(SimpleBackground));
  b->bg = bg;
  b->x = x;
  b->y = y;
  b->velx = velx;
  b->vely = vely;

  return b;
}
void Background_update(SimpleBackground *b)
{
  b->x = (b->x + b->velx + 256) % 256;
  b->y = (b->y + b->vely + 256) % 256;
  VDP_setHorizontalScroll(b->bg, b->x);
  VDP_setVerticalScroll(b->bg, b->y);
}
void Background_destroy(SimpleBackground *b)
{
  MEM_free(b);
  b = NULL;
}