//=============================================================================
//
// [UI.cpp]
// Author : Yo Jitaku
//
//=============================================================================
#include "UI.h"
#include "Player.h"
#include "Fade.h"
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffUI = NULL;
//texture pointer
LPDIRECT3DTEXTURE9 g_pTextureUI[UI_TYPE] = {};
//title polygon group
UI g_aUI[MAX_UI_COMPONET];

void SetUI(void)
{
	UI *pUI = &g_aUI[0];

	//health
	for (int nCnt = 0; nCnt < 3; nCnt++, pUI++)
	{
		pUI->pos.x = 100 + (float)nCnt * 75;
		pUI->pos.y = 75;
		pUI->pos.z = 0;
		pUI->size.x = 40;
		pUI->size.y = 40;
		pUI->nType = 0;
		pUI->bUse = true;
	}
	//level
	g_aUI[3].pos = D3DXVECTOR3(500, 75, 0);
	g_aUI[3].size = D3DXVECTOR2(150, 50);
	g_aUI[3].nType = 1;
	g_aUI[3].bUse = true;
	//bomb
	g_aUI[4].pos = D3DXVECTOR3(700, 75, 0);
	g_aUI[4].size = D3DXVECTOR2(100, 50);
	g_aUI[4].nType = 2;
	g_aUI[4].bUse = true;
	//numberlevel
	g_aUI[5].pos = D3DXVECTOR3(580, 75, 0);
	g_aUI[5].size = D3DXVECTOR2(20, 30);
	g_aUI[5].nType = 3;
	g_aUI[5].bUse = true;
	//numberbomb
	g_aUI[6].pos = D3DXVECTOR3(742, 75, 0);
	g_aUI[6].size = D3DXVECTOR2(18, 26);
	g_aUI[6].nType = 3;
	g_aUI[6].bUse = true;
}
HRESULT InitUI(void)
{
	LPDIRECT3DDEVICE9 pDeviceUI = GetDevice();
	VERTEX_2D *pVtx;
	UI *pUI = &g_aUI[0];

	SetUI();//init

	D3DXCreateTextureFromFile(pDeviceUI, "data/TEXTURE/Health.png", &g_pTextureUI[0]);
	D3DXCreateTextureFromFile(pDeviceUI, "data/TEXTURE/Level.png", &g_pTextureUI[1]);
	D3DXCreateTextureFromFile(pDeviceUI, "data/TEXTURE/Bomb.png", &g_pTextureUI[2]);
	D3DXCreateTextureFromFile(pDeviceUI, "data/TEXTURE/UINumber.png", &g_pTextureUI[3]);

	//create vertex buffer
	if (FAILED(pDeviceUI->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_UI_COMPONET, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffUI, NULL))) return E_FAIL;

	g_pVtxBuffUI->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntUI = 0; nCntUI < MAX_UI_COMPONET; nCntUI++, pVtx += 4, pUI++)
	{
		pVtx[0].pos = D3DXVECTOR3(pUI->pos.x - g_aUI[nCntUI].size.x, pUI->pos.y - pUI->size.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(pUI->pos.x + g_aUI[nCntUI].size.x, pUI->pos.y - pUI->size.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(pUI->pos.x - g_aUI[nCntUI].size.x, pUI->pos.y + pUI->size.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(pUI->pos.x + g_aUI[nCntUI].size.x, pUI->pos.y + pUI->size.y, 0.0f);
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		if (nCntUI > 4)//numberの表示
		{
			pVtx[0].tex = D3DXVECTOR2(0.0, 0.0);
			pVtx[1].tex = D3DXVECTOR2((float)0.1, 0.0);
			pVtx[2].tex = D3DXVECTOR2(0.0, 1.0);
			pVtx[3].tex = D3DXVECTOR2((float)0.1, 1.0);
		}
		else//hp texture
		{
			pVtx[0].tex = D3DXVECTOR2(0.0, 0.0);
			pVtx[1].tex = D3DXVECTOR2(1.0, 0.0);
			pVtx[2].tex = D3DXVECTOR2(0.0, 1.0);
			pVtx[3].tex = D3DXVECTOR2(1.0, 1.0);
		}
	}
	g_pVtxBuffUI->Unlock();
	return S_OK;
}
void UninitUI(void)
{
	if (g_pVtxBuffUI != NULL)
	{
		g_pVtxBuffUI->Release();
		g_pVtxBuffUI = NULL;
	}
	for (int nCnt = 0; nCnt < UI_TYPE; nCnt++)
	{
		if (g_pTextureUI[nCnt] != NULL)
		{
			g_pTextureUI[nCnt]->Release();
			g_pTextureUI[nCnt] = NULL;
		}
	}
}
void UpdateUI(void)
{
	VERTEX_2D *pVtx;
	UI *pUI = &g_aUI[0];
	PLAYER *pPlayer = GetPlayer();

	//health
	if (pPlayer->nLife == 0)
	{
		SetFade(FADE_OUT, MODE_RANKING);
	}
	for (int nCnt = 0; nCnt < 3; nCnt++, pUI++)
	{
		if (nCnt >= pPlayer->nLife) pUI->bUse = false;
		else pUI->bUse = true;
	}

	g_pVtxBuffUI->Lock(0, 0, (void**)&pVtx, 0);
	//level
	pVtx[20].tex = D3DXVECTOR2((float)0.0 + (float)(0.1 * pPlayer->nBulletLevel), 0.0);
	pVtx[21].tex = D3DXVECTOR2((float)0.1 + (float)(0.1 * pPlayer->nBulletLevel), 0.0);
	pVtx[22].tex = D3DXVECTOR2((float)0.0 + (float)(0.1 * pPlayer->nBulletLevel), 1.0);
	pVtx[23].tex = D3DXVECTOR2((float)0.1 + (float)(0.1 * pPlayer->nBulletLevel), 1.0);
	//bomb number
	pVtx[24].tex = D3DXVECTOR2((float)0.0 + (float)(0.1 * pPlayer->nBomb), 0.0);
	pVtx[25].tex = D3DXVECTOR2((float)0.1 + (float)(0.1 * pPlayer->nBomb), 0.0);
	pVtx[26].tex = D3DXVECTOR2((float)0.0 + (float)(0.1 * pPlayer->nBomb), 1.0);
	pVtx[27].tex = D3DXVECTOR2((float)0.1 + (float)(0.1 * pPlayer->nBomb), 1.0);
	g_pVtxBuffUI->Unlock();
}
void DrawUI(void)
{
	LPDIRECT3DDEVICE9 pDeviceTl = GetDevice();
	UI *pUI = &g_aUI[0];

	pDeviceTl->SetStreamSource(0, g_pVtxBuffUI, 0, sizeof(VERTEX_2D));//頂点Data flowの設定
	pDeviceTl->SetFVF(FVF_VERTEX_2D);//頂点modの設定
	for (int nCnt = 0; nCnt < MAX_UI_COMPONET; nCnt++, pUI++)
	{
		pDeviceTl->SetTexture(0, g_pTextureUI[pUI->nType]);//画像設定
		if (pUI->bUse == true) pDeviceTl->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);//頂点描画
	}
}