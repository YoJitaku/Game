//=============================================================================
//
// [Explosion.h]
// Author : JITAKU YO
//
//=============================================================================
#pragma once
#include "DirectX.h"

#define EXPLOSION_PARTICLE_NUM 20

void SetExplosion(D3DXVECTOR3 pos);
HRESULT InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);