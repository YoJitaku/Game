//=============================================================================
//
// [BossStage.cpp]
// Author : Yo Jitaku
//
//=============================================================================
#include "BossStage.h"
#include "Fade.h"
#include "Input.h"
#include "Player.h"
#include "Bullet.h"

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBoss = NULL;//頂点buffのpointer
LPDIRECT3DTEXTURE9 g_pTextureBoss[TYPE_BOSS] = {};//画像のpointer
BOSS g_Boss[MAX_COMPONENT_BOSS - 3];//bullet最大数
BOSSEYE g_BossEyes[3];//bosseyes　三つ
int g_nCntTime = 0;//時間count
int g_nCntspin = 0;//回転speedのcount
float g_fAngle[3];//bosseyesの回転角度　三つ
void SetBoss(void)
{
	//background
	g_Boss[0].pos = D3DXVECTOR3(SCREEN_WIDTH * 2, SCREEN_HEIGHT / 2, 0.0f);
	g_Boss[0].size.x = SCREEN_WIDTH * 2;
	g_Boss[0].size.y = SCREEN_HEIGHT / 2;
	g_Boss[0].move.x = -2;
	g_Boss[0].nType = 0;
	g_Boss[0].bUse = true;
	//boss
	g_Boss[1].pos = D3DXVECTOR3(1200, SCREEN_HEIGHT / 2, 0.0f);
	g_Boss[1].size.x = 250;
	g_Boss[1].size.y = 250;
	g_Boss[1].move.x = 0.5;
	g_Boss[1].move.y = 0.5;
	g_Boss[1].nType = 1;
	g_Boss[1].nLife = 250;
	g_Boss[1].bUse = true;
	g_Boss[1].bHit = false;
	//boss eyes
	g_BossEyes[0].pos = D3DXVECTOR3(1000, SCREEN_HEIGHT / 2, 0.0f);
	g_BossEyes[0].oldpos = g_BossEyes[0].pos;
	g_BossEyes[0].size = D3DXVECTOR2(30, 30);
	g_BossEyes[0].nType = 2;
	g_BossEyes[0].move.y = 1;
	g_BossEyes[0].bUse = true;
	g_BossEyes[1].pos = D3DXVECTOR3(1400, SCREEN_HEIGHT / 2, 0.0f);
	g_BossEyes[1].oldpos = g_BossEyes[0].pos;
	g_BossEyes[1].size = D3DXVECTOR2(30, 30);
	g_BossEyes[1].nType = 2;
	g_BossEyes[1].bUse = true;
	g_BossEyes[2].pos = D3DXVECTOR3(1200, 600, 0.0f);
	g_BossEyes[2].oldpos = g_BossEyes[0].pos;
	g_BossEyes[2].size = D3DXVECTOR2(30, 30);
	g_BossEyes[2].nType = 2;
	g_BossEyes[2].bUse = true;
	//bosseyes spin
	g_fAngle[0] = (float)PI;
	g_fAngle[1] = (float)PI * 2;
	g_fAngle[2] = (float)PI * (float)2.5;
}

