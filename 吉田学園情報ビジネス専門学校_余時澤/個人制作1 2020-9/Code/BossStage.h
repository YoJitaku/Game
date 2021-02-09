//=============================================================================
//
// [BossStage.h]
// Author : Yo Jitaku
//
//=============================================================================
#include "DirectX.h"

#define MAX_COMPONENT_BOSS (5)
#define TYPE_BOSS (3)
#define PI (3.14)
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR2 size;
	D3DXVECTOR3 move;
	int nLife, nType, nBulletType;
	bool bUse;
	bool bHit;
}BOSS;

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 oldpos;
	D3DXVECTOR2 size;
	D3DXVECTOR3 move;
	int nType, nBulletType;
	bool bUse;
}BOSSEYE;

void SetBoss(void);
HRESULT InitBoss(void);
void UninitBoss(void);
void UpdateBoss(void);
void DrawBoss(void);
BOSS *GetBoss(void);
BOSSEYE *GetBossEyes(void);
void Spin(D3DXVECTOR3 pos, float fLength, float fRot, int Num);