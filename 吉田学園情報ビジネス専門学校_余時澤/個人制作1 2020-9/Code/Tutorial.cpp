//=============================================================================
//
// [Tutorial.cpp]
// Author : Yo Jitaku
//
//=============================================================================
#include "Tutorial.h"
#include "Fade.h"
#include "Input.h"
//create buffer pointer
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL;
//texture pointer
LPDIRECT3DTEXTURE9 g_pTextureTutorial[MAX_COMPONENT_TUTORIAL] = {};
//title polygon group
TUTORIAL g_aTutorial1[MAX_COMPONENT_TUTORIAL];

HRESULT InitTutorial(void)
{
	LPDIRECT3DDEVICE9 pDeviceTt = GetDevice();
	VERTEX_2D *pVtx;

	SetTutorial();//init

	D3DXCreateTextureFromFile(pDeviceTt, "data/TEXTURE/Tutorial.png", &g_pTextureTutorial[0]);

	//create vertex buffer
	if (FAILED(pDeviceTt->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_COMPONENT_TUTORIAL, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffTutorial, NULL))) return E_FAIL;

	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntTitle = 0; nCntTitle < MAX_COMPONENT_TUTORIAL; nCntTitle++, pVtx += 4)
	{
		pVtx[0].pos = D3DXVECTOR3(g_aTutorial1[nCntTitle].pos.x - g_aTutorial1[nCntTitle].size.x, g_aTutorial1[nCntTitle].pos.y - g_aTutorial1[nCntTitle].size.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aTutorial1[nCntTitle].pos.x + g_aTutorial1[nCntTitle].size.x, g_aTutorial1[nCntTitle].pos.y - g_aTutorial1[nCntTitle].size.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aTutorial1[nCntTitle].pos.x - g_aTutorial1[nCntTitle].size.x, g_aTutorial1[nCntTitle].pos.y + g_aTutorial1[nCntTitle].size.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aTutorial1[nCntTitle].pos.x + g_aTutorial1[nCntTitle].size.x, g_aTutorial1[nCntTitle].pos.y + g_aTutorial1[nCntTitle].size.y, 0.0f);
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
	g_pVtxBuffTutorial->Unlock();
	return S_OK;
}

//release memory
void UninitTutorial(void)
{
	if (g_pVtxBuffTutorial != NULL)
	{
		g_pVtxBuffTutorial->Release();
		g_pVtxBuffTutorial = NULL;
	}
	for (int nCnt = 0; nCnt < MAX_COMPONENT_TUTORIAL; nCnt++)
	{
		if (g_pTextureTutorial[nCnt] != NULL)
		{
			g_pTextureTutorial[nCnt]->Release();
			g_pTextureTutorial[nCnt] = NULL;
		}
	}
}

void UpdateTutorial(void)
{
	if ((GetkeyboardTrigger(DIK_RETURN) == true)) SetFade(FADE_OUT, MODE_TITLE2);
}

void DrawTutorial(void)
{
	LPDIRECT3DDEVICE9 pDeviceTt = GetDevice();
	TUTORIAL *pTutorial = &g_aTutorial1[0];

	pDeviceTt->SetStreamSource(0, g_pVtxBuffTutorial, 0, sizeof(VERTEX_2D));//í∏ì_Data flowÇÃê›íË
	pDeviceTt->SetFVF(FVF_VERTEX_2D);//í∏ì_modÇÃê›íË

	for (int nCntTitle = 0; nCntTitle < MAX_COMPONENT_TUTORIAL; nCntTitle++, pTutorial++)
	{
		if (pTutorial->bUse == true)
		{
			pDeviceTt->SetTexture(0, g_pTextureTutorial[nCntTitle]);//âÊëúê›íË
			pDeviceTt->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTitle * 4, 2);//í∏ì_ï`âÊ
		}
	}
}

void SetTutorial(void)
{
	//background
	g_aTutorial1[0].pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	g_aTutorial1[0].size.x = SCREEN_WIDTH / 2;
	g_aTutorial1[0].size.y = SCREEN_HEIGHT / 2;
	g_aTutorial1[0].bUse = true;
}