HRESULT InitBoss(void)
{
	LPDIRECT3DDEVICE9 pDeviceBs = GetDevice();
	VERTEX_2D *pVtx;

	SetPlayer(1);//player posion Init
	SetBoss();//BossInit

	D3DXCreateTextureFromFile(pDeviceBs, "data/TEXTURE/bossstage.png", &g_pTextureBoss[0]);
	D3DXCreateTextureFromFile(pDeviceBs, "data/TEXTURE/Boss.png", &g_pTextureBoss[1]);
	D3DXCreateTextureFromFile(pDeviceBs, "data/TEXTURE/BossEyes.png", &g_pTextureBoss[2]);
	//create vertex buffer
	if (FAILED(pDeviceBs->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_COMPONENT_BOSS, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffBoss, NULL))) return E_FAIL;

	g_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);
	//boss本体
	for (int nCnt = 0; nCnt < MAX_COMPONENT_BOSS - 3; nCnt++, pVtx += 4)
	{
		pVtx[0].pos = D3DXVECTOR3(g_Boss[nCnt].pos.x - g_Boss[nCnt].size.x, g_Boss[nCnt].pos.y - g_Boss[nCnt].size.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Boss[nCnt].pos.x + g_Boss[nCnt].size.x, g_Boss[nCnt].pos.y - g_Boss[nCnt].size.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Boss[nCnt].pos.x - g_Boss[nCnt].size.x, g_Boss[nCnt].pos.y + g_Boss[nCnt].size.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Boss[nCnt].pos.x + g_Boss[nCnt].size.x, g_Boss[nCnt].pos.y + g_Boss[nCnt].size.y, 0.0f);
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[0].tex = D3DXVECTOR2(0.0, 0.0);
		pVtx[1].tex = D3DXVECTOR2(1.0, 0.0);
		pVtx[2].tex = D3DXVECTOR2(0.0, 1.0);
		pVtx[3].tex = D3DXVECTOR2(1.0, 1.0);
	}
	//boss eyes
	for (int nCnt = 0; nCnt < 3; nCnt++, pVtx += 4)
	{
		pVtx[0].pos = D3DXVECTOR3(g_BossEyes[nCnt].pos.x - g_BossEyes[nCnt].size.x, g_BossEyes[nCnt].pos.y - g_BossEyes[nCnt].size.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_BossEyes[nCnt].pos.x + g_BossEyes[nCnt].size.x, g_BossEyes[nCnt].pos.y - g_BossEyes[nCnt].size.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_BossEyes[nCnt].pos.x - g_BossEyes[nCnt].size.x, g_BossEyes[nCnt].pos.y + g_BossEyes[nCnt].size.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_BossEyes[nCnt].pos.x + g_BossEyes[nCnt].size.x, g_BossEyes[nCnt].pos.y + g_BossEyes[nCnt].size.y, 0.0f);
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[0].tex = D3DXVECTOR2(0.0, 0.0);
		pVtx[1].tex = D3DXVECTOR2(1.0, 0.0);
		pVtx[2].tex = D3DXVECTOR2(0.0, 1.0);
		pVtx[3].tex = D3DXVECTOR2(1.0, 1.0);
	}
	g_pVtxBuffBoss->Unlock();
	return S_OK;
}

void UninitBoss(void)
{
	if (g_pVtxBuffBoss != NULL)
	{
		g_pVtxBuffBoss->Release();
		g_pVtxBuffBoss = NULL;
	}
	for (int nCntStage = 0; nCntStage < 3; nCntStage++)
	{
		if (g_pTextureBoss[nCntStage] != NULL)
		{
			g_pTextureBoss[nCntStage]->Release();
			g_pTextureBoss[nCntStage] = NULL;
		}
	}
	g_Boss[1].bUse = false;
}

