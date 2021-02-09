//=============================================================================
//
// [Title2.cpp]
// Author : Yo Jitaku
//
//=============================================================================
#include "Title2.h"
#include "Input.h"
#include "Fade.h"
#include "Sound.h"
//create buffer pointer
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle2 = NULL;
//texture pointer
LPDIRECT3DTEXTURE9 g_pTextureTitle2[MAX_COMPONENT_TITLE2] = {};
//title polygon group
TITLE2 g_aTitle2[MAX_COMPONENT_TITLE2];

int g_nCntAnimetl2 = 0;

HRESULT InitTitle2(void)
{
	LPDIRECT3DDEVICE9 pDeviceTl = GetDevice();
	VERTEX_2D *pVtx;
	TITLE2 *pTitle2 = &g_aTitle2[0];

	SetTitle2();//init

	D3DXCreateTextureFromFile(pDeviceTl, "data/TEXTURE/Title2Background1.png", &g_pTextureTitle2[0]);
	D3DXCreateTextureFromFile(pDeviceTl, "data/TEXTURE/Title2Background2.png", &g_pTextureTitle2[1]);
	D3DXCreateTextureFromFile(pDeviceTl, "data/TEXTURE/Title2Background3.png", &g_pTextureTitle2[2]);
	D3DXCreateTextureFromFile(pDeviceTl, "data/TEXTURE/Title2UFO.png", &g_pTextureTitle2[3]);
	D3DXCreateTextureFromFile(pDeviceTl, "data/TEXTURE/Title2Start.png", &g_pTextureTitle2[4]);
	D3DXCreateTextureFromFile(pDeviceTl, "data/TEXTURE/Title2Tutorial.png", &g_pTextureTitle2[5]);
	D3DXCreateTextureFromFile(pDeviceTl, "data/TEXTURE/Title2Ranking.png", &g_pTextureTitle2[6]);
	D3DXCreateTextureFromFile(pDeviceTl, "data/TEXTURE/Hand.png", &g_pTextureTitle2[7]);

	//create vertex buffer
	if (FAILED(pDeviceTl->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_COMPONENT_TITLE2, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffTitle2, NULL))) return E_FAIL;

	g_pVtxBuffTitle2->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntTitle = 0; nCntTitle < MAX_COMPONENT_TITLE2; nCntTitle++, pVtx += 4, pTitle2++)
	{
		pVtx[0].pos = D3DXVECTOR3(pTitle2->pos.x - pTitle2->size.x, pTitle2->pos.y - pTitle2->size.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(pTitle2->pos.x + pTitle2->size.x, pTitle2->pos.y - pTitle2->size.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(pTitle2->pos.x - pTitle2->size.x, pTitle2->pos.y + pTitle2->size.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(pTitle2->pos.x + pTitle2->size.x, pTitle2->pos.y + pTitle2->size.y, 0.0f);
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		if (nCntTitle == 3)//ufo animation
		{
			pVtx[0].tex = D3DXVECTOR2(0.0, 0.0);
			pVtx[1].tex = D3DXVECTOR2(0.25, 0.0);
			pVtx[2].tex = D3DXVECTOR2(0.0, 1.0);
			pVtx[3].tex = D3DXVECTOR2(0.25, 1.0);
		}
		else
		{
			pVtx[0].tex = D3DXVECTOR2(0.0, 0.0);
			pVtx[1].tex = D3DXVECTOR2(1.0, 0.0);
			pVtx[2].tex = D3DXVECTOR2(0.0, 1.0);
			pVtx[3].tex = D3DXVECTOR2(1.0, 1.0);
		}
	}
	g_pVtxBuffTitle2->Unlock();
	return S_OK;
}

//release memory
void UninitTitle2(void)
{
	if (g_pVtxBuffTitle2 != NULL)
	{
		g_pVtxBuffTitle2->Release();
		g_pVtxBuffTitle2 = NULL;
	}
	for (int nCntTitle = 0; nCntTitle < MAX_COMPONENT_TITLE2; nCntTitle++)
	{
		if (g_pTextureTitle2[nCntTitle] != NULL)
		{
			g_pTextureTitle2[nCntTitle]->Release();
			g_pTextureTitle2[nCntTitle] = NULL;
		}
	}
}

void UpdateTitle2(void)
{
	VERTEX_2D *pVtx;
	TITLE2 *pTitle2 = &g_aTitle2[0];
	g_nCntAnimetl2++;
	float fStarSpeed = (float)0.0025;//background star move speed

	g_pVtxBuffTitle2->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntTl2 = 0; nCntTl2 < MAX_COMPONENT_TITLE2; nCntTl2++, pVtx += 4, pTitle2++)
	{
		if (nCntTl2 < 3)//background 123 star
		{
			pVtx[0].tex = D3DXVECTOR2((float)(fStarSpeed * g_nCntAnimetl2 * (nCntTl2 + 1)), (float)(fStarSpeed * g_nCntAnimetl2 * (nCntTl2 + 1)));
			pVtx[1].tex = D3DXVECTOR2((float)(1.0 + fStarSpeed * g_nCntAnimetl2 * (nCntTl2 + 1)), (float)(fStarSpeed * g_nCntAnimetl2 * (nCntTl2 + 1)));
			pVtx[2].tex = D3DXVECTOR2((float)(fStarSpeed * g_nCntAnimetl2 * (nCntTl2 + 1)), (float)(1.0 + fStarSpeed * g_nCntAnimetl2 * (nCntTl2 + 1)));
			pVtx[3].tex = D3DXVECTOR2((float)(1.0 + fStarSpeed * g_nCntAnimetl2 * (nCntTl2 + 1)), (float)(1.0 + fStarSpeed * g_nCntAnimetl2 * (nCntTl2 + 1)));
		}
		else if (nCntTl2 == 3)//ufo
		{
			if (g_nCntAnimetl2 % 10 == 0)
			{
				pTitle2->nPatterAnim++;
				pVtx[0].tex = D3DXVECTOR2((float)(0.25 * pTitle2->nPatterAnim), 0.0);
				pVtx[1].tex = D3DXVECTOR2((float)(0.25 * (pTitle2->nPatterAnim + 1)), 0.0);
				pVtx[2].tex = D3DXVECTOR2((float)(0.25 * pTitle2->nPatterAnim), 1.0);
				pVtx[3].tex = D3DXVECTOR2((float)(0.25 * (pTitle2->nPatterAnim + 1)), 1.0);
			}
		}
		else if (nCntTl2 == 7)//select
		{
			if ((GetkeyboardTrigger(DIK_UP) == true))
			{
				PlaySound(SOUND_LABEL_SE_SELECT);
				pTitle2->pos.y -= 100;
				if (pTitle2->pos.y <= 200) pTitle2->pos.y = 500;
			}
			else if ((GetkeyboardTrigger(DIK_DOWN) == true))
			{
				PlaySound(SOUND_LABEL_SE_SELECT);
				pTitle2->pos.y += 100;
				if (pTitle2->pos.y >= 600) pTitle2->pos.y = 300;
			}
			pVtx[0].pos = D3DXVECTOR3(pTitle2->pos.x - pTitle2->size.x, pTitle2->pos.y - pTitle2->size.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(pTitle2->pos.x + pTitle2->size.x, pTitle2->pos.y - pTitle2->size.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(pTitle2->pos.x - pTitle2->size.x, pTitle2->pos.y + pTitle2->size.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(pTitle2->pos.x + pTitle2->size.x, pTitle2->pos.y + pTitle2->size.y, 0.0f);
		}
	}
	g_pVtxBuffTitle2->Unlock();

	//enter press 
	if ((GetkeyboardTrigger(DIK_RETURN) == true) && g_aTitle2[7].pos.y == 300)
	{
		PlaySound(SOUND_LABEL_SE_DECIDE);
		SetFade(FADE_OUT, MODE_STAGE1);
	}
	else if ((GetkeyboardTrigger(DIK_RETURN) == true) && g_aTitle2[7].pos.y == 400)
	{
		PlaySound(SOUND_LABEL_SE_DECIDE);
		SetFade(FADE_OUT, MODE_TUTORIAL);
	}
	else if ((GetkeyboardTrigger(DIK_RETURN) == true) && g_aTitle2[7].pos.y == 500)
	{
		PlaySound(SOUND_LABEL_SE_DECIDE);
		SetFade(FADE_OUT, MODE_RANKING);
	}
}

void DrawTitle2(void)
{
	LPDIRECT3DDEVICE9 pDeviceTl = GetDevice();
	TITLE2 *pTitle2 = &g_aTitle2[0];

	pDeviceTl->SetStreamSource(0, g_pVtxBuffTitle2, 0, sizeof(VERTEX_2D));//í∏ì_Data flowÇÃê›íË
	pDeviceTl->SetFVF(FVF_VERTEX_2D);//í∏ì_modÇÃê›íË

	for (int nCntTitle = 0; nCntTitle < MAX_COMPONENT_TITLE2; nCntTitle++, pTitle2++)
	{
		if (pTitle2->bUse == true)
		{
			pDeviceTl->SetTexture(0, g_pTextureTitle2[nCntTitle]);//âÊëúê›íË
			pDeviceTl->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTitle * 4, 2);//í∏ì_ï`âÊ
		}
	}
}

void SetTitle2(void)
{
	//background1
	g_aTitle2[0].pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	g_aTitle2[0].size.x = SCREEN_WIDTH / 2;
	g_aTitle2[0].size.y = SCREEN_HEIGHT / 2;
	g_aTitle2[0].bUse = true;
	g_aTitle2[0].nPatterAnim = 0;
	//background2
	g_aTitle2[1].pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	g_aTitle2[1].size.x = SCREEN_WIDTH / 2;
	g_aTitle2[1].size.y = SCREEN_HEIGHT / 2;
	g_aTitle2[1].bUse = true;
	g_aTitle2[1].nPatterAnim = 0;
	//background3
	g_aTitle2[2].pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	g_aTitle2[2].size.x = SCREEN_WIDTH / 2;
	g_aTitle2[2].size.y = SCREEN_HEIGHT / 2;
	g_aTitle2[2].bUse = true;
	g_aTitle2[2].nPatterAnim = 0;
	//ufo
	g_aTitle2[3].pos = D3DXVECTOR3(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 2, 0.0f);
	g_aTitle2[3].size.x = 300;
	g_aTitle2[3].size.y = 200;
	g_aTitle2[3].bUse = true;
	g_aTitle2[3].nPatterAnim = 0;
	//start
	g_aTitle2[4].pos = D3DXVECTOR3(1100, 300, 0.0f);
	g_aTitle2[4].size.x = 70;
	g_aTitle2[4].size.y = 45;
	g_aTitle2[4].bUse = true;
	g_aTitle2[4].nPatterAnim = 0;
	//Tutorial
	g_aTitle2[5].pos = D3DXVECTOR3(1100, 400, 0.0f);
	g_aTitle2[5].size.x = 80;
	g_aTitle2[5].size.y = 45;
	g_aTitle2[5].bUse = true;
	g_aTitle2[5].nPatterAnim = 0;
	//Ranking
	g_aTitle2[6].pos = D3DXVECTOR3(1100, 500, 0.0f);
	g_aTitle2[6].size.x = 85;
	g_aTitle2[6].size.y = 40;
	g_aTitle2[6].bUse = true;
	g_aTitle2[6].nPatterAnim = 0;
	//Hand
	g_aTitle2[7].pos = D3DXVECTOR3(1000, 300, 0.0f);
	g_aTitle2[7].size.x = 25;
	g_aTitle2[7].size.y = 20;
	g_aTitle2[7].bUse = true;
	g_aTitle2[7].nPatterAnim = 0;
}