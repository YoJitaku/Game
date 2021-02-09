//=============================================================================
//
// [Ground.h] Main Game`s Terrain (use meshfield to draw)
// Author : JITAKU YO
//
//=============================================================================
#ifndef _GROUND_H_
#define _GROUND_H_
#include "DirectX.h"

//typedef struct
//{
//	int nRow;
//	int nColumn;
//	POLYGON_3D *pMeshfield;
//	HRESULT InitMeshField(void);
//}MESHFIELD;

#define ROW_NUM 200//çsêî
#define COLUMN_NUM 200//óÒêî
#define MAP_SIZE_X 1000//ïù
#define MAP_SIZE_Y 1000//çÇÇ≥

HRESULT InitGround(void);
void UninitGround(void);
void UpdateGround(void);
void DrawGround(void);

#endif
