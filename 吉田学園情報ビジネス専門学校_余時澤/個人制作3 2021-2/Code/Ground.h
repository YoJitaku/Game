//=============================================================================
//
// [Ground.h] Main Game`s Terrain (use meshfield to draw)
// Author : JITAKU YO
//
//=============================================================================
#ifndef _GROUND_H_
#define _GROUND_H_
#include "DirectX.h"

#define ROW_NUM 200//çsêî
#define COLUMN_NUM 200//óÒêî
#define MAP_SIZE_X 5200//ïù
#define MAP_SIZE_Y 5200//çÇÇ≥

HRESULT InitGround(void);
void UninitGround(void);
void UpdateGround(void);
void DrawGround(void);

#endif
