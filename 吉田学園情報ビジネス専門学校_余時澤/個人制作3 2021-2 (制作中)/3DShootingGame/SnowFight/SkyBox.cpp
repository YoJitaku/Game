//=============================================================================
//
// [SkyBox.cpp]
// Author : JITAKU YO
//
//=============================================================================
#include "SkyBox.h"

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSkyBox = NULL;
LPDIRECT3DTEXTURE9 g_pTextureSkyBox[SKYBOX_POLY] = {};
D3DXMATRIX g_WorldMtxSkyBox;//単位行列
float g_Length = SKYBOX_LENGTH * 1.1f;//int -> float
//int g_nCntTime = 0;
POLYGON_3D *pSkyBox;

void SetSkyBox(void)
{
	pSkyBox[0].pos = D3DXVECTOR3(0.f, 0.f, SKYBOX_LENGTH);
	pSkyBox[0].rot = D3DXVECTOR3(0.f, 0.f, 0.f);
	pSkyBox[0].nor = D3DXVECTOR3(0.f, 0.f, 1.f);

	pSkyBox[1].pos = D3DXVECTOR3(0.f, 0.f, -SKYBOX_LENGTH);
	pSkyBox[1].rot = D3DXVECTOR3(0.f, D3DX_PI, 0.f);
	pSkyBox[1].nor = D3DXVECTOR3(0.f, 0.f, 1.f);

	pSkyBox[2].pos = D3DXVECTOR3(-SKYBOX_LENGTH, 0.f, 0.f);
	pSkyBox[2].rot = D3DXVECTOR3(0.f, -D3DX_PI / 2, 0.f);
	pSkyBox[2].nor = D3DXVECTOR3(-1.f, 0.f, 0.f);

	pSkyBox[3].pos = D3DXVECTOR3(SKYBOX_LENGTH, 0.f, 0.f);
	pSkyBox[3].rot = D3DXVECTOR3(0.f, D3DX_PI / 2, 0.f);
	pSkyBox[3].nor = D3DXVECTOR3(1.f, 0.f, 0.f);

	pSkyBox[4].pos = D3DXVECTOR3(0.f, SKYBOX_LENGTH, 0.f);
	pSkyBox[4].rot = D3DXVECTOR3(-D3DX_PI / 2, 0.f, 0.f);
	pSkyBox[4].nor = D3DXVECTOR3(-1.f, 0.f, 0.f);
}
HRESULT InitSkyBox(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_3D *pVtx;

	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/SkyBox/Front.jpg", &g_pTextureSkyBox[0]);  //前
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/SkyBox/Back.jpg", &g_pTextureSkyBox[1]);  //後ろ
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/SkyBox/Left.jpg", &g_pTextureSkyBox[2]);  //左
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/SkyBox/Right.jpg", &g_pTextureSkyBox[3]);  //右
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/SkyBox/Top.jpg", &g_pTextureSkyBox[4]);  //上

	pSkyBox = (POLYGON_3D *)malloc(SKYBOX_POLY * sizeof(POLYGON_3D)); //メモリ定義
	SetSkyBox();
	if (FAILED(pDevice->CreateVertexBuffer(256 * sizeof(VERTEX_3D),
		D3DUSAGE_WRITEONLY,
		D3DFVF_SKYBOX, 
		D3DPOOL_MANAGED,
		&g_pVtxBuffSkyBox,
		NULL)))
		return E_FAIL;

	g_pVtxBuffSkyBox->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < SKYBOX_POLY; nCnt++, pVtx += 4)
	{
		pVtx[0].pos = D3DXVECTOR3(-SKYBOX_LENGTH , SKYBOX_LENGTH , 0.f);
		pVtx[1].pos = D3DXVECTOR3(SKYBOX_LENGTH , SKYBOX_LENGTH , 0.f);
		pVtx[2].pos = D3DXVECTOR3(-SKYBOX_LENGTH , -SKYBOX_LENGTH , 0.f);
		pVtx[3].pos = D3DXVECTOR3(SKYBOX_LENGTH , -SKYBOX_LENGTH , 0.f);

		pVtx[0].nor = pSkyBox[nCnt].nor;
		pVtx[1].nor = pSkyBox[nCnt].nor;
		pVtx[2].nor = pSkyBox[nCnt].nor;
		pVtx[3].nor = pSkyBox[nCnt].nor;

		pVtx[0].col = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
		pVtx[1].col = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
		pVtx[2].col = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
		pVtx[3].col = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);

		pVtx[0].tex = D3DXVECTOR2(0.f, 0.f);
		pVtx[1].tex = D3DXVECTOR2(1.f, 0.f);
		pVtx[2].tex = D3DXVECTOR2(0.f, 1.f);
		pVtx[3].tex = D3DXVECTOR2(1.f, 1.f);
	}
	g_pVtxBuffSkyBox->Unlock();

	return S_OK;
}

void UninitSkyBox(void)
{

}

void DrawSkyBox(void)
{
	//g_nCntTime++;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxTrans, mtxRot, matRotSky;
	for (int nCnt = 0; nCnt < SKYBOX_POLY; nCnt++)
	{
		D3DXMatrixIdentity(&g_WorldMtxSkyBox); //単位行列
		D3DXMatrixRotationYawPitchRoll(&mtxRot, pSkyBox[nCnt].rot.y, pSkyBox[nCnt].rot.x, pSkyBox[nCnt].rot.z); //the opreation is Roll->Pitch->Yaw 最後output回されたmatrix
		D3DXMatrixMultiply(&g_WorldMtxSkyBox, &g_WorldMtxSkyBox, &mtxRot); //世界matrixの周り　Param1 out put matrix = 世界matrix * 回されたmatrix
		//D3DXMatrixRotationY(&matRotSky, -0.0005f * g_nCntTime);
		//D3DXMatrixMultiply(&g_WorldMtxSkyBox, &g_WorldMtxSkyBox, &matRotSky);
		D3DXMatrixTranslation(&mtxTrans, pSkyBox[nCnt].pos.x, pSkyBox[nCnt].pos.y, pSkyBox[nCnt].pos.z); //世界matrix全体　移動したい距離というmatrixの合算
		D3DXMatrixMultiply(&g_WorldMtxSkyBox, &g_WorldMtxSkyBox, &mtxTrans); //世界matrixの移動
		pDevice->SetTransform(D3DTS_WORLD, &g_WorldMtxSkyBox); //set the world into Map
		pDevice->SetStreamSource(0, g_pVtxBuffSkyBox, 0, sizeof(VERTEX_3D));
		pDevice->SetFVF(FVF_VERTEX_3D);
		pDevice->SetTexture(0, g_pTextureSkyBox[nCnt]);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
	}
}