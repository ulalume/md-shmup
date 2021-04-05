
#include "simple_background.h"

#define BG_TILE_WIDTH 64
#define BG_TILE_HEIGHT 32
#define BG_WIDTH 512
#define BG_HEIGHT 256

SimpleBackground *Background_create(int pallette, VDPPlane bg, const Image *image, int x, int y, int velx, int vely)
{
  VDP_loadTileSet(image->tileset, 1, DMA);
  VDP_setPlaneSize(BG_TILE_WIDTH, BG_TILE_HEIGHT, FALSE);

  int i = 0;
  int thex = 0;
  int they = 0;
  int val = 1;
  for (i = 0; i < BG_TILE_WIDTH * BG_TILE_HEIGHT; i += 1)
  {
    thex = i % BG_TILE_WIDTH;
    they = i / BG_TILE_WIDTH;

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
  b->x = (b->x + b->velx + BG_WIDTH) % BG_WIDTH;
  b->y = (b->y + b->vely + BG_HEIGHT) % BG_HEIGHT;
  VDP_setHorizontalScroll(b->bg, b->x);
  VDP_setVerticalScroll(b->bg, b->y);
}
void Background_destroy(SimpleBackground *b)
{
  MEM_free(b);
  b = NULL;
}