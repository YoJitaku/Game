#include "FootPrint.h"

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFootPrint = NULL;
LPDIRECT3DTEXTURE9 g_pTextureFootPrint[FOOT_PRINT_FILE_NUM] = {};
BILLBOARD *pFootParticle;
POLYGON_3D *pFootTexture;

HRESULT InitFootPrint(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_3D *pVtx;
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/FootPrint/LeftFoot.png", &g_pTextureFootPrint[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/FootPrint/RightFoot.png", &g_pTextureFootPrint[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/FootPrint/FootPrintParticle.png", &g_pTextureFootPrint[2]);

	pFootParticle = (BILLBOARD *)malloc(FOOT_PRINT_PARTICLE_POLY * sizeof(BILLBOARD));
	pFootTexture = (POLYGON_3D *)malloc(FOOT_PRINT_TEXTURE_POLY * sizeof(POLYGON_3D));

	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * (FOOT_PRINT_PARTICLE_POLY + FOOT_PRINT_TEXTURE_POLY) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFootPrint,
		NULL)))
		return E_FAIL;

	//Init FOOT_PRINT_TEXTURE_POLY
	for (int nCnt = 0; nCnt < FOOT_PRINT_TEXTURE_POLY; nCnt++)
	{
		//pFootTexture[nCnt].pos = D3DXVECTOR3(0.f, 0.f, 0.f);
		//pFootTexture[nCnt].nor = D3DXVECTOR3(0.f, 1.f, 0.f);
		//pFootTexture[nCnt].rot = D3DXVECTOR3(0.f, 0.f, 0.f);
		//pFootTexture[nCnt].size = D3DXVECTOR2(50.f, 50.f);
	}
	
	g_pVtxBuffFootPrint->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < FOOT_PRINT_PARTICLE_POLY; nCnt++, pVtx += 4)
	{

	}
	for (int nCnt = 0; nCnt < FOOT_PRINT_TEXTURE_POLY; nCnt++, pVtx += 4)
	{

	}
	g_pVtxBuffFootPrint->Unlock();
	return S_OK;
}
void UninitFootPrint(void)
{
	if (g_pVtxBuffFootPrint != NULL)
	{
		g_pVtxBuffFootPrint->Release();
		g_pVtxBuffFootPrint = NULL;
	}
	for (int nCnt = 0; nCnt < FOOT_PRINT_FILE_NUM; nCnt++)
	{
		if (g_pTextureFootPrint[nCnt] != NULL)
		{
			g_pTextureFootPrint[nCnt]->Release();
			g_pTextureFootPrint[nCnt] = NULL;
		}
	}
	free(pFootParticle);
	free(pFootTexture);
}
void UpdateFootPrint(void)
{

}
void DrawFootPrint(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans, mtxWorld;

	for (int nCnt = 0; nCnt < FOOT_PRINT_PARTICLE_POLY; nCnt++)
	{

	}
	for (int nCnt = 0; nCnt < FOOT_PRINT_TEXTURE_POLY; nCnt++)
	{

	}
}
void SetFootPrint(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{

}