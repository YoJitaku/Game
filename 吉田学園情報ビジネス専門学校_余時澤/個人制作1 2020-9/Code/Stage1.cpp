//=============================================================================
//
// [Stage1.cpp]
// Author : Yo Jitaku
//
//=============================================================================
#include "Stage1.h"
#include "Input.h"
#include "Fade.h"
#include "Player.h"

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffStage1 = NULL;//頂点buffer
LPDIRECT3DTEXTURE9 g_pTextureStage1[MAX_COMPONENT_STAGE1] = {};//texture
STAGE1 g_aStage1[MAX_COMPONENT_STAGE1];//background component
int	g_nCntAnimeSt1 = 0;//時間count

//基本設定
void SetStage1(void)
{
	//background
	g_aStage1[0].pos = D3DXVECTOR3(SCREEN_WIDTH * 2, SCREEN_HEIGHT / 2, 0.0f);
	g_aStage1[0].size.x = SCREEN_WIDTH * 2;
	g_aStage1[0].size.y = SCREEN_HEIGHT / 2;
	g_aStage1[0].move.x = -2;
	g_aStage1[0].bUse = true;
	//sun
	g_aStage1[1].pos = D3DXVECTOR3(1300.0f, 100.0f, 0.0f);
	g_aStage1[1].size.x = 100;
	g_aStage1[1].size.y = 100;
	g_aStage1[1].move.x = -1;
	g_aStage1[1].bUse = true;
	//cloud1
	g_aStage1[2].pos = D3DXVECTOR3(1800, 300, 0.0f);
	g_aStage1[2].size.x = 150;
	g_aStage1[2].size.y = 75;
	g_aStage1[2].move.x = (float)-3.5;
	g_aStage1[2].move.y = 30;
	g_aStage1[2].bUse = true;
	//cloud2
	g_aStage1[3].pos = D3DXVECTOR3(2000, 100, 0.0f);
	g_aStage1[3].size.x = 200;
	g_aStage1[3].size.y = 100;
	g_aStage1[3].move.x = -3;
	g_aStage1[3].move.y = -10;
	g_aStage1[3].bUse = true;
	//cloud3
	g_aStage1[4].pos = D3DXVECTOR3(1750, 200, 0.0f);
	g_aStage1[4].size.x = 100;
	g_aStage1[4].size.y = 50;
	g_aStage1[4].move.x = (float)-4.5;
	g_aStage1[4].move.y = 15;
	g_aStage1[4].bUse = true;
	//next mark
	g_aStage1[5].pos = D3DXVECTOR3(1300, 400, 0.0f);
	g_aStage1[5].size.x = 100;
	g_aStage1[5].size.y = 50;
	g_aStage1[5].bUse = false;
}

