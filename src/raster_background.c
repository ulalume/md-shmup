
#include "raster_background.h"

#define BG_CELL_WIDTH 64
#define BG_CELL_HEIGHT 32
#define BG_WIDTH (BG_CELL_WIDTH * 8)
#define BG_HEIGHT (BG_CELL_HEIGHT * 8)

RasterBackground *rasterBackground;

static void RasterBackground_vint()
{
  VDP_setHorizontalScrollLine(rasterBackground->bg, 0, rasterBackground->_x, TABLE_LEN, TRUE);
}

RasterBackground *RasterBackground_create(int paletteIndex, VDPPlane bg, const Image *image, fix16 x[TABLE_LEN], int y, fix16 velx[TABLE_LEN], int vely)
{
  RasterBackground_destroy(rasterBackground);

  SYS_disableInts();

  VDP_setPalette(paletteIndex, image->palette->data);
  VDP_loadTileSet(image->tileset, 1, DMA);
  VDP_setPlaneSize(BG_CELL_WIDTH, BG_CELL_HEIGHT, FALSE);

  VDP_setScrollingMode(HSCROLL_LINE, VSCROLL_PLANE);
  SYS_setVIntCallback(&RasterBackground_vint);

  int i = 0;
  int thex = 0;
  int they = 0;
  int val = 1;
  for (i = 0; i < BG_CELL_WIDTH * BG_CELL_HEIGHT; i += 1)
  {
    thex = i % BG_CELL_WIDTH;
    they = i / BG_CELL_WIDTH;

    val = (random() % (10 - 1 + 1)) + 1;
    if (val > 3)
      val = 1;

    VDP_setTileMapXY(bg, TILE_ATTR_FULL(paletteIndex, 0, 0, 0, val), thex, they);
  }

  SYS_enableInts();
  RasterBackground *b = (RasterBackground *)MEM_alloc(sizeof(RasterBackground));

  b->bg = bg;
  for (i = 0; i < TABLE_LEN; i++)
  {
    b->x[i] = x[i];
    b->velx[i] = velx[i];
  }
  b->y = y;
  b->vely = vely;

  rasterBackground = b;
  return b;
}
void RasterBackground_update(RasterBackground *b)
{
  for (int i = 0; i < TABLE_LEN; i++)
  {
    b->x[i] += b->velx[i];
    b->_x[i] = fix16ToInt(b->x[i]) & 0x1FF;
  }
  b->y = (b->y + b->vely + BG_HEIGHT) % BG_HEIGHT;
  VDP_setVerticalScroll(b->bg, b->y);
}

void RasterBackground_destroy(RasterBackground *b)
{
  SYS_setVIntCallback(NULL);
  if (b != NULL)
  {
    MEM_free(b);
    b = NULL;
  }
}