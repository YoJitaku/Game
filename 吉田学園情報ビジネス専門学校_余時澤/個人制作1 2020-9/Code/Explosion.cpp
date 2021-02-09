//=============================================================================
//
// [Explosion.cpp]
// Author : Yo Jitaku
//
//=============================================================================
#include "explosion.h"
#include "Sound.h"

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;//explosionのbuffer
LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL;//画像のpointer
EXPLOSION g_pExplosion[EXPLOSION_NUMBER];//explosionの構造体

int g_nCounterAnimEp = 0;

HRESULT InitExplosion(void)
{
	//pointerを定義する
	EXPLOSION *pExplosion = &g_pExplosion[0];
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDeviceEp = GetDevice();

	D3DXCreateTextureFromFile(pDeviceEp, "data/TEXTURE/explosion000.png", &g_pTextureExplosion);
	if (FAILED(pDeviceEp->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * EXPLOSION_NUMBER, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffExplosion, NULL))) return E_FAIL;
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntExplosion = 0; nCntExplosion < EXPLOSION_NUMBER; nCntExplosion++, pExplosion++, pVtx += 4)
	{
		//初期化
		pExplosion->pos.x = 0;
		pExplosion->pos.y = 0;
		pExplosion->pos.z = 0;
		pExplosion->nPatterAnim = 0;
		pExplosion->bUse = false;
		pExplosion->nsize = 30;

		pVtx[0].pos = D3DXVECTOR3(pExplosion->pos.x - pExplosion->nsize, pExplosion->pos.y - pExplosion->nsize, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(pExplosion->pos.x + pExplosion->nsize, pExplosion->pos.y - pExplosion->nsize, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(pExplosion->pos.x - pExplosion->nsize, pExplosion->pos.y + pExplosion->nsize, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(pExplosion->pos.x + pExplosion->nsize, pExplosion->pos.y + pExplosion->nsize, 0.0f);
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 250, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 250, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 250, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 250, 255);
		pVtx[0].tex = D3DXVECTOR2((float)(0.125 * pExplosion->nPatterAnim), 0);
		pVtx[1].tex = D3DXVECTOR2((float)(0.125 * (pExplosion->nPatterAnim + 1)), 0);
		pVtx[2].tex = D3DXVECTOR2((float)(0.125 * pExplosion->nPatterAnim), 1);
		pVtx[3].tex = D3DXVECTOR2((float)(0.125 * (pExplosion->nPatterAnim + 1)), 1);
		g_pVtxBuffExplosion->Unlock();
	}
	return S_OK;
}

void UninitExplosion(void)
{
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}
}

void UpdateExplosion(void)
{
	EXPLOSION *pExplosion = &g_pExplosion[0];
	VERTEX_2D *pVtx;
	g_nCounterAnimEp++;//animation activate, speed control

	if (g_nCounterAnimEp % 5 == 0)
	{
		g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
		for (int nCntExplosion = 0; nCntExplosion < EXPLOSION_NUMBER; nCntExplosion++, pExplosion++, pVtx += 4)
		{
			if (pExplosion->bUse == true)
			{
				if (pExplosion->nPatterAnim == 8)//一回animationを終わったら停止
				{
					pExplosion->nPatterAnim = 0;
					pExplosion->bUse = false;
					break;
				}
				else
				{
					pVtx[0].pos = D3DXVECTOR3(pExplosion->pos.x - pExplosion->nsize, pExplosion->pos.y - pExplosion->nsize, 0.0f);
					pVtx[1].pos = D3DXVECTOR3(pExplosion->pos.x + pExplosion->nsize, pExplosion->pos.y - pExplosion->nsize, 0.0f);
					pVtx[2].pos = D3DXVECTOR3(pExplosion->pos.x - pExplosion->nsize, pExplosion->pos.y + pExplosion->nsize, 0.0f);
					pVtx[3].pos = D3DXVECTOR3(pExplosion->pos.x + pExplosion->nsize, pExplosion->pos.y + pExplosion->nsize, 0.0f);
					pVtx[0].tex = D3DXVECTOR2((float)(0.125 * pExplosion->nPatterAnim), 0);
					pVtx[1].tex = D3DXVECTOR2((float)(0.125 * (pExplosion->nPatterAnim + 1)), 0);
					pVtx[2].tex = D3DXVECTOR2((float)(0.125 * pExplosion->nPatterAnim), 1);
					pVtx[3].tex = D3DXVECTOR2((float)(0.125 * (pExplosion->nPatterAnim + 1)), 1);
				}
				pExplosion->nPatterAnim++;//animation next frame
			}
		}
		g_pVtxBuffExplosion->Unlock();
	}
}

void DrawExplosion(void)
{
	EXPLOSION *pExplosion = &g_pExplosion[0];
	LPDIRECT3DDEVICE9 pDeviceEp = GetDevice();
	pDeviceEp->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_2D));//explosion画像の頂点Data flowの設定
	pDeviceEp->SetFVF(FVF_VERTEX_2D);//頂点modの設定
	pDeviceEp->SetTexture(0, g_pTextureExplosion);//explosion画像設定
	for (int nCntExplosion = 0; nCntExplosion < EXPLOSION_NUMBER; nCntExplosion++, pExplosion++)
	{
		if (pExplosion->bUse == true)
		{
			//描画(1,ploygonの種類　2,始める頂点　3,polygonの数(2つD3DPT_TRIANGLESTRIP三角形))
			pDeviceEp->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntExplosion * 4, 2);
		}
	}
}

//外部輸入explosionをするところの座標
void SetExplosion(D3DXVECTOR3 pos, int size)
{
	VERTEX_2D *pVtx;
	EXPLOSION *pExplosion = &g_pExplosion[0];

	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntExplosion = 0; nCntExplosion < EXPLOSION_NUMBER; nCntExplosion++, pExplosion++, pVtx += 4)
	{
		if (pExplosion->bUse == false)
		{
			pExplosion->pos = pos;
			pExplosion->nPatterAnim = 0;
			pExplosion->bUse = true;
			pExplosion->nsize = size;
			PlaySound(SOUND_LABEL_SE_EXPLOSIONENEMY);

			//important! ここで座標を一回更新する必要がある。もしなっかたら前回animation最後のframe情報を残している。(前回の座標は次のupdateで更新する,今回draw処理の後)
			pVtx[0].pos = D3DXVECTOR3(pExplosion->pos.x - pExplosion->nsize, pExplosion->pos.y - pExplosion->nsize, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(pExplosion->pos.x + pExplosion->nsize, pExplosion->pos.y - pExplosion->nsize, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(pExplosion->pos.x - pExplosion->nsize, pExplosion->pos.y + pExplosion->nsize, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(pExplosion->pos.x + pExplosion->nsize, pExplosion->pos.y + pExplosion->nsize, 0.0f);
			break;
		}
	}
	g_pVtxBuffExplosion->Unlock();
}