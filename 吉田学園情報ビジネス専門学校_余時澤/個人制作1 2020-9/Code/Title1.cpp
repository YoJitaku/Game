//=============================================================================
//
// [Title1.cpp]
// Author : Yo Jitaku
//
//=============================================================================
#include "Title1.h"
#include "Input.h"
#include "Fade.h"
#include "Sound.h"

//create buffer pointer
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle1 = NULL;
//texture pointer
LPDIRECT3DTEXTURE9 g_pTextureTitle1[MAX_COMPONENT_TITLE1] = {};
//title polygon group
TITLE1 g_aTitle1[MAX_COMPONENT_TITLE1];
//時間count
int g_nCntAnimeTl1 = 0;

HRESULT InitTitle1(void)
{
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDeviceTl = GetDevice();
	TITLE1 *pTitle1 = &g_aTitle1[0];
	SetTitle1();//頂点set

	D3DXCreateTextureFromFile(pDeviceTl, "data/TEXTURE/Title1Background.png", &g_pTextureTitle1[0]);
	D3DXCreateTextureFromFile(pDeviceTl, "data/TEXTURE/Title1Logo.png", &g_pTextureTitle1[1]);
	D3DXCreateTextureFromFile(pDeviceTl, "data/TEXTURE/Title1Presskey.png", &g_pTextureTitle1[2]);
	D3DXCreateTextureFromFile(pDeviceTl, "data/TEXTURE/Title1UFO.png", &g_pTextureTitle1[3]);
	
	//create vertex buffer
	if (FAILED(pDeviceTl->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_COMPONENT_TITLE1, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffTitle1, NULL))) return E_FAIL;

	g_pVtxBuffTitle1->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntTitle = 0; nCntTitle < MAX_COMPONENT_TITLE1; nCntTitle++, pVtx += 4, pTitle1++)
	{
		pVtx[0].pos = D3DXVECTOR3(pTitle1->pos.x - pTitle1->size.x, pTitle1->pos.y - pTitle1->size.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(pTitle1->pos.x + pTitle1->size.x, pTitle1->pos.y - pTitle1->size.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(pTitle1->pos.x - pTitle1->size.x, pTitle1->pos.y + pTitle1->size.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(pTitle1->pos.x + pTitle1->size.x, pTitle1->pos.y + pTitle1->size.y, 0.0f);
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		if (nCntTitle == 3)//UFO animation
		{
			pVtx[0].tex = D3DXVECTOR2(0.0, 0.0);
			pVtx[1].tex = D3DXVECTOR2(0.25, 0.0);
			pVtx[2].tex = D3DXVECTOR2(0.0, 1.0);
			pVtx[3].tex = D3DXVECTOR2(0.25, 1.0);
		}
		else//別のcomponent
		{
			pVtx[0].tex = D3DXVECTOR2(0.0, 0.0);
			pVtx[1].tex = D3DXVECTOR2(1.0, 0.0);
			pVtx[2].tex = D3DXVECTOR2(0.0, 1.0);
			pVtx[3].tex = D3DXVECTOR2(1.0, 1.0);
		}
	}
	g_pVtxBuffTitle1->Unlock();
	return S_OK;
}

//release memory
void UninitTitle1(void)
{
	if (g_pVtxBuffTitle1 != NULL)
	{
		g_pVtxBuffTitle1->Release();
		g_pVtxBuffTitle1 = NULL;
	}
	for (int nCntTitle = 0; nCntTitle < MAX_COMPONENT_TITLE1; nCntTitle++)
	{
		if (g_pTextureTitle1[nCntTitle] != NULL)
		{
			g_pTextureTitle1[nCntTitle]->Release();
			g_pTextureTitle1[nCntTitle] = NULL;
		}
	}
}

void UpdateTitle1(void)
{
	VERTEX_2D *pVtx;
	TITLE1 *pTitle1 = &g_aTitle1[3];//ufo
	g_nCntAnimeTl1++;

	if (g_nCntAnimeTl1 % 10 == 0)
	{
		pTitle1->nPatterAnim++;
		g_pVtxBuffTitle1->Lock(0, 0, (void**)&pVtx, 0);
		pVtx[12].tex = D3DXVECTOR2((float)(0.25 * pTitle1->nPatterAnim), 0.0);
		pVtx[13].tex = D3DXVECTOR2((float)(0.25 * (pTitle1->nPatterAnim + 1)), 0.0);
		pVtx[14].tex = D3DXVECTOR2((float)(0.25 * pTitle1->nPatterAnim), 1.0);
		pVtx[15].tex = D3DXVECTOR2((float)(0.25 * (pTitle1->nPatterAnim + 1)), 1.0);
		g_pVtxBuffTitle1->Unlock();
	}

	pTitle1 = &g_aTitle1[1];//title
	if (pTitle1->pos.y < 200)
	{
		pTitle1->pos.y += 3;
		g_pVtxBuffTitle1->Lock(0, 0, (void**)&pVtx, 0);
		pVtx[4].pos = D3DXVECTOR3(pTitle1->pos.x - pTitle1->size.x, pTitle1->pos.y - pTitle1->size.y, 0.0f);
		pVtx[5].pos = D3DXVECTOR3(pTitle1->pos.x + pTitle1->size.x, pTitle1->pos.y - pTitle1->size.y, 0.0f);
		pVtx[6].pos = D3DXVECTOR3(pTitle1->pos.x - pTitle1->size.x, pTitle1->pos.y + pTitle1->size.y, 0.0f);
		pVtx[7].pos = D3DXVECTOR3(pTitle1->pos.x + pTitle1->size.x, pTitle1->pos.y + pTitle1->size.y, 0.0f);
		g_pVtxBuffTitle1->Unlock();	
	}

	//press enter
	if ((GetkeyboardTrigger(DIK_RETURN) == true))
	{
		PlaySound(SOUND_LABEL_SE_DECIDE);
		SetFade(FADE_OUT, MODE_TITLE2);
	}

	//presskey blink
	else if(g_nCntAnimeTl1 % 30 == 0)
	{
		pTitle1 = &g_aTitle1[2];
		pTitle1->bUse = !pTitle1->bUse;
	}
}

void DrawTitle1(void)
{
	LPDIRECT3DDEVICE9 pDeviceTl = GetDevice();
	TITLE1 *pTitle1 = &g_aTitle1[0];

	pDeviceTl->SetStreamSource(0, g_pVtxBuffTitle1, 0, sizeof(VERTEX_2D));//頂点Data flowの設定
	pDeviceTl->SetFVF(FVF_VERTEX_2D);//頂点modの設定

	for (int nCntTitle = 0; nCntTitle < MAX_COMPONENT_TITLE1; nCntTitle++, pTitle1++)
	{
		if (pTitle1->bUse == true)
		{
			pDeviceTl->SetTexture(0, g_pTextureTitle1[nCntTitle]);//画像設定
			pDeviceTl->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTitle * 4, 2);//頂点描画
		}
	}
}

void SetTitle1(void)
{
	//background
	g_aTitle1[0].pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	g_aTitle1[0].size.x = SCREEN_WIDTH / 2;
	g_aTitle1[0].size.y = SCREEN_HEIGHT / 2;
	g_aTitle1[0].nPatterAnim = 0;
	g_aTitle1[0].bUse = true;
	//logo
	g_aTitle1[1].pos = D3DXVECTOR3(1000 , -50, 0.0f);
	g_aTitle1[1].size.x = 400;
	g_aTitle1[1].size.y = 150;
	g_aTitle1[1].nPatterAnim = 0;
	g_aTitle1[1].bUse = true;
	//presskey
	g_aTitle1[2].pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 200, 0.0f);
	g_aTitle1[2].size.x = 200;
	g_aTitle1[2].size.y = 30;
	g_aTitle1[2].nPatterAnim = 0;
	g_aTitle1[2].bUse = true;
	//UFO
	g_aTitle1[3].pos = D3DXVECTOR3(300, 250, 0.0f);
	g_aTitle1[3].size.x = 200;
	g_aTitle1[3].size.y = 130;
	g_aTitle1[3].nPatterAnim = 0;
	g_aTitle1[3].bUse = true;
}