//=============================================================================
//
// [Player.cpp]
// Author : Yo Jitaku
//
//=============================================================================
#include "player.h"
#include "Input.h"
#include <cmath>
#include "Bullet.h"
#include "Fade.h"
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;//頂点buffのpointer
LPDIRECT3DTEXTURE9 g_pTexturePlayer[MAX_PICTURE] = {};//画像のpointer
PLAYER g_aPlayer[PLAYER_NUMBER];//1 player
int g_nCntAnimePlayer = 0, g_nCntPlayerHit = 0;//時間count
GUNFIRE g_GunFire;//gunfire effect
BOMB g_Bomb[1];//bomb effect

void SetPlayer(int stage)
{
	//stageにっよてplayerの登場違う
	if (stage == 0)
	{
		g_aPlayer[0].pos = D3DXVECTOR3(300, -100, 0.0f);
		g_aPlayer[0].bPlayerInStage1 = false;
		g_aPlayer[0].bPlayerInBoss = true;
		g_aPlayer[0].size.x = 50;
		g_aPlayer[0].size.y = 50;
		g_aPlayer[0].bUse = true;
		g_aPlayer[0].nLife = 3;
		g_aPlayer[0].nBulletLevel = 0;
		g_aPlayer[0].nBomb = 3;
		g_aPlayer[0].bHit = false;
	}
	else if (stage == 1)
	{
		g_aPlayer[0].pos = D3DXVECTOR3(-100 , SCREEN_HEIGHT / 2, 0.0f);
		g_aPlayer[0].bPlayerInBoss = false;
	}
}

//gunfire effect
void SetGunFire(D3DXVECTOR3 pos)
{
	g_GunFire.pos.x = pos.x + g_aPlayer[0].size.x + 50;
	g_GunFire.pos.y = pos.y - 10;
	g_GunFire.pos.z = pos.z;
	g_GunFire.size = D3DXVECTOR2(100, 100);
	g_GunFire.bUse = true;
}

//bomb effect
void SetBomb(D3DXVECTOR3 pos)
{
	g_Bomb[0].pos = pos;
	g_Bomb[0].size = D3DXVECTOR2(100, 100);
	g_Bomb[0].bUse = false;
}

