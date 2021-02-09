//=============================================================================
//
// [UI.cpp]
// Author : JITAKU YO
//
//=============================================================================
#include "UI.h"

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffUI = NULL;
LPDIRECT3DTEXTURE9 g_pTextureUI[UI_TYPE] = {};
POLYGON_2D *pUIPoly;
POLYGON_NUM *pUInum;
int nCntTime4 = 0;
HRESULT InitUI(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D *pVtx;
	pUIPoly = (POLYGON_2D *)malloc(UI_POLYGON * sizeof(POLYGON_2D));
	pUInum = (POLYGON_NUM *)malloc(UI_NUMBER * sizeof(POLYGON_NUM));

	//照準器1
	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/UI/AimCircle.png", &g_pTextureUI[0])))return E_FAIL;
	pUIPoly[0].bUse = true;
	pUIPoly[0].pos = D3DXVECTOR3(WIDTH_SCREEN / 2, 450, 0);
	pUIPoly[0].size = D3DXVECTOR2(WIDTH_SCREEN / 3, HEIGHT_SCREEN / 3);

	//照準器2
	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/UI/AimCross.png", &g_pTextureUI[1])))return E_FAIL;
	pUIPoly[1].bUse = true;
	pUIPoly[1].pos = D3DXVECTOR3(WIDTH_SCREEN / 2, 450, 0);
	pUIPoly[1].size = D3DXVECTOR2(WIDTH_SCREEN / 3, HEIGHT_SCREEN / 3);

	//温度計
	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/UI/TemColor.png", &g_pTextureUI[2])))return E_FAIL;
	pUIPoly[2].bUse = true;
	pUIPoly[2].pos = D3DXVECTOR3(107, 800, 0);
	pUIPoly[2].size = D3DXVECTOR2(37, 225);
	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/UI/BodyTemperature.png", &g_pTextureUI[3])))return E_FAIL;
	pUIPoly[3].bUse = true; 
	pUIPoly[3].pos = D3DXVECTOR3(100, 800, 0);
	pUIPoly[3].size = D3DXVECTOR2(150, 300);

	//スラッシュ
	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/UI/Slash.png", &g_pTextureUI[4])))return E_FAIL;
	pUIPoly[4].bUse = true;
	pUIPoly[4].pos = D3DXVECTOR3(1700, 950, 0);
	pUIPoly[4].size = D3DXVECTOR2(150, 50);
	
	//体温
	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/UI/TemperatureNumber.png", &g_pTextureUI[5])))return E_FAIL;
	pUInum[0].bUse = true;
	pUInum[0].pos = D3DXVECTOR3(80, 510, 0);
	pUInum[0].size = D3DXVECTOR2(35, 45);
	pUInum[0].nTexture = 5;
	pUInum[0].nDisplayNumber = 3;
	pUInum[1].bUse = true;
	pUInum[1].pos = D3DXVECTOR3(135, 510, 0);
	pUInum[1].size = D3DXVECTOR2(35, 45);
	pUInum[1].nTexture = 5;
	pUInum[1].nDisplayNumber = 6;

	//弾の数
	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/UI/BulletNumber.png", &g_pTextureUI[6])))return E_FAIL;
	pUInum[2].bUse = true;
	pUInum[2].pos = D3DXVECTOR3(1600, 955, 0);
	pUInum[2].size = D3DXVECTOR2(30, 40);
	pUInum[2].nTexture = 6;
	pUInum[2].nDisplayNumber = 3;

	pUInum[3].bUse = true;
	pUInum[3].pos = D3DXVECTOR3(1655, 955, 0);
	pUInum[3].size = D3DXVECTOR2(30, 40);
	pUInum[3].nTexture = 6;
	pUInum[3].nDisplayNumber = 0;

	pUInum[4].bUse = true;
	pUInum[4].pos = D3DXVECTOR3(1765, 960, 0);
	pUInum[4].size = D3DXVECTOR2(20, 30);
	pUInum[4].nTexture = 6;
	pUInum[4].nDisplayNumber = 3;

	pUInum[5].bUse = true;
	pUInum[5].pos = D3DXVECTOR3(1805, 960, 0);
	pUInum[5].size = D3DXVECTOR2(20, 30);
	pUInum[5].nTexture = 6;
	pUInum[5].nDisplayNumber = 0;
	//create vertex buffer
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * (UI_POLYGON + UI_NUMBER), D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffUI, NULL))) return E_FAIL;

	g_pVtxBuffUI->Lock(0, 0, (void**)&pVtx, 0);
	//polygon
	for (int nCntUI = 0; nCntUI < UI_POLYGON; nCntUI++, pVtx += 4)
	{
		pVtx[0].pos = D3DXVECTOR3(pUIPoly[nCntUI].pos.x - pUIPoly[nCntUI].size.x, pUIPoly[nCntUI].pos.y - pUIPoly[nCntUI].size.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(pUIPoly[nCntUI].pos.x + pUIPoly[nCntUI].size.x, pUIPoly[nCntUI].pos.y - pUIPoly[nCntUI].size.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(pUIPoly[nCntUI].pos.x - pUIPoly[nCntUI].size.x, pUIPoly[nCntUI].pos.y + pUIPoly[nCntUI].size.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(pUIPoly[nCntUI].pos.x + pUIPoly[nCntUI].size.x, pUIPoly[nCntUI].pos.y + pUIPoly[nCntUI].size.y, 0.0f);
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		pVtx[0].tex = D3DXVECTOR2(0.0, 0.0);
		pVtx[1].tex = D3DXVECTOR2(1.0, 0.0);
		pVtx[2].tex = D3DXVECTOR2(0.0, 1.0);
		pVtx[3].tex = D3DXVECTOR2(1.0, 1.0);
	}

	//number
	for (int nCntUI = 0; nCntUI < UI_NUMBER; nCntUI++, pVtx += 4)
	{
		pVtx[0].pos = D3DXVECTOR3(pUInum[nCntUI].pos.x - pUInum[nCntUI].size.x, pUInum[nCntUI].pos.y - pUInum[nCntUI].size.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(pUInum[nCntUI].pos.x + pUInum[nCntUI].size.x, pUInum[nCntUI].pos.y - pUInum[nCntUI].size.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(pUInum[nCntUI].pos.x - pUInum[nCntUI].size.x, pUInum[nCntUI].pos.y + pUInum[nCntUI].size.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(pUInum[nCntUI].pos.x + pUInum[nCntUI].size.x, pUInum[nCntUI].pos.y + pUInum[nCntUI].size.y, 0.0f);
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		pVtx[0].tex = D3DXVECTOR2((pUInum[nCntUI].nDisplayNumber * 0.1f), 0.0);
		pVtx[1].tex = D3DXVECTOR2((pUInum[nCntUI].nDisplayNumber * 0.1f + 0.1f), 0.0);
		pVtx[2].tex = D3DXVECTOR2((pUInum[nCntUI].nDisplayNumber * 0.1f), 1.0);
		pVtx[3].tex = D3DXVECTOR2((pUInum[nCntUI].nDisplayNumber * 0.1f + 0.1f), 1.0);
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
	free(pUIPoly);
	free(pUInum);
}

void UpdateUI(void)
{

}

void DrawUI(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();;
	int nAdd = 0;
	pDevice->SetStreamSource(0, g_pVtxBuffUI, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);
	for (int nCnt = 0; nCnt < UI_POLYGON + UI_NUMBER; nCnt++)
	{
		if (pUIPoly[nCnt].bUse == true && nCnt < UI_POLYGON )
		{
			pDevice->SetTexture(0, g_pTextureUI[nCnt]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
		else if (pUInum[nCnt - UI_POLYGON].bUse == true && nCnt < UI_POLYGON + UI_NUMBER)
		{
			pDevice->SetTexture(0, g_pTextureUI[pUInum[nCnt - UI_POLYGON].nTexture]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}
}