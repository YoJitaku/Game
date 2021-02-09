//=============================================================================
//
// [Player.h]
// Author : Yo Jitaku
//
//=============================================================================
#include "DirectX.h"

#define SPEEDUP (3)
#define SPEEDDOWN (0.2f)
#define PLAYER_NUMBER (1)
#define MAX_PICTURE (3)
typedef struct
{
	int nLife;
	int nPatterAnim = 0;
	int nMoveDistance = 10;
	int nBulletLevel;
	int nBomb;
	D3DXVECTOR3 pos;
	D3DXVECTOR2 size;
	D3DXVECTOR2 acceleration;
	bool bUse, bPlayerInStage1, bPlayerInBoss, bHit;
}PLAYER;

typedef struct
{
	bool bUse;
	D3DXVECTOR3 pos;
	D3DXVECTOR2 size;
	int nPatterAnim = 0;
}GUNFIRE;

typedef struct
{
	bool bUse;
	D3DXVECTOR3 pos;
	D3DXVECTOR2 size;
}BOMB;

HRESULT InitPlayer(void);
void DrawPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void SetPlayer(int stage);
PLAYER *GetPlayer(void);
void SetGunFire(D3DXVECTOR3 pos);
BOMB *GetBomb(void);