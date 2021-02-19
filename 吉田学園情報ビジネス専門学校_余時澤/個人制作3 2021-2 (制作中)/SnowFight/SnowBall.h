#pragma once
#include "DirectX.h"

#define SNOWBALL_MAX_NUM 100
#define MAX_DISTANCE 2000.f
#define SPEED_RADIO 50.f

HRESULT InitSnowBall(void);
void UninitSnowBall(void);
void UpdateSnowBall(void);
void DrawSnowBall(void);
void SetSnowBall(D3DXVECTOR3 pos, D3DXVECTOR3 move);