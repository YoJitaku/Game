//=============================================================================
//
// [UI.cpp]
// Author : JITAKU YO
//
//=============================================================================
#include "UI.h"
#include "Fade.h"
#include "Player.h"

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffUI = NULL;
LPDIRECT3DTEXTURE9 g_pTextureUI[UI_TYPE] = {};
POLYGON_2D *pUIPoly;
POLYGON_NUM *pUInum;
int nCntTime4;

HRESULT InitUI(void)
{
	nCntTime4 = 0;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D *pVtx;
	pUInum = (POLYGON_NUM *)malloc(UI_NUMBER * sizeof(POLYGON_NUM));

	//‘Ì‰·
	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/UI/TemperatureNumber.png", &g_pTextureUI[0])))return E_FAIL;
	pUInum[0].bUse = true;
	pUInum[0].pos = D3DXVECTOR3(WIDTH_SCREEN / 2 - 30, 100, 0);
	pUInum[0].size = D3DXVECTOR2(35, 45);
	pUInum[0].nTexture = 0;
	pUInum[0].nDisplayNumber = 9;
	pUInum[1].bUse = true;
	pUInum[1].pos = D3DXVECTOR3(WIDTH_SCREEN / 2 + 30, 100, 0);
	pUInum[1].size = D3DXVECTOR2(35, 45);
	pUInum[1].nTexture = 0;
	pUInum[1].nDisplayNumber = 9;

	//’e‚Ì”
	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/UI/BulletNumber.png", &g_pTextureUI[1])))return E_FAIL;
	pUInum[2].bUse = true;
	pUInum[2].pos = D3DXVECTOR3(WIDTH_SCREEN / 2 + 750, 100, 0);
	pUInum[2].size = D3DXVECTOR2(30, 40);
	pUInum[2].nTexture = 1;
	pUInum[2].nDisplayNumber = 0;

	pUInum[3].bUse = true;
	pUInum[3].pos = D3DXVECTOR3(WIDTH_SCREEN / 2 + 820, 100, 0);
	pUInum[3].size = D3DXVECTOR2(30, 40);
	pUInum[3].nTexture = 1;
	pUInum[3].nDisplayNumber = 0;

	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * (UI_NUMBER), D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffUI, NULL))) return E_FAIL;

	g_pVtxBuffUI->Lock(0, 0, (void**)&pVtx, 0);
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
	free(pUInum);
}

void UpdateUI(void)
{
	nCntTime4++;
	if (nCntTime4 % 60 == 1)
	{
		if (pUInum[1].nDisplayNumber != 0)
		{
			pUInum[1].nDisplayNumber--;
		}
		else
		{
			if (pUInum[0].nDisplayNumber != 0)
			{
				pUInum[0].nDisplayNumber--;
				pUInum[1].nDisplayNumber = 9;
			}
			else
			{
				SetFade(FADE_OUT, MODE_RANKING);
			}
		}
	}

	PLAYER *pPlayer = GetPlayer();
	int	nScore = pPlayer[0].nScore;
	if (nScore >= 10)
	{
		pUInum[3].nDisplayNumber = nScore % 10;
		pUInum[2].nDisplayNumber = nScore / 10;
	}
	else
	{
		pUInum[3].nDisplayNumber = nScore;
	}

	VERTEX_2D *pVtx;
	g_pVtxBuffUI->Lock(0, 0, (void**)&pVtx, 0);
	//number
	for (int nCntUI = 0; nCntUI < UI_NUMBER; nCntUI++, pVtx += 4)
	{
		pVtx[0].tex = D3DXVECTOR2((pUInum[nCntUI].nDisplayNumber * 0.1f), 0.0);
		pVtx[1].tex = D3DXVECTOR2((pUInum[nCntUI].nDisplayNumber * 0.1f + 0.1f), 0.0);
		pVtx[2].tex = D3DXVECTOR2((pUInum[nCntUI].nDisplayNumber * 0.1f), 1.0);
		pVtx[3].tex = D3DXVECTOR2((pUInum[nCntUI].nDisplayNumber * 0.1f + 0.1f), 1.0);
	}
	g_pVtxBuffUI->Unlock();
}

void DrawUI(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();;
	pDevice->SetStreamSource(0, g_pVtxBuffUI, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);
	for (int nCnt = 0; nCnt < UI_NUMBER; nCnt++)
	{
		if (pUInum[nCnt].bUse == true)
		{
			pDevice->SetTexture(0, g_pTextureUI[pUInum[nCnt].nTexture]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}
}

POLYGON_NUM *GetUI(void)
{
	return &pUInum[0];
}