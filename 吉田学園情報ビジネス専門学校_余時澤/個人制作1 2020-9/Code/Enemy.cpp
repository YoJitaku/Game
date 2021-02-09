//=============================================================================
//
// [Enemy.cpp]
// Author : Yo Jitaku
//
//=============================================================================
#include "Enemy.h"
#include "Player.h"
#include "Bullet.h"
#include "Stage1.h"
#include "Input.h"
#include "Fade.h"

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;//頂点buffのpointer
LPDIRECT3DTEXTURE9 g_pTextureEnemy[MAX_TYPE_ENEMY] = {};//画像のpointer
ENEMY g_aEnemy[MAX_ENEMY];//Enemy最大数
int g_nCntTimeToShot, g_GPINITCNT;//bullet発射の時間count, enemy groupの記録
int g_nCntItem, g_ItemNum;//itemを持ているenemy番号の記録, itemの種類
bool g_aKillGP[6];//enemy group中で、すべてenemyを消滅するの判断

ENEMY *GetEnemy(void)
{
	return &g_aEnemy[0];
}

void SetEnemy(void)
{
	ENEMY *pEnemy;
	pEnemy = &g_aEnemy[0];
	g_nCntTimeToShot = 0;
	g_GPINITCNT = 0;
	//消滅状態の初期化
	for (int nCnt = 0; nCnt < 5; nCnt++) g_aKillGP[nCnt] = false;
	//group enemy AからFまでの設定
	for (int nCntGroupA = 0; nCntGroupA < GPA; nCntGroupA++, pEnemy++)
	{
		pEnemy->pos.x = 1500;
		pEnemy->pos.y = 100 + (float)nCntGroupA * 120;
		pEnemy->pos.z = 0;
		pEnemy->size.x = 30;
		pEnemy->size.y = 30;
		pEnemy->move.x = -2.5;
		pEnemy->move.y = 0;
		pEnemy->nType = 0;
		pEnemy->Item = 0;
		pEnemy->nLife = 2;
	}
	for (int nCntGroupB = 0; nCntGroupB < GPB; nCntGroupB++, pEnemy++)
	{
		pEnemy->pos.x = 1600 + (float)nCntGroupB * 50;
		pEnemy->pos.y = 100 + (float)nCntGroupB * 75;
		pEnemy->pos.z = 0;
		pEnemy->size.x = 30;
		pEnemy->size.y = 30;
		pEnemy->move.x = -2.5;
		pEnemy->move.y = 0;
		pEnemy->nType = 1;
		pEnemy->Item = 0;
		pEnemy->nLife = 3;
	}
	for (int nCntGroupC = 0; nCntGroupC < GPC; nCntGroupC++, pEnemy++)
	{
		if (nCntGroupC < (GPC / 2))
		{
			pEnemy->pos.x = 1600;
			pEnemy->pos.y = 150 + (float)nCntGroupC * 100;
			pEnemy->move.y = 1;
		}
		else
		{
			pEnemy->pos.x = 1800;
			pEnemy->pos.y = 150 + (float)(nCntGroupC - GPC / 2) * 100;
			pEnemy->move.y = -1;
		}
		pEnemy->pos.z = 0;
		pEnemy->size.x = 30;
		pEnemy->size.y = 30;
		pEnemy->move.x = -2.5;
		pEnemy->nType = 2;
		pEnemy->Item = 0;
		pEnemy->nLife = 3;
	}
	for (int nCntGpd = 0; nCntGpd < GPD; nCntGpd++, pEnemy++)
	{
		if (nCntGpd < (GPD / 2))
		{
			pEnemy->pos.x = 500 - (float)nCntGpd * 70;
			pEnemy->pos.y = -30 - (float)nCntGpd * 70;
			pEnemy->move.y = 2;
		}
		else
		{
			pEnemy->pos.x = 500 - (float)(nCntGpd - GPD / 2) * 70;
			pEnemy->pos.y = 830 + (float)(nCntGpd - GPD / 2) * 70;
			pEnemy->move.y = -2;
		}
		pEnemy->size.x = 30;
		pEnemy->size.y = 30;
		pEnemy->move.x = 2;
		pEnemy->nType = 3;
		pEnemy->Item = 0;
		pEnemy->nLife = 4;
	}
	for (int nCntGpe = 0; nCntGpe < GPE; nCntGpe++, pEnemy++)
	{
		pEnemy->pos = RandomPos();
		pEnemy->move = RandomMove(pEnemy->pos);
		pEnemy->nType = rand() % 4;
		pEnemy->size.x = 30;
		pEnemy->size.y = 30;
		pEnemy->Item = 0;
		pEnemy->nLife = 5;
	}
	for (int nCntGpf = 0; nCntGpf < GPF; nCntGpf++, pEnemy++)
	{
		pEnemy->pos = RandomPos();
		pEnemy->move = RandomMove(pEnemy->pos);
		pEnemy->nType = rand() % 4;
		pEnemy->size.x = 30;
		pEnemy->size.y = 30;
		pEnemy->Item = 0;
		pEnemy->nLife = 6;
	}
	g_ItemNum = rand() % 10;//item持ているenemyのランダム
	g_nCntItem = 0;
}

