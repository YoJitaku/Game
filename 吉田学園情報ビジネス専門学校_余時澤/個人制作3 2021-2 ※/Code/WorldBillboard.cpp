//=============================================================================
//
// [WorldBillboard.cpp]
// Author : JITAKU YO
//
//=============================================================================

#if 1
#define _CRT_SECURE_NO_WARNINGS
#include "WorldBillboard.h"

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWorldBillboard = NULL; //頂点bufferのpointer
LPDIRECT3DTEXTURE9 g_pTextureWorldBillboard[WORLDBILLBOARD_TEX_NUM] = {}; //textureのpointer
BILLBOARD *pWorldBillboard;

void ReadFileBillboard(void)
{
	FILE *pFile;
	pFile = fopen("WorldBillboard.txt", "r");
	for (int nCnt = 0; nCnt < WORLDBILLBOARD_NUM; nCnt++)
	{
		fscanf(pFile, "%f %f %f",
			&pWorldBillboard[nCnt].pos.x,
			&pWorldBillboard[nCnt].pos.y,
			&pWorldBillboard[nCnt].pos.z);

		pWorldBillboard[nCnt].nID = nCnt;
		pWorldBillboard[nCnt].nTextureID = rand() % 2;
		pWorldBillboard[nCnt].size = D3DXVECTOR2(80, 150);
		pWorldBillboard[nCnt].pos.y += pWorldBillboard[nCnt].size.y;
		pWorldBillboard[nCnt].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pWorldBillboard[nCnt].bUse = true;
	}
	fclose(pFile);
}

HRESULT InitWorldBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_3D *pVtx;
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Billboard/tree1.png", &g_pTextureWorldBillboard[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Billboard/tree2.png", &g_pTextureWorldBillboard[1]);
	//D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/tree3.png", &g_pTextureWorldBillboard[2]);
	//D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/grass1.png", &g_pTextureWorldBillboard[3]);
	//D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/grass2.png", &g_pTextureWorldBillboard[4]);

	pWorldBillboard = (BILLBOARD *)malloc(WORLDBILLBOARD_NUM * sizeof(BILLBOARD)); //メモリ定義
	ReadFileBillboard();

	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_3D) * WORLDBILLBOARD_NUM * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWorldBillboard,
		NULL)))
		return E_FAIL;
	g_pVtxBuffWorldBillboard->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < WORLDBILLBOARD_NUM; nCnt++, pVtx += 4)
	{
		pVtx[0].pos = D3DXVECTOR3(-pWorldBillboard[nCnt].size.x, pWorldBillboard[nCnt].size.y, 0.f);
		pVtx[1].pos = D3DXVECTOR3(pWorldBillboard[nCnt].size.x, pWorldBillboard[nCnt].size.y, 0.f);
		pVtx[2].pos = D3DXVECTOR3(-pWorldBillboard[nCnt].size.x, -pWorldBillboard[nCnt].size.y, 0.f);
		pVtx[3].pos = D3DXVECTOR3(pWorldBillboard[nCnt].size.x, -pWorldBillboard[nCnt].size.y, 0.f);
		pVtx[0].nor = pWorldBillboard[nCnt].nor;
		pVtx[1].nor = pWorldBillboard[nCnt].nor;
		pVtx[2].nor = pWorldBillboard[nCnt].nor;
		pVtx[3].nor = pWorldBillboard[nCnt].nor;
		pVtx[0].col = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
		pVtx[1].col = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
		pVtx[2].col = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
		pVtx[3].col = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
		pVtx[0].tex = D3DXVECTOR2(0.f, 0.f);
		pVtx[1].tex = D3DXVECTOR2(1.f, 0.f);
		pVtx[2].tex = D3DXVECTOR2(0.f, 1.f);
		pVtx[3].tex = D3DXVECTOR2(1.f, 1.f);
	}
	g_pVtxBuffWorldBillboard->Unlock();
	return S_OK;
}

void UninitWorldBillboard(void)
{
	if (g_pVtxBuffWorldBillboard != NULL)
		g_pVtxBuffWorldBillboard = NULL;
	for (int nCnt = 0; nCnt < WORLDBILLBOARD_TEX_NUM; nCnt++)
	{
		if (g_pTextureWorldBillboard[nCnt] != NULL)
			g_pTextureWorldBillboard[nCnt] = NULL;
	}
	free(pWorldBillboard);
}

void DrawWorldBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxTrans, WorldBillboard; //計算用のmatrix
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE); //close the lighting and diffuse effect
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER); //alpha test function
	pDevice->SetRenderState(D3DRS_ALPHAREF, 100); //alpha number
	for (int nCnt = 0; nCnt < WORLDBILLBOARD_NUM; nCnt++)
	{
		if (pWorldBillboard[nCnt].bUse == true)
		{
			D3DXMatrixIdentity(&WorldBillboard); //単位行列
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);
			//ポリゴンをカメラに対して正面に向ける
			D3DXMatrixInverse(&WorldBillboard, NULL, &mtxView);
			//平行移動の部分は無視する
			WorldBillboard._41 = 0.0f;
			WorldBillboard._42 = 0.0f;
			WorldBillboard._43 = 0.0f;
			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, pWorldBillboard[nCnt].pos.x, pWorldBillboard[nCnt].pos.y, pWorldBillboard[nCnt].pos.z); //世界matrix全体　移動したい距離というmatrixの合算
			D3DXMatrixMultiply(&WorldBillboard, &WorldBillboard, &mtxTrans); //世界matrixの移動
			
			pDevice->SetTransform(D3DTS_WORLD, &WorldBillboard); //set the world into Map
			pDevice->SetStreamSource(0, g_pVtxBuffWorldBillboard, 0, sizeof(VERTEX_3D));
			pDevice->SetFVF(FVF_VERTEX_3D);
			pDevice->SetTexture(0, g_pTextureWorldBillboard[pWorldBillboard[nCnt].nTextureID]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}
	//reset
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	//αテストを無効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);
}

#endif // 1