//=============================================================================
//
// [Bullet.h]
// Author : Yo Jitaku
//
//=============================================================================
#include "DirectX.h"

#define BULLET_TEXTURE (3)
#define PLAYER_BULLET_NUMBER (256)
#define ENEMY_BULLET_NUMBER (256)

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXVECTOR2 size;
	int nType, nLevel = 0;//nBasexÇÕèâä˙ç¿ïWÇÃyíl
	bool bUse;
	float fAngle = 0;
}BULLET;

HRESULT InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife);
void SetEnemyBullet(D3DXVECTOR3 pos, D3DXVECTOR3 aim, float fAngle, int nType);