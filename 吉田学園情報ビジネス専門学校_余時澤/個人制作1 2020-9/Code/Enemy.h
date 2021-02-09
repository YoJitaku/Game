//=============================================================================
//
// [Enemy.h]
// Author : Yo Jitaku
//
//=============================================================================
#include "DirectX.h"

#define MAX_TYPE_ENEMY (4)
#define GPA (6)
#define GPB (8)
#define GPC (12)
#define GPD (14)
#define GPE (10)
#define GPF (15)
#define MAX_ENEMY (256)

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR2 size;
	D3DXVECTOR3 move;
	int nType, nPatterAnim = 0, Item, nLife;
	bool bUse = false;
	bool bHit;
}ENEMY;

HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, int nType);
ENEMY *GetEnemy(void);
void InitNewGroupEnemy(int GpNumber, ENEMY *pEnemy);
bool CheckKillGP(int GpNumber, ENEMY *pEnemy);
D3DXVECTOR3 RandomPos(void); 
D3DXVECTOR3 RandomMove(D3DXVECTOR3 Rpos);