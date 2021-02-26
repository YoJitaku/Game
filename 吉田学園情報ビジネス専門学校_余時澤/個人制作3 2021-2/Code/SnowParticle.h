//=============================================================================
//
// [SnowParticle.h]
// Author : JITAKU YO
//
//=============================================================================
#pragma once
#include "DirectX.h"

#define SNOW_TYPE 4
#define PARTICLE_NUM 10000
#define SNOW_RANGE_X 5000
#define SNOW_RANGE_Y 2000
#define SNOW_RANGE_Z 5000
#define FALL_SPEED 100.0f
#define ROT_SPEED 5.0f
#define SNOW_SIZE 2.0f

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	float fFallSpeed;
	float fRotSpeed;
	int TextureIndex;
}SNOWPARTICLE;

typedef struct
{
	D3DXVECTOR3 rot;
	float fWindSpeed;
	float fRotSpeed;
}WIND;

HRESULT InitSnowParticle(void);
void UninitSnowParticle(void);
void UpdateSnowParticle(void);
void DrawSnowParticle(void);