void UpdateBoss(void)
{
	VERTEX_2D *pVtx;
	BOSS *pBoss = &g_Boss[0];
	PLAYER *pPlayer = GetPlayer();
	BOSSEYE *pBossEyes = &g_BossEyes[0];
	g_nCntTime++;

	if (pPlayer->bPlayerInBoss == true)//player登場したら　update初め
	{
		g_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);
		//bossとbackgroundの移動
		for (int nCnt = 0; nCnt < MAX_COMPONENT_BOSS - 3; nCnt++, pBoss++, pVtx += 4)
		{
			switch (nCnt)
			{
			case 0://background
				pBoss->pos += pBoss->move;
				if (pBoss->pos.x <= -SCREEN_WIDTH) pBoss->pos.x = SCREEN_WIDTH * 2;
				break;
			case 1://boss
				if (pBoss->bUse != false)
				{
					pBoss->pos += pBoss->move;
					if (pBoss->pos.x < 1150 || pBoss->pos.x > 1250) pBoss->move.x = -pBoss->move.x;
					if (pBoss->pos.y < 200 || pBoss->pos.y > 500) pBoss->move.y = -pBoss->move.y;
				}
				if (pBoss->bHit == true)
				{
					pVtx[0].col = D3DCOLOR_RGBA(242, 38, 19, 255);
					pVtx[1].col = D3DCOLOR_RGBA(242, 38, 19, 255);
					pVtx[2].col = D3DCOLOR_RGBA(242, 38, 19, 255);
					pVtx[3].col = D3DCOLOR_RGBA(242, 38, 19, 255);
					if (g_nCntTime % 2 == 0) pBoss->bHit = false;
				}
				else
				{
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				}
				break;
			}
			pVtx[0].pos = D3DXVECTOR3(pBoss->pos.x - pBoss->size.x, pBoss->pos.y - pBoss->size.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(pBoss->pos.x + pBoss->size.x, pBoss->pos.y - pBoss->size.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(pBoss->pos.x - pBoss->size.x, pBoss->pos.y + pBoss->size.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(pBoss->pos.x + pBoss->size.x, pBoss->pos.y + pBoss->size.y, 0.0f);
		}

		//bosseyesの移動とbullet発射
		pBoss = &g_Boss[1];
		int nRandomShot;
		if (g_nCntTime % 100 == 0) nRandomShot = rand() % 3;
		else nRandomShot = 4;
		for (int nCnt = 0; nCnt < 3; nCnt++, pBossEyes++, pVtx += 4)
		{
			switch (nCnt)//三つのeyesにっよて　bulletの種類は違う
			{
			case 0:
				if (pBossEyes->bUse == true)
				{
					Spin(pBoss->pos, 200, (float)PI / 270, 0);
					if (nRandomShot == 0)
					{
						SetEnemyBullet(pBossEyes->pos, D3DXVECTOR3(-8, 0, 0), 0, 1);
						SetEnemyBullet(pBossEyes->pos, D3DXVECTOR3(-8, -2, 0), 0, 1);
						SetEnemyBullet(pBossEyes->pos, D3DXVECTOR3(-8, 2, 0), 0, 1);
						SetEnemyBullet(pBossEyes->pos, D3DXVECTOR3(-8, -4, 0), 0, 1);
						SetEnemyBullet(pBossEyes->pos, D3DXVECTOR3(-8, 4, 0), 0, 1);
						SetEnemyBullet(pBossEyes->pos, D3DXVECTOR3(-8, -6, 0), 0, 1);
						SetEnemyBullet(pBossEyes->pos, D3DXVECTOR3(-8, 6, 0), 0, 1);
						SetEnemyBullet(pBossEyes->pos, D3DXVECTOR3(-8, -8, 0), 0, 1);
						SetEnemyBullet(pBossEyes->pos, D3DXVECTOR3(-8, 8, 0), 0, 1);
						SetEnemyBullet(pBossEyes->pos, D3DXVECTOR3(-8, -10, 0), 0, 1);
						SetEnemyBullet(pBossEyes->pos, D3DXVECTOR3(-8, 10, 0), 0, 1);
					}
				}
				break;
			case 1:
				if (pBossEyes->bUse == true)
				{
					Spin(pBoss->pos, 200, (float)PI / 90, 1);
					if (nRandomShot == 1)
					{
						SetEnemyBullet(pBossEyes->pos, D3DXVECTOR3(-5, 0, 0), 0, 1);
						SetEnemyBullet(pBossEyes->pos, D3DXVECTOR3(-5, -5, 0), 0, 1);
						SetEnemyBullet(pBossEyes->pos, D3DXVECTOR3(-5, 5, 0), 0, 1);
						SetEnemyBullet(pBossEyes->pos, D3DXVECTOR3(-5, -2.5, 0), 0, 1);
						SetEnemyBullet(pBossEyes->pos, D3DXVECTOR3(-5, 2.5, 0), 0, 1);
						SetEnemyBullet(pBossEyes->pos, D3DXVECTOR3(0, -5, 0), 0, 1);
						SetEnemyBullet(pBossEyes->pos, D3DXVECTOR3(0, 5, 0), 0, 1);
						SetEnemyBullet(pBossEyes->pos, D3DXVECTOR3(5, 5, 0), 0, 1);
						SetEnemyBullet(pBossEyes->pos, D3DXVECTOR3(5, -5, 0), 0, 1);
						SetEnemyBullet(pBossEyes->pos, D3DXVECTOR3(5, 2.5, 0), 0, 1);
						SetEnemyBullet(pBossEyes->pos, D3DXVECTOR3(5, -2.5, 0), 0, 1);
						SetEnemyBullet(pBossEyes->pos, D3DXVECTOR3(5, 0, 0), 0, 1);
					}
				}
				break;
			case 2:
				if (pBossEyes->bUse == true)
				{
					Spin(pBoss->pos, 200, (float)PI / 180, 2);
					if (nRandomShot == 2)
					{
						D3DXVECTOR3 different = pPlayer->pos - pBossEyes->pos;
						float g_fAnglePolygon = atan2f(different.x, different.y);
						SetEnemyBullet(pBossEyes->pos, different, g_fAnglePolygon + (float)0.1, 2);
						SetEnemyBullet(pBossEyes->pos, different, g_fAnglePolygon + (float)0.05, 2);
						SetEnemyBullet(pBossEyes->pos, different, g_fAnglePolygon, 2);
						SetEnemyBullet(pBossEyes->pos, different, g_fAnglePolygon - (float)0.05, 2);
						SetEnemyBullet(pBossEyes->pos, different, g_fAnglePolygon - (float)0.1, 2);
					}
				}
				break;
			}
			pVtx[0].pos = D3DXVECTOR3(pBossEyes->pos.x - pBossEyes->size.x, pBossEyes->pos.y - pBossEyes->size.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(pBossEyes->pos.x + pBossEyes->size.x, pBossEyes->pos.y - pBossEyes->size.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(pBossEyes->pos.x - pBossEyes->size.x, pBossEyes->pos.y + pBossEyes->size.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(pBossEyes->pos.x + pBossEyes->size.x, pBossEyes->pos.y + pBossEyes->size.y, 0.0f);
		}
		g_pVtxBuffBoss->Unlock();
	}
}

void DrawBoss(void)
{
	LPDIRECT3DDEVICE9 pDeviceSt1 = GetDevice();
	BOSS *pBoss = &g_Boss[0];
	BOSSEYE *pBossEyes = &g_BossEyes[0];

	pDeviceSt1->SetStreamSource(0, g_pVtxBuffBoss, 0, sizeof(VERTEX_2D));//頂点Data flowの設定
	pDeviceSt1->SetFVF(FVF_VERTEX_2D);//頂点modの設定

	//background and boss本体
	for (int nCntBoss = 0; nCntBoss < MAX_COMPONENT_BOSS - 3; nCntBoss++, pBoss++)
	{
		if (pBoss->bUse == true)
		{
			pDeviceSt1->SetTexture(0, g_pTextureBoss[pBoss->nType]);//Textureの設定
			pDeviceSt1->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBoss * 4, 2);//頂点の描画
		}
	}
	//boss eyes
	for (int nCntBoss = 0; nCntBoss < 3; nCntBoss++, pBoss++)
	{
		if (pBossEyes->bUse == true)
		{
			pDeviceSt1->SetTexture(0, g_pTextureBoss[pBossEyes->nType]);//Textureの設定
			pDeviceSt1->DrawPrimitive(D3DPT_TRIANGLESTRIP, 8 + nCntBoss * 4, 2);//頂点の描画
		}
	}
}

BOSS *GetBoss(void)
{
	return &g_Boss[1];
}

BOSSEYE *GetBossEyes(void)
{
	return &g_BossEyes[0];
}

//bosseyesの回転処理
void Spin(D3DXVECTOR3 pos, float fLength, float fRot, int Num)
{
	BOSSEYE *pBossEyes = &g_BossEyes[Num];
	g_fAngle[Num] += fRot;
	pBossEyes->pos.x = pos.x + fLength * cos(g_fAngle[Num]);
	pBossEyes->pos.y = pos.y + fLength * sin(g_fAngle[Num]);
	pBossEyes->pos.z = 0.0f;
}