HRESULT InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevicePy = GetDevice();
	VERTEX_2D *pVtx;
	BOMB *pBomb = &g_Bomb[0];

	//初期化
	SetPlayer(0);//最初はstage0から
	SetGunFire(D3DXVECTOR3(100 ,100 ,0));
	g_GunFire.bUse = false;
	SetBomb(g_aPlayer[0].pos);

	D3DXCreateTextureFromFile(pDevicePy, "data/TEXTURE/PlayerStop.png", &g_pTexturePlayer[0]);
	D3DXCreateTextureFromFile(pDevicePy, "data/TEXTURE/Gunfire1.png", &g_pTexturePlayer[1]);
	D3DXCreateTextureFromFile(pDevicePy, "data/TEXTURE/Effect.png", &g_pTexturePlayer[2]);
	//create vertex buffer
	if (FAILED(pDevicePy->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 3, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffPlayer, NULL))) return E_FAIL;
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
	//player
	pVtx[0].pos = D3DXVECTOR3(g_aPlayer[0].pos.x - g_aPlayer[0].size.x, g_aPlayer[0].pos.y - g_aPlayer[0].size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aPlayer[0].pos.x + g_aPlayer[0].size.x, g_aPlayer[0].pos.y - g_aPlayer[0].size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aPlayer[0].pos.x - g_aPlayer[0].size.x, g_aPlayer[0].pos.y + g_aPlayer[0].size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aPlayer[0].pos.x + g_aPlayer[0].size.x, g_aPlayer[0].pos.y + g_aPlayer[0].size.y, 0.0f);
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[0].tex = D3DXVECTOR2((float)(0.25 * g_aPlayer->nPatterAnim), 0.0);
	pVtx[1].tex = D3DXVECTOR2((float)(0.25 * (g_aPlayer->nPatterAnim + 1)), 0.0);
	pVtx[2].tex = D3DXVECTOR2((float)(0.25 * g_aPlayer->nPatterAnim), 1.0);
	pVtx[3].tex = D3DXVECTOR2((float)(0.25 * (g_aPlayer->nPatterAnim + 1)), 1.0);
	//gunfire
	pVtx[4].pos = D3DXVECTOR3(g_GunFire.pos.x - g_GunFire.size.x, g_GunFire.pos.y - g_GunFire.size.y, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(g_GunFire.pos.x + g_GunFire.size.x, g_GunFire.pos.y - g_GunFire.size.y, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(g_GunFire.pos.x - g_GunFire.size.x, g_GunFire.pos.y + g_GunFire.size.y, 0.0f);
	pVtx[7].pos = D3DXVECTOR3(g_GunFire.pos.x + g_GunFire.size.x, g_GunFire.pos.y + g_GunFire.size.y, 0.0f);
	pVtx[4].rhw = 1.0f;
	pVtx[5].rhw = 1.0f;
	pVtx[6].rhw = 1.0f;
	pVtx[7].rhw = 1.0f;
	pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[4].tex = D3DXVECTOR2((float)(0.5 * g_GunFire.nPatterAnim), 0.0);
	pVtx[5].tex = D3DXVECTOR2((float)(0.5 * (g_GunFire.nPatterAnim + 1)), 0.0);
	pVtx[6].tex = D3DXVECTOR2((float)(0.5 * g_GunFire.nPatterAnim), 1.0);
	pVtx[7].tex = D3DXVECTOR2((float)(0.5 * (g_GunFire.nPatterAnim + 1)), 1.0);
	//bomb
	pVtx[8].pos = D3DXVECTOR3(pBomb->pos.x - pBomb->size.x, pBomb->pos.y - pBomb->size.y, 0.0f);
	pVtx[9].pos = D3DXVECTOR3(pBomb->pos.x + pBomb->size.x, pBomb->pos.y - pBomb->size.y, 0.0f);
	pVtx[10].pos = D3DXVECTOR3(pBomb->pos.x - pBomb->size.x, pBomb->pos.y + pBomb->size.y, 0.0f);
	pVtx[11].pos = D3DXVECTOR3(pBomb->pos.x + pBomb->size.x, pBomb->pos.y + pBomb->size.y, 0.0f);
	pVtx[8].rhw = 1.0f;
	pVtx[9].rhw = 1.0f;
	pVtx[10].rhw = 1.0f;
	pVtx[11].rhw = 1.0f;
	pVtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 150);
	pVtx[9].col = D3DCOLOR_RGBA(255, 255, 255, 150);
	pVtx[10].col = D3DCOLOR_RGBA(255, 255, 255, 150);
	pVtx[11].col = D3DCOLOR_RGBA(255, 255, 255, 150);
	pVtx[8].tex = D3DXVECTOR2(0.0, 0.0);
	pVtx[9].tex = D3DXVECTOR2(1.0, 0.0);
	pVtx[10].tex = D3DXVECTOR2(0.0, 1.0);
	pVtx[11].tex = D3DXVECTOR2(1.0, 1.0);

	g_pVtxBuffPlayer->Unlock();
	return S_OK;
}

void UninitPlayer(void)
{
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
	for (int nCntPlayer = 0; nCntPlayer < MAX_PICTURE; nCntPlayer++)
	{
		if (g_pTexturePlayer[nCntPlayer] != NULL)
		{
			g_pTexturePlayer[nCntPlayer]->Release();
			g_pTexturePlayer[nCntPlayer] = NULL;
		}
	}
}

