//=============================================================================
//
// [Enemy.h]
// Author : JITAKU YO
//
//=============================================================================
#pragma once
#include "DirectX.h"

#define ENEMY_NUM 50
#define ENEMY_BORN_RANGE 4000

HRESULT InitEnemyMenu(void);
HRESULT InitEnemy(void);
void UninitEnemy(void);
void UninitEnemyM(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void DrawEnemyM(void);
void SetEnemy(void);
MODEL *GetEnemy(void);