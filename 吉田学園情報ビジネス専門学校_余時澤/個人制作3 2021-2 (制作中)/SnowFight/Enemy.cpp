//=============================================================================
//
// [Enemy.cpp]
// Author : JITAKU YO
//
//=============================================================================
#include "Enemy.h"

MODEL *pEnemy;

HRESULT InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pEnemy = (MODEL*)malloc(ENEMY_NUM * sizeof(MODEL));
	for (int nCnt = 0; nCnt < ENEMY_NUM; nCnt++)
	{
		D3DXLoadMeshFromX("data/MODEL/SnowMan.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &pEnemy[nCnt].Xfile_Materials, NULL, &pEnemy[nCnt].Xfile_MaterialNum, &pEnemy[nCnt].Xfile_Mesh);
		SetEnemy();
	}
	return S_OK;
}

void SetEnemy(void)
{
	for (int nCnt = 0; nCnt < ENEMY_NUM; nCnt++)
	{
		pEnemy[nCnt].bUse = true;
		pEnemy[nCnt].pos.x = (float)(rand() % ENEMY_BORN_RANGE - ENEMY_BORN_RANGE / 2);
		pEnemy[nCnt].pos.z = (float)(rand() % ENEMY_BORN_RANGE - ENEMY_BORN_RANGE / 2);
		pEnemy[nCnt].pos.y = 0.0f;
		pEnemy[nCnt].rot = D3DXVECTOR3(0.f, 0.f, 0.f);
		pEnemy[nCnt].rot.y = (rand() % 314) / 100.f * D3DX_PI;
	}
}

void UninitEnemy(void)
{
	free(pEnemy);
}

void UpdateEnemy(void)
{

}

void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans, mtxWorld;
	D3DMATERIAL9 matDef;
	D3DXMATERIAL *pMat;

	for (int nCnt = 0; nCnt < ENEMY_NUM; nCnt++)
	{
		if (pEnemy[nCnt].bUse == true)
		{
			D3DXMatrixIdentity(&mtxWorld);//’PˆÊmatrix
			D3DXMatrixRotationYawPitchRoll(&mtxRot, pEnemy[nCnt].rot.y, pEnemy[nCnt].rot.x, pEnemy[nCnt].rot.z);//‰ñ“]Šp“x
			D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);//‡ŽZ
			D3DXMatrixTranslation(&mtxTrans, pEnemy[nCnt].pos.x, pEnemy[nCnt].pos.y, pEnemy[nCnt].pos.z); //¢ŠEmatrix‘S‘Ì@ˆÚ“®‚µ‚½‚¢‹——£‚Æ‚¢‚¤matrix‚Ì‡ŽZ
			D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);//‡ŽZ
			pDevice->SetTransform(D3DTS_WORLD, &mtxWorld); //set the world into Map
			pDevice->GetMaterial(&matDef);
			pMat = (D3DXMATERIAL*)pEnemy[nCnt].Xfile_Materials->GetBufferPointer();
			for (int nCntMat = 0; nCntMat < (int)pEnemy[nCnt].Xfile_MaterialNum; nCntMat++)
			{
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				pDevice->SetTexture(0, NULL);
				pEnemy[nCnt].Xfile_Mesh->DrawSubset(nCntMat);
			}
			pDevice->SetMaterial(&matDef);
		}
	}
}