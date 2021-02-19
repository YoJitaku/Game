//=============================================================================
//
// [GCO.cpp] game clear and game over
// Author : JITAKU YO
//
//=============================================================================
#include "GameClearOver.h"

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGCO = NULL;//頂点buffのpointer
LPDIRECT3DTEXTURE9 g_pTextureGCO[2] = {};//画像のpointer
POLYGON_2D *pGCO;

HRESULT InitGCO(void)
{
	LPDIRECT3DDEVICE9 pDeviceGCO = GetDevice();
	VERTEX_2D *pVtx;
	pGCO = (POLYGON_2D *)malloc(GCO_COMPONENT * sizeof(POLYGON_2D));

	//初期化
	pGCO[0].bUse = false;
	pGCO[0].size = D3DXVECTOR2(WIDTH_SCREEN / 2, HEIGHT_SCREEN / 2);
	pGCO[0].pos = D3DXVECTOR3(WIDTH_SCREEN / 2, HEIGHT_SCREEN / 2, 0.0f);
	pGCO[1].bUse = false;
	pGCO[1].size = D3DXVECTOR2(WIDTH_SCREEN / 2, HEIGHT_SCREEN / 2);
	pGCO[1].pos = D3DXVECTOR3(WIDTH_SCREEN / 2, HEIGHT_SCREEN / 2, 0.0f);

	D3DXCreateTextureFromFile(pDeviceGCO, "data/Texture/ScreenTransition/GameOver.png", &g_pTextureGCO[0]);
	D3DXCreateTextureFromFile(pDeviceGCO, "data/Texture/ScreenTransition/GameClear.png", &g_pTextureGCO[1]);

	if (FAILED(pDeviceGCO->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * GCO_COMPONENT, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffGCO, NULL))) return E_FAIL;

	g_pVtxBuffGCO->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < 2; nCnt++, pVtx += 4)
	{
		pVtx[0].pos = D3DXVECTOR3(pGCO[nCnt].pos.x - pGCO[nCnt].size.x, pGCO[nCnt].pos.y - pGCO[nCnt].size.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(pGCO[nCnt].pos.x + pGCO[nCnt].size.x, pGCO[nCnt].pos.y - pGCO[nCnt].size.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(pGCO[nCnt].pos.x - pGCO[nCnt].size.x, pGCO[nCnt].pos.y + pGCO[nCnt].size.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(pGCO[nCnt].pos.x + pGCO[nCnt].size.x, pGCO[nCnt].pos.y + pGCO[nCnt].size.y, 0.0f);
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
	g_pVtxBuffGCO->Unlock();
	return S_OK;
}

void UninitGCO(void)
{
	if (g_pVtxBuffGCO != NULL)
	{
		g_pVtxBuffGCO->Release();
		g_pVtxBuffGCO = NULL;
	}
	for (int nCnt = 0; nCnt < GCO_COMPONENT; nCnt++)
	{
		if (g_pTextureGCO[nCnt] != NULL)
		{
			g_pTextureGCO[nCnt]->Release();
			g_pTextureGCO[nCnt] = NULL;
		}
	}
}

void UpdateGCO(void)
{

}

void DrawGCO(void)
{
	LPDIRECT3DDEVICE9 pDeviceOAC = GetDevice();
	pDeviceOAC->SetStreamSource(0, g_pVtxBuffGCO, 0, sizeof(VERTEX_2D));//頂点Data flowの設定
	pDeviceOAC->SetFVF(FVF_VERTEX_2D);//頂点modの設定

	for (int nCnt = 0; nCnt < GCO_COMPONENT; nCnt++)
	{
		if (pGCO[nCnt].bUse == true)
		{
			pDeviceOAC->SetTexture(0, g_pTextureGCO[nCnt]);//Textureの設定
			pDeviceOAC->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);//頂点の描画
		}
	}
}