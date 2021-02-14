//=============================================================================
//
// [polyblock.h]Å@
// Author : Yo Jitaku
//
//=============================================================================
#pragma once
#include "DirectX.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BLOCK_TEXTURE (18)
#define DEFAULT_WIDTH (96)
#define DEFAULT_HEIGHT (108)
#define MAP_DATA_ROW 20
#define MAP_DATA_COLUMN 500
#define POLYGON_STAGE_1 2//title
#define POLYGON_STAGE_2 39//menu 
#define POLYGON_STAGE_3 1//handbook 
#define POLYGON_STAGE_4 421//stage1 
#define POLYGON_STAGE_5 441//stage2 
#define POLYGON_STAGE_6 1//rank
#define DOOR_NUM 2
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXVECTOR2 size;
	int nMoveType, nMoveRange, nTextureID, nAnime, nDoorID;
	bool bUse, bBlock, bAnime;
}POLYGON;



void LOOPTOREAD(FILE *pFile);
void ReadFile(int nStage);
void SetPolygon(int nStage);
HRESULT InitPolyBlock(int nStage);
void UninitPolyBlock(int nStage);
void UpdatePolyBlock(int nStage);
void DrawPolyBlock(int nStage);
POLYGON *GetPolyBlock(void);
int PolyNum(int nStage);
D3DXVECTOR2 *GetAllMove(void);
int *MapData(void);