//=============================================================================
//
// [SnowParticle.cpp]
// Author : JITAKU YO
//
//=============================================================================
#include "SnowParticle.h"

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSnowParticle = NULL; //í∏ì_bufferÇÃpointer
LPDIRECT3DTEXTURE9 g_pTextureSnowParticle[SNOW_TYPE]; //textureÇÃpointer
SNOWPARTICLE pSnow[PARTICLE_NUM];
WIND Wind;
int g_nCntTimeParticle;
float g_fWindx, g_fWindz;//ïóå¸Ç´(snowç¿ïWçXêVóp)

HRESULT InitSnowParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_3D *pVtx;
	g_nCntTimeParticle = 0;
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Snow/Snow1.png", &g_pTextureSnowParticle[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Snow/Snow2.png", &g_pTextureSnowParticle[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Snow/Snow3.png", &g_pTextureSnowParticle[2]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Snow/Snow4.png", &g_pTextureSnowParticle[3]);

	Wind.fRotSpeed = 0.0f;
	Wind.fWindSpeed = 50.f;
	Wind.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	for (int nCnt = 0; nCnt < PARTICLE_NUM; nCnt++)
	{
		pSnow[nCnt].pos.x = (float)(rand() % SNOW_RANGE_X - SNOW_RANGE_X / 2);
		pSnow[nCnt].pos.z = (float)(rand() % SNOW_RANGE_Z - SNOW_RANGE_Z / 2);
		pSnow[nCnt].pos.y = (float)(rand() % (SNOW_RANGE_Y / 2));
		pSnow[nCnt].fFallSpeed = (rand() % 50 + FALL_SPEED) / 80.f;
		pSnow[nCnt].rot.x = (rand() % 314) / 100.f * D3DX_PI;
		pSnow[nCnt].rot.y = (rand() % 314) / 100.f * D3DX_PI;
		pSnow[nCnt].rot.z = (rand() % 314) / 100.f * D3DX_PI;
		pSnow[nCnt].fRotSpeed = (rand() % 10 + ROT_SPEED) / 100.f ;
		pSnow[nCnt].TextureIndex = rand() % 4;
	}

	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * PARTICLE_NUM * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSnowParticle,
		NULL)))
		return E_FAIL;
		
	g_pVtxBuffSnowParticle->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < PARTICLE_NUM; nCnt++, pVtx += 4)
	{
		pVtx[0].pos = D3DXVECTOR3(-SNOW_SIZE, -SNOW_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(+SNOW_SIZE, -SNOW_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-SNOW_SIZE, +SNOW_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(+SNOW_SIZE, +SNOW_SIZE, 0.0f);
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[0].nor = D3DXVECTOR3(0.f, 1.f, 0.f);
		pVtx[1].nor = D3DXVECTOR3(0.f, 1.f, 0.f);
		pVtx[2].nor = D3DXVECTOR3(0.f, 1.f, 0.f);
		pVtx[3].nor = D3DXVECTOR3(0.f, 1.f, 0.f);
		pVtx[0].tex = D3DXVECTOR2(0.0, 0.0);
		pVtx[1].tex = D3DXVECTOR2(1.0, 0.0);
		pVtx[2].tex = D3DXVECTOR2(0.0, 1.0);
		pVtx[3].tex = D3DXVECTOR2(1.0, 1.0);
	}
	g_pVtxBuffSnowParticle->Unlock();
	return S_OK;
}

void UninitSnowParticle(void)
{
	if (g_pVtxBuffSnowParticle != NULL)
	{
		g_pVtxBuffSnowParticle->Release();
		g_pVtxBuffSnowParticle = NULL;
	}
	for (int nCnt = 0; nCnt < SNOW_TYPE; nCnt++)
	{
		if (g_pTextureSnowParticle[nCnt] != NULL)
		{
			g_pTextureSnowParticle[nCnt]->Release();
			g_pTextureSnowParticle[nCnt] = NULL;
		}
	}
}

void UpdateSnowParticle(void)
{
	g_nCntTimeParticle++;
	if (g_nCntTimeParticle % 1000 == 0 || g_nCntTimeParticle == 1)
	{
		g_fWindx = g_fWindz = 0.0f;
		Wind.fWindSpeed = rand() % 50 / 10.f;
		Wind.fRotSpeed = (float)(2.0f / 50.f) * D3DX_PI;
		Wind.rot.y += Wind.fRotSpeed;
		g_fWindx = (float)cos(Wind.rot.y) * Wind.fWindSpeed;
		g_fWindz = (float)sin(Wind.rot.y) * Wind.fWindSpeed;
	}
	
	for (int nCnt = 0; nCnt < PARTICLE_NUM; nCnt++)
	{
		pSnow[nCnt].pos.y -= pSnow[nCnt].fFallSpeed;
		if (pSnow[nCnt].pos.y <= 0)
		{
			pSnow[nCnt].pos.x = (float)(rand() % SNOW_RANGE_X - SNOW_RANGE_X / 2);
			pSnow[nCnt].pos.z = (float)(rand() % SNOW_RANGE_Z - SNOW_RANGE_Z / 2);
			pSnow[nCnt].pos.y = (float)(rand() % (SNOW_RANGE_Y / 2));
		}
		pSnow[nCnt].pos.x += g_fWindx;
		pSnow[nCnt].pos.z += g_fWindz;
		pSnow[nCnt].rot.x += pSnow[nCnt].fRotSpeed;
		pSnow[nCnt].rot.y += pSnow[nCnt].fRotSpeed;
	}
}

void DrawSnowParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans, mtxWorld;
	
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);//óºñ ï`âÊ

	for (int nCnt = 0; nCnt < PARTICLE_NUM; nCnt++)
	{
		D3DXMatrixIdentity(&mtxWorld);//íPà matrix
		D3DXMatrixRotationYawPitchRoll(&mtxRot, pSnow[nCnt].rot.y, pSnow[nCnt].rot.x, pSnow[nCnt].rot.z);//âÒì]äpìx
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);//çáéZ
		D3DXMatrixTranslation(&mtxTrans, pSnow[nCnt].pos.x, pSnow[nCnt].pos.y, pSnow[nCnt].pos.z); //ê¢äEmatrixëSëÃÅ@à⁄ìÆÇµÇΩÇ¢ãóó£Ç∆Ç¢Ç§matrixÇÃçáéZ
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);//çáéZ
		pDevice->SetTransform(D3DTS_WORLD, &mtxWorld); //set the world into Map
		pDevice->SetStreamSource(0, g_pVtxBuffSnowParticle, 0, sizeof(VERTEX_3D));
		pDevice->SetFVF(FVF_VERTEX_3D);
		pDevice->SetTexture(0, g_pTextureSnowParticle[pSnow[nCnt].TextureIndex]);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
	}
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);//ó†ñ ï`âÊÇµÇ»Ç¢
}