void UpdatePlayer(void)
{
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevicePy = GetDevice();
	PLAYER *pPlayer = &g_aPlayer[0];
	GUNFIRE *pGunfire = &g_GunFire;
	BOMB *pBomb = &g_Bomb[0];
	g_nCntAnimePlayer++;

	//player stage0で登場処理
	if (pPlayer->bPlayerInStage1 == false)
	{
		pPlayer->pos.y += 5;
		if (pPlayer->pos.y >= SCREEN_HEIGHT / 2) pPlayer->bPlayerInStage1 = true;
	}
	//player bossStageで登場処理
	else if (pPlayer->bPlayerInBoss == false)
	{
		pPlayer->pos.x += 5;
		if (pPlayer->pos.x >= 350) pPlayer->bPlayerInBoss = true;
	}
	else//playerのupdate
	{
		//move limit screen内の限り
		if (pPlayer->pos.y < 0)  pPlayer->pos.y = 0;
		if (pPlayer->pos.y > SCREEN_HEIGHT) pPlayer->pos.y = SCREEN_HEIGHT;
		if (pPlayer->pos.x < 0) pPlayer->pos.x = 0;
		if (pPlayer->pos.x > SCREEN_WIDTH) pPlayer->pos.x = SCREEN_WIDTH;
		//keyboard reaction
		if (GetkeyboardPress(DIK_RIGHT) == true)
		{
			if (GetkeyboardPress(DIK_UP) == true)//RIGHT,UP 斜め移動
			{
 				pPlayer->acceleration.y -= SPEEDUP;
				pPlayer->acceleration.x += SPEEDUP;
				if (pPlayer->acceleration.y <= -(sinf(D3DX_PI / 4) * pPlayer->nMoveDistance)) pPlayer->acceleration.y = -(sinf(D3DX_PI / 4) * pPlayer->nMoveDistance);//speed limit
				if (pPlayer->acceleration.x >= (cosf(D3DX_PI / 4) * pPlayer->nMoveDistance)) pPlayer->acceleration.x = (cosf(D3DX_PI / 4) * pPlayer->nMoveDistance);//speed limit
			}
			else if (GetkeyboardPress(DIK_DOWN) == true)//RIGHT,DOWN 斜め移動
			{
				pPlayer->acceleration.y += SPEEDUP;
				pPlayer->acceleration.x += SPEEDUP;
				if (pPlayer->acceleration.y >= (sinf(D3DX_PI / 4) * pPlayer->nMoveDistance)) pPlayer->acceleration.y = (sinf(D3DX_PI / 4) * pPlayer->nMoveDistance);//speed limit
				if (pPlayer->acceleration.x >= (cosf(D3DX_PI / 4) * pPlayer->nMoveDistance)) pPlayer->acceleration.x = (cosf(D3DX_PI / 4) * pPlayer->nMoveDistance);//speed limit
			}
			else
			{
				pPlayer->acceleration.x += SPEEDUP;//RIGHT　移動
				if (pPlayer->acceleration.x >= pPlayer->nMoveDistance) pPlayer->acceleration.x = (float)pPlayer->nMoveDistance;//speed limit
			}
		}
		else if (GetkeyboardPress(DIK_LEFT) == true)
		{
			if (GetkeyboardPress(DIK_UP) == true)//LEFT,UP 斜め移動
			{
				pPlayer->acceleration.y -= SPEEDUP;
				pPlayer->acceleration.x -= SPEEDUP;
				if (pPlayer->acceleration.y <= -(sinf(D3DX_PI / 4) * pPlayer->nMoveDistance)) pPlayer->acceleration.y = -(sinf(D3DX_PI / 4) * pPlayer->nMoveDistance);//speed limit
				if (pPlayer->acceleration.x <= -(cosf(D3DX_PI / 4) * pPlayer->nMoveDistance)) pPlayer->acceleration.x = -(cosf(D3DX_PI / 4) * pPlayer->nMoveDistance);//speed limit
			}
			else if (GetkeyboardPress(DIK_DOWN) == true)//LEFT,DOWN 斜め移動
			{
				pPlayer->acceleration.y += SPEEDUP;
				pPlayer->acceleration.x -= SPEEDUP;
				if (pPlayer->acceleration.y >= (sinf(D3DX_PI / 4) * pPlayer->nMoveDistance)) pPlayer->acceleration.y = (sinf(D3DX_PI / 4) * pPlayer->nMoveDistance);//speed limit
				if (pPlayer->acceleration.x <= -(cosf(D3DX_PI / 4) * pPlayer->nMoveDistance)) pPlayer->acceleration.x = -(cosf(D3DX_PI / 4) * pPlayer->nMoveDistance);//speed limit
			}
			else
			{
				pPlayer->acceleration.x -= SPEEDUP;//LEFT　移動
				if (pPlayer->acceleration.x <= -pPlayer->nMoveDistance) pPlayer->acceleration.x = (float)-pPlayer->nMoveDistance;//speed limit
			}
		}
		else if (GetkeyboardPress(DIK_UP) == true)
		{
			pPlayer->acceleration.y -= SPEEDUP;//UP　移動
			if (pPlayer->acceleration.y <= -pPlayer->nMoveDistance) pPlayer->acceleration.y = (float)-pPlayer->nMoveDistance;//speed limit
		}
		else if (GetkeyboardPress(DIK_DOWN) == true)
		{
			pPlayer->acceleration.y += SPEEDUP;//DOWN　移動
			if (pPlayer->acceleration.y >= pPlayer->nMoveDistance) pPlayer->acceleration.y = (float)pPlayer->nMoveDistance;//speed limit
		}
		if (GetkeyboardTrigger(DIK_Z) == true)//bulletを発射
		{
			pGunfire->bUse = true;
			switch (pPlayer->nBulletLevel)//bullet level
			{
			case 0:
				SetBullet(D3DXVECTOR3(pPlayer->pos.x, pPlayer->pos.y - 10, 0.0f), D3DXVECTOR3(30, 0.0f, 0.0f), 100);
				break;
			case 1:
				SetBullet(D3DXVECTOR3(pPlayer->pos.x, pPlayer->pos.y - 20, 0.0f), D3DXVECTOR3(30, 0.0f, 0.0f), 100);
				SetBullet(D3DXVECTOR3(pPlayer->pos.x, pPlayer->pos.y, 0.0f), D3DXVECTOR3(30, 0.0f, 0.0f), 100);
				break;
			case 2:
				SetBullet(D3DXVECTOR3(pPlayer->pos.x, pPlayer->pos.y - 20, 0.0f), D3DXVECTOR3(30, 0.0f, 0.0f), 100);
				SetBullet(D3DXVECTOR3(pPlayer->pos.x, pPlayer->pos.y, 0.0f), D3DXVECTOR3(30, 0.0f, 0.0f), 100);
				SetBullet(D3DXVECTOR3(pPlayer->pos.x - 10, pPlayer->pos.y - 25, 0.0f), D3DXVECTOR3(30, -10, 0.0f), 100);
				SetBullet(D3DXVECTOR3(pPlayer->pos.x - 10, pPlayer->pos.y + 5, 0.0f), D3DXVECTOR3(30, 10, 0.0f), 100);
				break;
			case 3:
				SetBullet(D3DXVECTOR3(pPlayer->pos.x, pPlayer->pos.y - 10, 0.0f), D3DXVECTOR3(30, 0.0f, 0.0f), 100);
				SetBullet(D3DXVECTOR3(pPlayer->pos.x, pPlayer->pos.y - 30, 0.0f), D3DXVECTOR3(30, 0.0f, 0.0f), 100);
				SetBullet(D3DXVECTOR3(pPlayer->pos.x, pPlayer->pos.y + 10, 0.0f), D3DXVECTOR3(30, 0.0f, 0.0f), 100);
				SetBullet(D3DXVECTOR3(pPlayer->pos.x - 10, pPlayer->pos.y - 15, 0.0f), D3DXVECTOR3(30, -5, 0.0f), 100);
				SetBullet(D3DXVECTOR3(pPlayer->pos.x - 10, pPlayer->pos.y - 5, 0.0f), D3DXVECTOR3(30, 5, 0.0f), 100);
				SetBullet(D3DXVECTOR3(pPlayer->pos.x - 20, pPlayer->pos.y - 35, 0.0f), D3DXVECTOR3(30, -5, 0.0f), 100);
				SetBullet(D3DXVECTOR3(pPlayer->pos.x - 20, pPlayer->pos.y + 15, 0.0f), D3DXVECTOR3(30, 5, 0.0f), 100);
				break;
			}	
		}
		if (GetkeyboardTrigger(DIK_X) == true)//bombを使用する
		{
			if (pPlayer->nBomb > 0 && pBomb->bUse == false)
			{
				SetBomb(pPlayer->pos);
				pBomb->bUse = true;
				pPlayer->nBomb--;
			}
		}
	}

	//Update finally set
	pPlayer->acceleration.x += (0.0f - pPlayer->acceleration.x) * SPEEDDOWN;//加速度
	pPlayer->acceleration.y += (0.0f - pPlayer->acceleration.y) * SPEEDDOWN;//加速度
	pPlayer->pos.x += pPlayer->acceleration.x;//加速度
	pPlayer->pos.y += pPlayer->acceleration.y;//加速度
	if (g_nCntAnimePlayer % 10 == 0)pPlayer->nPatterAnim++;//player animation
	if (g_nCntAnimePlayer % 4 == 0)pGunfire->nPatterAnim++;//gunfire animation

	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
	//player get hit
	if (pPlayer->bHit == true && g_nCntAnimePlayer % 2 == 0)
	{
		pVtx[0].col = D3DCOLOR_RGBA(240, 52, 52, 150);
		pVtx[1].col = D3DCOLOR_RGBA(240, 52, 52, 150);
		pVtx[2].col = D3DCOLOR_RGBA(240, 52, 52, 150);
		pVtx[3].col = D3DCOLOR_RGBA(240, 52, 52, 150);
		if (g_nCntAnimePlayer % 10 == 0)
		{
			g_nCntPlayerHit++;
			if (g_nCntPlayerHit == 15)//原状回復
			{
				pPlayer->bHit = false;
				g_nCntPlayerHit = 0;
			}
		}
	}
	else if (pPlayer->bHit == true && g_nCntAnimePlayer % 2 != 0)
	{
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
	else
	{
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}

	pVtx[0].pos = D3DXVECTOR3(pPlayer->pos.x - pPlayer->size.x, pPlayer->pos.y - pPlayer->size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pPlayer->pos.x + pPlayer->size.x, pPlayer->pos.y - pPlayer->size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pPlayer->pos.x - pPlayer->size.x, pPlayer->pos.y + pPlayer->size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pPlayer->pos.x + pPlayer->size.x, pPlayer->pos.y + pPlayer->size.y, 0.0f);
	pVtx[0].tex = D3DXVECTOR2((float)(0.25 * pPlayer->nPatterAnim), 0.0);
	pVtx[1].tex = D3DXVECTOR2((float)(0.25 * (pPlayer->nPatterAnim + 1)), 0.0);
	pVtx[2].tex = D3DXVECTOR2((float)(0.25 * pPlayer->nPatterAnim), 1.0);
	pVtx[3].tex = D3DXVECTOR2((float)(0.25 * (pPlayer->nPatterAnim + 1)), 1.0);

	//gunfire pos update
	if (pGunfire->bUse == true)
	{
		SetGunFire(D3DXVECTOR3(pPlayer->pos.x, pPlayer->pos.y, 0.0f));
		pVtx[4].pos = D3DXVECTOR3(pGunfire->pos.x - pGunfire->size.x, pGunfire->pos.y - pGunfire->size.y, 0.0f);
		pVtx[5].pos = D3DXVECTOR3(pGunfire->pos.x + pGunfire->size.x, pGunfire->pos.y - pGunfire->size.y, 0.0f);
		pVtx[6].pos = D3DXVECTOR3(pGunfire->pos.x - pGunfire->size.x, pGunfire->pos.y + pGunfire->size.y, 0.0f);
		pVtx[7].pos = D3DXVECTOR3(pGunfire->pos.x + pGunfire->size.x, pGunfire->pos.y + pGunfire->size.y, 0.0f);
		pVtx[4].tex = D3DXVECTOR2((float)(0.25 * pGunfire->nPatterAnim), 0.0);
		pVtx[5].tex = D3DXVECTOR2((float)(0.25 * (pGunfire->nPatterAnim + 1)), 0.0);
		pVtx[6].tex = D3DXVECTOR2((float)(0.25 * pGunfire->nPatterAnim), 1.0);
		pVtx[7].tex = D3DXVECTOR2((float)(0.25 * (pGunfire->nPatterAnim + 1)), 1.0);
	}

	//BombUpdate
	pBomb = &g_Bomb[0];
	float g_fFadeCnt = (float)0.03;
	D3DXCOLOR g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	if (pBomb->size.x > 800)//bombの範囲
	{
		pBomb->size = pPlayer->size;
		pBomb->bUse = false;
	}
	else//bombの拡大
	{
		pBomb->size.x += 15;
		pBomb->size.y += 15;
	}
	pVtx[8].pos = D3DXVECTOR3(pBomb->pos.x - pBomb->size.x, pBomb->pos.y - pBomb->size.y, 0.0f);
	pVtx[9].pos = D3DXVECTOR3(pBomb->pos.x + pBomb->size.x, pBomb->pos.y - pBomb->size.y, 0.0f);
	pVtx[10].pos = D3DXVECTOR3(pBomb->pos.x - pBomb->size.x, pBomb->pos.y + pBomb->size.y, 0.0f);
	pVtx[11].pos = D3DXVECTOR3(pBomb->pos.x + pBomb->size.x, pBomb->pos.y + pBomb->size.y, 0.0f);
	pVtx[8].tex = D3DXVECTOR2(0.0, 0.0);
	pVtx[9].tex = D3DXVECTOR2(1.0, 0.0);
	pVtx[10].tex = D3DXVECTOR2(0.0, 1.0);
	pVtx[11].tex = D3DXVECTOR2(1.0, 1.0);
	g_pVtxBuffPlayer->Unlock();
	//一回animationを終わったら停止
	if (pGunfire->nPatterAnim == 4)
	{
		pGunfire->nPatterAnim = 0;
		pGunfire->bUse = false;
	}
}

void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevicePy = GetDevice();
	PLAYER *pPlayer = &g_aPlayer[0];
	GUNFIRE *pGunfire = &g_GunFire;
	BOMB *pBomb = &g_Bomb[0];

	//頂点Data flowの設定
	pDevicePy->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));
	//頂点modの設定
	pDevicePy->SetFVF(FVF_VERTEX_2D);

	//頂点Data flowの使用(1,ploygonの種類　2,始める頂点　3,polygonの数(2つD3DPT_TRIANGLESTRIP三角形))
	if (pPlayer->bUse == true)
	{
		//画像の設定
		pDevicePy->SetTexture(0, g_pTexturePlayer[0]);
		pDevicePy->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}

	//発砲するeffect
	if (pGunfire->bUse == true)
	{
		pDevicePy->SetTexture(0, g_pTexturePlayer[1]);
		pDevicePy->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4, 2);
	}

	//Draw player bomb
	if (pBomb->bUse == true)
	{
		pDevicePy->SetTexture(0, g_pTexturePlayer[2]);
		pDevicePy->DrawPrimitive(D3DPT_TRIANGLESTRIP, 8, 2);
	}
}

PLAYER *GetPlayer(void)
{
	return &g_aPlayer[0];
}

BOMB *GetBomb(void)
{
	return &g_Bomb[0];
}