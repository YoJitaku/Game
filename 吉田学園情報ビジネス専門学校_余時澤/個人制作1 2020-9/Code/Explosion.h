//=============================================================================
//
// [Explosion.h]
// Author : Yo Jitaku
//
//=============================================================================
#include "DirectX.h"

#define EXPLOSION_NUMBER (30)
typedef struct
{
	D3DXVECTOR3 pos;
	int nPatterAnim, nsize;
	bool bUse = false;
}EXPLOSION;

HRESULT InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
void SetExplosion(D3DXVECTOR3 pos, int size);