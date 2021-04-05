
#include <genesis.h>
#include "stage1_background.h"

#define BG_CELL_WIDTH 64
#define BG_CELL_HEIGHT 32
#define BG_WIDTH (BG_CELL_WIDTH * 8)
#define BG_HEIGHT (BG_CELL_HEIGHT * 8)

Stage1Background *Stage1Background_create(int paletteIndex, const Palette *palette, VDPPlane bg, const MapDefinition *mapDef, int x, int y, int velx, int vely)
{
  SYS_disableInts();
  VDP_setPaletteColor(63, RGB24_TO_VDPCOLOR(0x9292b6));
  VDP_setBackgroundColor(63);

  VDP_setPalette(paletteIndex, palette->data);
  VDP_setPlaneSize(BG_CELL_WIDTH, BG_CELL_HEIGHT, FALSE);
  VDP_loadTileSet(mapDef->tileset, TILE_USERINDEX, DMA);

  Map *map = MAP_create(mapDef, bg, TILE_ATTR_FULL(paletteIndex, FALSE, FALSE, FALSE, TILE_USERINDEX));
  //u16 tilemapBuf[64 * 32 * 2];

  //MAP_getTilemapRect(map, 0, 0, 64, 16, TRUE, tilemapBuf);
  //VDP_setTileMapData(bg, tilemapBuf, 0, 32 * 16, 32, DMA);

  Stage1Background *b = (Stage1Background *)MEM_alloc(sizeof(Stage1Background));
  b->bg = bg;
  b->x = x;
  b->y = y;
  b->velx = velx;
  b->vely = vely;
  b->map = map;
  SYS_enableInts();

  return b;
}
void Stage1Background_update(Stage1Background *b)
{
  b->x = (b->x + b->velx); //+ BG_WIDTH) % BG_WIDTH;
  b->y = (b->y + b->vely); //+ BG_HEIGHT) % BG_HEIGHT;

  MAP_scrollTo(b->map, -b->x, -b->y);
}
void Stage1Background_destroy(Stage1Background *b)
{
  MEM_free(b->map);
  MEM_free(b);
  b = NULL;
}