HRESULT InitStage1Bg(void)
{
	LPDIRECT3DDEVICE9 pDeviceSt1 = GetDevice();
	VERTEX_2D *pVtx;
	STAGE1 *pStage = &g_aStage1[0];
	SetStage1();//頂点set

	D3DXCreateTextureFromFile(pDeviceSt1, "data/TEXTURE/Stage2Background.png", &g_pTextureStage1[0]);
	D3DXCreateTextureFromFile(pDeviceSt1, "data/TEXTURE/Stage1Sun.png", &g_pTextureStage1[1]);
	D3DXCreateTextureFromFile(pDeviceSt1, "data/TEXTURE/Stage1Cloud1.png", &g_pTextureStage1[2]);
	D3DXCreateTextureFromFile(pDeviceSt1, "data/TEXTURE/Stage1Cloud2.png", &g_pTextureStage1[3]);
	D3DXCreateTextureFromFile(pDeviceSt1, "data/TEXTURE/Stage1Cloud3.png", &g_pTextureStage1[4]);
	D3DXCreateTextureFromFile(pDeviceSt1, "data/TEXTURE/Next.png", &g_pTextureStage1[5]);

	//create vertex buffer
	if (FAILED(pDeviceSt1->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_COMPONENT_STAGE1, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffStage1, NULL))) return E_FAIL;

	g_pVtxBuffStage1->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntStage = 0; nCntStage < MAX_COMPONENT_STAGE1; nCntStage++, pVtx += 4, pStage++)
	{
		if (pStage->bUse == true)
		{
			pVtx[0].pos = D3DXVECTOR3(pStage->pos.x - pStage->size.x, pStage->pos.y - pStage->size.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(pStage->pos.x + pStage->size.x, pStage->pos.y - pStage->size.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(pStage->pos.x - pStage->size.x, pStage->pos.y + pStage->size.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(pStage->pos.x + pStage->size.x, pStage->pos.y + pStage->size.y, 0.0f);
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
	}
	g_pVtxBuffStage1->Unlock();
	return S_OK;
}

void UninitStage1Bg(void)
{
	if (g_pVtxBuffStage1 != NULL)
	{
		g_pVtxBuffStage1->Release();
		g_pVtxBuffStage1 = NULL;
	}
	for (int nCntStage = 0; nCntStage < MAX_COMPONENT_STAGE1; nCntStage++)
	{
		if (g_pTextureStage1[nCntStage] != NULL)
		{
			g_pTextureStage1[nCntStage]->Release();
			g_pTextureStage1[nCntStage] = NULL;
		}
	}
}
void UpdateStage1Bg(void)
{
	VERTEX_2D *pVtx;
	STAGE1 *pStage1 = &g_aStage1[0];
	PLAYER *pPlayer = GetPlayer();
	g_nCntAnimeSt1++;

	//player登場したらbackground移動開始
	if (pPlayer->bPlayerInStage1 == true)
	{
		g_pVtxBuffStage1->Lock(0, 0, (void**)&pVtx, 0);
		for (int nCnt = 0; nCnt < MAX_COMPONENT_STAGE1; nCnt++, pVtx += 4, pStage1++)
		{
			pStage1->pos.x += pStage1->move.x;
			switch (nCnt)
			{
			case 0://background
				if (pStage1->pos.x <= -SCREEN_WIDTH)pStage1->pos.x = SCREEN_WIDTH * 2;
				break;
			case 1://sun
				if (pStage1->pos.x <= 1000)pStage1->move.x = +1;
				if (pStage1->pos.x >= 1600)pStage1->move.x = -1;
				break;
			case 2://cloud1
				if (pStage1->pos.x <= -100)
				{
					pStage1->pos.x = 1700;
					pStage1->pos.y += pStage1->move.y;
					if (pStage1->pos.y >= 500) pStage1->pos.y -= 450;
				}
				break;
			case 3://cloud2
				if (pStage1->pos.x <= -50)
				{
					pStage1->pos.x = 1800;
					pStage1->pos.y += pStage1->move.y;
					if (pStage1->pos.y <= 50) pStage1->pos.y += 250;
					if (pStage1->pos.y >= 500) pStage1->pos.y -= 400;
				}
				break;
			case 4://cloud3
				if (pStage1->pos.x <= -50)
				{
					pStage1->pos.x = 1800;
					pStage1->pos.y += pStage1->move.y;
					if (pStage1->pos.y <= 150) pStage1->move.y = 25;
					else if (pStage1->pos.y >= 500) pStage1->move.y = -30;
				}
				break;
			case 5://next mark
				if (pStage1->bUse == true)
				{
					pStage1->pos.x += 2;
					if (pStage1->pos.x >= 1450) pStage1->pos.x = 1300;
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
			}
			pVtx[0].pos = D3DXVECTOR3(pStage1->pos.x - pStage1->size.x, pStage1->pos.y - pStage1->size.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(pStage1->pos.x + pStage1->size.x, pStage1->pos.y - pStage1->size.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(pStage1->pos.x - pStage1->size.x, pStage1->pos.y + pStage1->size.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(pStage1->pos.x + pStage1->size.x, pStage1->pos.y + pStage1->size.y, 0.0f);
		}
		g_pVtxBuffStage1->Unlock();
	}
}

void DrawStage1Bg(void)
{
	LPDIRECT3DDEVICE9 pDeviceSt1 = GetDevice();
	STAGE1 *pStage1 = &g_aStage1[0];

	pDeviceSt1->SetStreamSource(0, g_pVtxBuffStage1, 0, sizeof(VERTEX_2D));//explosion画像の頂点Data flowの設定
	pDeviceSt1->SetFVF(FVF_VERTEX_2D);//頂点modの設定

	for (int nCntTitle = 0; nCntTitle < MAX_COMPONENT_STAGE1; nCntTitle++, pStage1++)
	{
		if (pStage1->bUse == true)
		{
			pDeviceSt1->SetTexture(0, g_pTextureStage1[nCntTitle]);//explosion画像設定
			pDeviceSt1->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTitle * 4, 2);//描画
		}
	}
}

STAGE1 *GetStage1Next(void)
{
	return &g_aStage1[5];
}