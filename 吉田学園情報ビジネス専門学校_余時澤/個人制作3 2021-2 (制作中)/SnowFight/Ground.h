//=============================================================================
//
// [Ground.h] Main Game`s Terrain (use meshfield to draw)
// Author : JITAKU YO
//
//=============================================================================
#ifndef _GROUND_H_
#define _GROUND_H_
#include "DirectX.h"

#define ROW_NUM 200//�s��
#define COLUMN_NUM 200//��
#define MAP_SIZE_X 5200//��
#define MAP_SIZE_Y 5200//����

HRESULT InitGround(void);
void UninitGround(void);
void UpdateGround(void);
void DrawGround(void);

#endif