HRESULT InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDeviceEn = GetDevice();
	srand((int)time(0));//ランダム時間seed
	SetEnemy();
	VERTEX_2D *pVtx;
	ENEMY *pEnemy = &g_aEnemy[0];

	D3DXCreateTextureFromFile(pDeviceEn, "data/TEXTURE/EnemyA.png", &g_pTextureEnemy[0]);
	D3DXCreateTextureFromFile(pDeviceEn, "data/TEXTURE/EnemyB.png", &g_pTextureEnemy[1]);
	D3DXCreateTextureFromFile(pDeviceEn, "data/TEXTURE/EnemyC.png", &g_pTextureEnemy[2]);
	D3DXCreateTextureFromFile(pDeviceEn, "data/TEXTURE/EnemyD.png", &g_pTextureEnemy[3]);
	//create vertex buffer
	if (FAILED(pDeviceEn->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffEnemy, NULL))) return E_FAIL;
	
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pVtx += 4, pEnemy++)
	{
		if (nCntEnemy == g_ItemNum)
		{
			if (g_nCntItem < 3)//全部三つ
			{
				pEnemy->Item = 1;//bullet upgrade item
				g_ItemNum += 7;
			}
			else if (g_nCntItem >= 3 && g_nCntItem < 10)//全部七つ
			{
				pEnemy->Item = 2;//Bomb number plusの item
				g_ItemNum += 10;
			}
			g_nCntItem++;
		}

		//全部enemy共同の初期化
		pEnemy->bHit = false;
		pEnemy->bUse = false;

		pVtx[0].pos = D3DXVECTOR3(pEnemy->pos.x - pEnemy->size.x, pEnemy->pos.y - pEnemy->size.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(pEnemy->pos.x + pEnemy->size.x, pEnemy->pos.y - pEnemy->size.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(pEnemy->pos.x - pEnemy->size.x, pEnemy->pos.y + pEnemy->size.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(pEnemy->pos.x + pEnemy->size.x, pEnemy->pos.y + pEnemy->size.y, 0.0f);
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[0].tex = D3DXVECTOR2((float)(0.5 * pEnemy->nPatterAnim), 0.0);
		pVtx[1].tex = D3DXVECTOR2((float)(0.5 * (pEnemy->nPatterAnim + 1)), 0.0);
		pVtx[2].tex = D3DXVECTOR2((float)(0.5 * pEnemy->nPatterAnim), 1.0);
		pVtx[3].tex = D3DXVECTOR2((float)(0.5 * (pEnemy->nPatterAnim + 1)), 1.0);
	}
	g_pVtxBuffEnemy->Unlock();
	return S_OK;
}

void UninitEnemy(void)
{
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
	for (int nCnt = 0; nCnt < MAX_TYPE_ENEMY; nCnt++)
	{
		if (g_pTextureEnemy[nCnt] != NULL)
		{
			g_pTextureEnemy[nCnt]->Release();
			g_pTextureEnemy[nCnt] = NULL;
		}
	}
}

void UpdateEnemy(void)
{
	VERTEX_2D *pVtx;
	ENEMY *pEnemy = &g_aEnemy[0];
	PLAYER *pPlayer = GetPlayer();
	g_nCntTimeToShot++;

	//player登場したら更新処理初め
	if (pPlayer->bPlayerInStage1 == true)
	{
		g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
		//////////////////////////////GPA
		if (g_aKillGP[0] == false && g_GPINITCNT == 0)	
 			InitNewGroupEnemy(GPA, &g_aEnemy[0]);
		for (int nCntGpA = 0; nCntGpA < GPA; nCntGpA++, pVtx += 4, pEnemy++)
		{
			if (g_nCntTimeToShot % 10 == 0)pEnemy->nPatterAnim++;
			if (pEnemy->bUse == true)
			{
				pEnemy->pos.x += pEnemy->move.x;
				if (pEnemy->bHit == true)
				{
					pVtx[0].col = D3DCOLOR_RGBA(242, 38, 19, 255);
					pVtx[1].col = D3DCOLOR_RGBA(242, 38, 19, 255);
					pVtx[2].col = D3DCOLOR_RGBA(242, 38, 19, 255);
					pVtx[3].col = D3DCOLOR_RGBA(242, 38, 19, 255);
					if (g_nCntTimeToShot % 3 == 0) pEnemy->bHit = false;
				}
				else
				{
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				}
				pVtx[0].pos = D3DXVECTOR3(pEnemy->pos.x - pEnemy->size.x, pEnemy->pos.y - pEnemy->size.y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(pEnemy->pos.x + pEnemy->size.x, pEnemy->pos.y - pEnemy->size.y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(pEnemy->pos.x - pEnemy->size.x, pEnemy->pos.y + pEnemy->size.y, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(pEnemy->pos.x + pEnemy->size.x, pEnemy->pos.y + pEnemy->size.y, 0.0f);
				pVtx[0].tex = D3DXVECTOR2((float)(0.5 * pEnemy->nPatterAnim), 0.0);
				pVtx[1].tex = D3DXVECTOR2((float)(0.5 * (pEnemy->nPatterAnim + 1)), 0.0);
				pVtx[2].tex = D3DXVECTOR2((float)(0.5 * pEnemy->nPatterAnim), 1.0);
				pVtx[3].tex = D3DXVECTOR2((float)(0.5 * (pEnemy->nPatterAnim + 1)), 1.0);
				if (pEnemy->pos.x <= 0) pEnemy->bUse = false;
				if (g_nCntTimeToShot % 200 == 0) SetEnemyBullet(pEnemy->pos, D3DXVECTOR3(-10, 0, 0), 0, 1);
			}
		}
		//////////////////////////////GPB
		if (g_GPINITCNT == 1) g_aKillGP[0] = CheckKillGP(GPA, &g_aEnemy[0]);
		if (g_aKillGP[0] == true && g_GPINITCNT == 1)
			InitNewGroupEnemy(GPB, &g_aEnemy[GPA]);
		for (int nCntGpB = 0; nCntGpB < GPB; nCntGpB++, pVtx += 4, pEnemy++)
		{
			if (g_nCntTimeToShot % 30 == 0)pEnemy->nPatterAnim++;
			if (pEnemy->bUse == true)
			{
				pEnemy->pos.x += pEnemy->move.x;
				if (pEnemy->bHit == true)
				{
					pVtx[0].col = D3DCOLOR_RGBA(242, 38, 19, 255);
					pVtx[1].col = D3DCOLOR_RGBA(242, 38, 19, 255);
					pVtx[2].col = D3DCOLOR_RGBA(242, 38, 19, 255);
					pVtx[3].col = D3DCOLOR_RGBA(242, 38, 19, 255);
					if (g_nCntTimeToShot % 3 == 0) pEnemy->bHit = false;
				}
				else
				{
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				}
				pVtx[0].pos = D3DXVECTOR3(pEnemy->pos.x - pEnemy->size.x, pEnemy->pos.y - pEnemy->size.y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(pEnemy->pos.x + pEnemy->size.x, pEnemy->pos.y - pEnemy->size.y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(pEnemy->pos.x - pEnemy->size.x, pEnemy->pos.y + pEnemy->size.y, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(pEnemy->pos.x + pEnemy->size.x, pEnemy->pos.y + pEnemy->size.y, 0.0f);
				pVtx[0].tex = D3DXVECTOR2((float)(0.5 * pEnemy->nPatterAnim), 0.0);
				pVtx[1].tex = D3DXVECTOR2((float)(0.5 * (pEnemy->nPatterAnim + 1)), 0.0);
				pVtx[2].tex = D3DXVECTOR2((float)(0.5 * pEnemy->nPatterAnim), 1.0);
				pVtx[3].tex = D3DXVECTOR2((float)(0.5 * (pEnemy->nPatterAnim + 1)), 1.0);
				if (pEnemy->pos.x <= 0) pEnemy->bUse = false;
				if (g_nCntTimeToShot % 100 == 0)
				{
					D3DXVECTOR3 different = pPlayer->pos - pEnemy->pos;
					float g_fAnglePolygon = atan2f(different.x, different.y);
					SetEnemyBullet(pEnemy->pos, different, g_fAnglePolygon, 2);
				}
			}
		}
		////////////////////////////GPC
		if (g_GPINITCNT == 2) g_aKillGP[1] = CheckKillGP(GPB, &g_aEnemy[GPA]);
		if (g_aKillGP[1] == true && g_GPINITCNT == 2)
 			InitNewGroupEnemy(GPC, &g_aEnemy[GPB + GPA]);
		for (int nCntGpC = 0; nCntGpC < GPC; nCntGpC++, pVtx += 4, pEnemy++)
		{
			if (g_nCntTimeToShot % 20 == 0)pEnemy->nPatterAnim++;
			
			if (pEnemy->bUse == true)
			{
				pEnemy->pos += pEnemy->move;
				if (pEnemy->bHit == true)
				{
					pVtx[0].col = D3DCOLOR_RGBA(242, 38, 19, 255);
					pVtx[1].col = D3DCOLOR_RGBA(242, 38, 19, 255);
					pVtx[2].col = D3DCOLOR_RGBA(242, 38, 19, 255);
					pVtx[3].col = D3DCOLOR_RGBA(242, 38, 19, 255);
					if (g_nCntTimeToShot % 3 == 0) pEnemy->bHit = false;
				}
				else
				{
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				}
				if (g_nCntTimeToShot % 200 == 0)pEnemy->move.y = -pEnemy->move.y;
				pVtx[0].pos = D3DXVECTOR3(pEnemy->pos.x - pEnemy->size.x, pEnemy->pos.y - pEnemy->size.y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(pEnemy->pos.x + pEnemy->size.x, pEnemy->pos.y - pEnemy->size.y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(pEnemy->pos.x - pEnemy->size.x, pEnemy->pos.y + pEnemy->size.y, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(pEnemy->pos.x + pEnemy->size.x, pEnemy->pos.y + pEnemy->size.y, 0.0f);
				pVtx[0].tex = D3DXVECTOR2((float)(0.5 * pEnemy->nPatterAnim), 0.0);
				pVtx[1].tex = D3DXVECTOR2((float)(0.5 * (pEnemy->nPatterAnim + 1)), 0.0);
				pVtx[2].tex = D3DXVECTOR2((float)(0.5 * pEnemy->nPatterAnim), 1.0);
				pVtx[3].tex = D3DXVECTOR2((float)(0.5 * (pEnemy->nPatterAnim + 1)), 1.0);
				if (g_nCntTimeToShot % 150 == 0) SetEnemyBullet(pEnemy->pos, D3DXVECTOR3(-10, 0, 0), 0, 1);
				if (pEnemy->pos.x <= 0) pEnemy->bUse = false;
			}
		}
		////////////////////////////GPD
		if (g_GPINITCNT == 3) g_aKillGP[2] = CheckKillGP(GPC, &g_aEnemy[GPA + GPB]);
		if (g_aKillGP[2] == true && g_GPINITCNT == 3)
			InitNewGroupEnemy(GPD, &g_aEnemy[GPC + GPB + GPA]);
		for (int nCntGpD = 0; nCntGpD < GPD; nCntGpD++, pVtx += 4, pEnemy++)
		{
			if (g_nCntTimeToShot % 20 == 0)pEnemy->nPatterAnim++;
			
			if (pEnemy->bUse == true)
			{
				pEnemy->pos += pEnemy->move;
				if (pEnemy->pos.x > 1100 && (pEnemy->pos.y < 100 || pEnemy->pos.y > 700)) pEnemy->move.y = 0;
				if (pEnemy->pos.x > 1400)
				{
					pEnemy->move.x = 0;
					if (pEnemy->pos.y < 100) pEnemy->move.y = 2;
					else if (pEnemy->pos.y > 700) pEnemy->move.y = -2;
				}
				if (pEnemy->bHit == true)
				{
					pVtx[0].col = D3DCOLOR_RGBA(242, 38, 19, 255);
					pVtx[1].col = D3DCOLOR_RGBA(242, 38, 19, 255);
					pVtx[2].col = D3DCOLOR_RGBA(242, 38, 19, 255);
					pVtx[3].col = D3DCOLOR_RGBA(242, 38, 19, 255);
					if (g_nCntTimeToShot % 3 == 0) pEnemy->bHit = false;
				}
				else
				{
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				}
				pVtx[0].pos = D3DXVECTOR3(pEnemy->pos.x - pEnemy->size.x, pEnemy->pos.y - pEnemy->size.y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(pEnemy->pos.x + pEnemy->size.x, pEnemy->pos.y - pEnemy->size.y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(pEnemy->pos.x - pEnemy->size.x, pEnemy->pos.y + pEnemy->size.y, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(pEnemy->pos.x + pEnemy->size.x, pEnemy->pos.y + pEnemy->size.y, 0.0f);
				pVtx[0].tex = D3DXVECTOR2((float)(0.5 * pEnemy->nPatterAnim), 0.0);
				pVtx[1].tex = D3DXVECTOR2((float)(0.5 * (pEnemy->nPatterAnim + 1)), 0.0);
				pVtx[2].tex = D3DXVECTOR2((float)(0.5 * pEnemy->nPatterAnim), 1.0);
				pVtx[3].tex = D3DXVECTOR2((float)(0.5 * (pEnemy->nPatterAnim + 1)), 1.0);
				if (pEnemy->pos.x <= 0) pEnemy->bUse = false;
				if (g_nCntTimeToShot % 150 == 0)
				{
					D3DXVECTOR3 different = pPlayer->pos - pEnemy->pos;
					float g_fAnglePolygon = atan2f(different.x, different.y);
					SetEnemyBullet(pEnemy->pos, different, g_fAnglePolygon, 2);
				}
			}
		}
		//////////////////////////GPE
		if (g_GPINITCNT == 4) g_aKillGP[3] = CheckKillGP(GPD, &g_aEnemy[GPA + GPB + GPC]);
		if (g_aKillGP[3] == true && g_GPINITCNT == 4)
    		InitNewGroupEnemy(GPE, &g_aEnemy[GPD + GPC + GPB + GPA]);
		for (int nCntGpE = 0; nCntGpE < GPE; nCntGpE++, pVtx += 4, pEnemy++)
		{
			if (g_nCntTimeToShot % 20 == 0)pEnemy->nPatterAnim++;

			if (pEnemy->bUse == true)
			{
				pEnemy->pos += pEnemy->move;
				if (pEnemy->pos.y > 770 || pEnemy->pos.y < 30) pEnemy->move.y = -pEnemy->move.y;
				if (pEnemy->bHit == true)
				{
					pVtx[0].col = D3DCOLOR_RGBA(242, 38, 19, 255);
					pVtx[1].col = D3DCOLOR_RGBA(242, 38, 19, 255);
					pVtx[2].col = D3DCOLOR_RGBA(242, 38, 19, 255);
					pVtx[3].col = D3DCOLOR_RGBA(242, 38, 19, 255);
					if (g_nCntTimeToShot % 3 == 0) pEnemy->bHit = false;
				}
				else
				{
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				}
				pVtx[0].pos = D3DXVECTOR3(pEnemy->pos.x - pEnemy->size.x, pEnemy->pos.y - pEnemy->size.y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(pEnemy->pos.x + pEnemy->size.x, pEnemy->pos.y - pEnemy->size.y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(pEnemy->pos.x - pEnemy->size.x, pEnemy->pos.y + pEnemy->size.y, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(pEnemy->pos.x + pEnemy->size.x, pEnemy->pos.y + pEnemy->size.y, 0.0f);
				pVtx[0].tex = D3DXVECTOR2((float)(0.5 * pEnemy->nPatterAnim), 0.0);
				pVtx[1].tex = D3DXVECTOR2((float)(0.5 * (pEnemy->nPatterAnim + 1)), 0.0);
				pVtx[2].tex = D3DXVECTOR2((float)(0.5 * pEnemy->nPatterAnim), 1.0);
				pVtx[3].tex = D3DXVECTOR2((float)(0.5 * (pEnemy->nPatterAnim + 1)), 1.0);
				if (pEnemy->pos.x <= 0) pEnemy->bUse = false;
				if (g_nCntTimeToShot % 150 == 0)
				{
					if (nCntGpE < GPE / 2) SetEnemyBullet(pEnemy->pos, D3DXVECTOR3((float)(rand() % 5 - 15), 0, 0), 0, 1);
					else
					{
						D3DXVECTOR3 different = pPlayer->pos - pEnemy->pos;
						float g_fAnglePolygon = atan2f(different.x, different.y);
						SetEnemyBullet(pEnemy->pos, different, g_fAnglePolygon, 2);
					}
				}
			}
		}
		////////////////////////////GPF
		if (g_GPINITCNT == 5) g_aKillGP[4] = CheckKillGP(GPE, &g_aEnemy[GPA + GPB + GPC + GPD]);
		if (g_aKillGP[4] == true && g_GPINITCNT == 5)
 			InitNewGroupEnemy(GPF, &g_aEnemy[GPE + GPD + GPC + GPB + GPA]);
		for (int nCntGpF = 0; nCntGpF < GPF; nCntGpF++, pVtx += 4, pEnemy++)
		{
			if (g_nCntTimeToShot % 20 == 0)pEnemy->nPatterAnim++;

			if (pEnemy->bUse == true)
			{
				pEnemy->pos += pEnemy->move;
				if (pEnemy->pos.y > 770 || pEnemy->pos.y < 30) pEnemy->move.y = -pEnemy->move.y;
				if (pEnemy->bHit == true)
				{
					pVtx[0].col = D3DCOLOR_RGBA(242, 38, 19, 255);
					pVtx[1].col = D3DCOLOR_RGBA(242, 38, 19, 255);
					pVtx[2].col = D3DCOLOR_RGBA(242, 38, 19, 255);
					pVtx[3].col = D3DCOLOR_RGBA(242, 38, 19, 255);
					if (g_nCntTimeToShot % 3 == 0) pEnemy->bHit = false;
				}
				else
				{
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				}
				pVtx[0].pos = D3DXVECTOR3(pEnemy->pos.x - pEnemy->size.x, pEnemy->pos.y - pEnemy->size.y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(pEnemy->pos.x + pEnemy->size.x, pEnemy->pos.y - pEnemy->size.y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(pEnemy->pos.x - pEnemy->size.x, pEnemy->pos.y + pEnemy->size.y, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(pEnemy->pos.x + pEnemy->size.x, pEnemy->pos.y + pEnemy->size.y, 0.0f);
				pVtx[0].tex = D3DXVECTOR2((float)(0.5 * pEnemy->nPatterAnim), 0.0);
				pVtx[1].tex = D3DXVECTOR2((float)(0.5 * (pEnemy->nPatterAnim + 1)), 0.0);
				pVtx[2].tex = D3DXVECTOR2((float)(0.5 * pEnemy->nPatterAnim), 1.0);
				pVtx[3].tex = D3DXVECTOR2((float)(0.5 * (pEnemy->nPatterAnim + 1)), 1.0);
				if (pEnemy->pos.x <= 0) pEnemy->bUse = false;
				if (g_nCntTimeToShot % 150 == 0)
				{
					if (nCntGpF < GPF / 2) SetEnemyBullet(pEnemy->pos, D3DXVECTOR3((float)(rand() % 5 - 15), 0, 0), 0, 1);
					else
					{
						D3DXVECTOR3 different = pPlayer->pos - pEnemy->pos;
						float g_fAnglePolygon = atan2f(different.x, different.y);
						SetEnemyBullet(pEnemy->pos, different, g_fAnglePolygon, 2);
					}
				}
			}
		}
		g_pVtxBuffEnemy->Unlock();
		//Next stageへ
		STAGE1 *pStage = GetStage1Next();
		if (g_GPINITCNT == 6) 
			g_aKillGP[5] = CheckKillGP(GPF, &g_aEnemy[GPA + GPB + GPC + GPD + GPE]);
		if (g_aKillGP[5] == true && g_GPINITCNT == 6)
		{
 			pStage->bUse = true;
			if (pPlayer->pos.x >= 1350 && pPlayer->pos.y <= 600 && pPlayer->pos.y >= 400) SetFade(FADE_OUT, MODE_BOSSSTAGE);
		}
	}
}

void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDeviceEn = GetDevice();
	ENEMY *pEnemy = &g_aEnemy[0];
	pDeviceEn->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));//頂点Data flowの設定
	pDeviceEn->SetFVF(FVF_VERTEX_2D);//頂点modの設定
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
	{
		if (pEnemy->bUse == true)
		{
			pDeviceEn->SetTexture(0, g_pTextureEnemy[pEnemy->nType]);//Textureの設定
			pDeviceEn->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnemy * 4, 2);//頂点の描画
		}
	}
}

//次のenemy groupをactivateする
void InitNewGroupEnemy(int GpNumber, ENEMY *pEnemy)
{
	g_GPINITCNT++;
	for (int nCntEn = 0; nCntEn < GpNumber; nCntEn++, pEnemy++) 
		pEnemy->bUse = true;
}

//当然groupのenemyの消滅判断
bool CheckKillGP(int GpNumber, ENEMY *pEnemy)
{
	int nCnt = 0;
	for (int nCntEn = 0; nCntEn < GpNumber; nCntEn++, pEnemy++) if (pEnemy->bUse == false) nCnt++;
	if (nCnt == GpNumber) return true;//全部倒した
	else return false;
}
//enemy group EとFの座標ランダム
D3DXVECTOR3 RandomPos(void)
{
	D3DXVECTOR3 Rpos;
	Rpos.x = 1600;
	Rpos.y = (float)(rand() % 700 + 50);
	Rpos.z = 0;
	return Rpos;
}
//enemy group EとFの移動ランダム
D3DXVECTOR3 RandomMove(D3DXVECTOR3 Rpos)
{
	D3DXVECTOR3 RMove;
	if (Rpos.y > 400) 	RMove.y = (float)(rand() % 30 - 30) / 10;
	else RMove.y = (float)(rand() % 30) / 10;
	RMove.x = (float)(rand() % 30 - 30) / 10 - 1;
	RMove.z = 0;
	return RMove;
}