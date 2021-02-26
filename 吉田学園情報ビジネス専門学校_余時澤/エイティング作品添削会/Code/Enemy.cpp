//=============================================================================
//
// [Enemy.cpp]
// Author : JITAKU YO
//
//=============================================================================
#include "Enemy.h"

MODEL *pEnemy;
MODEL *pEnemyM;
int g_nCntTime = 0;
HRESULT InitEnemyMenu(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pEnemyM = (MODEL*)malloc(ENEMY_NUM * sizeof(MODEL));
	float nCntPosz1 = -900.0f;
	float nCntPosz2 = -900.0f;
	float nCntPosz3 = -900.0f;
	float nCntPosz4 = -900.0f;
	for (int nCnt = 0; nCnt < ENEMY_NUM; nCnt++)
	{
		D3DXLoadMeshFromX("data/MODEL/SnowMan.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &pEnemyM[nCnt].Xfile_Materials, NULL, &pEnemyM[nCnt].Xfile_MaterialNum, &pEnemyM[nCnt].Xfile_Mesh);
		pEnemyM[nCnt].bUse = true;
		pEnemyM[nCnt].rot = D3DXVECTOR3(0.f, 0.f, 0.f);
		pEnemyM[nCnt].pos.y = -2.0f;
		if (nCnt < 15)
		{
			pEnemyM[nCnt].pos.x = -50.f;
			pEnemyM[nCnt].pos.z = nCntPosz1;
			nCntPosz1 += 100.f;
			pEnemyM[nCnt].rot.y = D3DX_PI * 3 / 4;
		}
		else if (nCnt < 30)
		{
			pEnemyM[nCnt].pos.x = 50.f;
			pEnemyM[nCnt].pos.z = nCntPosz2;
			nCntPosz2 += 100.f;
			pEnemyM[nCnt].rot.y = -D3DX_PI * 3 / 4;
		}
		else if (nCnt < 40)
		{
			pEnemyM[nCnt].pos.x = -100.f;
			pEnemyM[nCnt].pos.z = nCntPosz3;
			nCntPosz3 += 200.f;
			pEnemyM[nCnt].rot.y = D3DX_PI * 3 / 4;
		}
		else
		{
			pEnemyM[nCnt].pos.x = 100.f;
			pEnemyM[nCnt].pos.z = nCntPosz4;
			nCntPosz4 += 200.f;
			pEnemyM[nCnt].rot.y = -D3DX_PI * 3 / 4;
		}
	}

	return S_OK;
}

HRESULT InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pEnemy = (MODEL*)malloc(ENEMY_NUM * sizeof(MODEL));
	for (int nCnt = 0; nCnt < ENEMY_NUM; nCnt++)
	{
		D3DXLoadMeshFromX("data/MODEL/SnowMan.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &pEnemy[nCnt].Xfile_Materials, NULL, &pEnemy[nCnt].Xfile_MaterialNum, &pEnemy[nCnt].Xfile_Mesh);
		SetEnemy();
	}


	//“–‚½‚è”»’è—pbox‚ÌÝ’è
	int nNumVtx;//’¸“_”
	DWORD sizeFvF;//ˆê‚Â’¸“_format‚Ìsize
	BYTE *pVtxBuff;//’¸“_buffer‚Ö‚Ìpointer
	for (int nCnt = 0; nCnt < ENEMY_NUM; nCnt++)
	{
		nNumVtx = pEnemy[nCnt].Xfile_Mesh->GetNumVertices();//’¸“_”‚ðŽæ‚é
		sizeFvF = D3DXGetFVFVertexSize(pEnemy[nCnt].Xfile_Mesh->GetFVF());//format‚Ì‘å‚«‚³
		pEnemy[nCnt].Xfile_Mesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);//’¸“_buff‚ðlock
		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;//’¸“_î•ñ‚ðŽæ‚é
			pVtxBuff += sizeFvF;//ŽŸ‚És‚­

								//“–‚½‚è”»’è—pbox‚Ì’¸“_‚ð’T‚·
			if (nCntVtx == 0)//‰‚ß‚Ì’¸“_
			{
				pEnemy[nCnt].MaxColBox = vtx;
				pEnemy[nCnt].MinColBox = vtx;
			}
			else
			{
				if (vtx.x > pEnemy[nCnt].MaxColBox.x) pEnemy[nCnt].MaxColBox.x = vtx.x;
				else if (vtx.x < pEnemy[nCnt].MinColBox.x) pEnemy[nCnt].MinColBox.x = vtx.x;
				if (vtx.y > pEnemy[nCnt].MaxColBox.y) pEnemy[nCnt].MaxColBox.y = vtx.y;
				else if (vtx.y < pEnemy[nCnt].MinColBox.y) pEnemy[nCnt].MinColBox.y = vtx.y;
				if (vtx.z > pEnemy[nCnt].MaxColBox.z) pEnemy[nCnt].MaxColBox.z = vtx.z;
				else if (vtx.z < pEnemy[nCnt].MinColBox.z) pEnemy[nCnt].MinColBox.z = vtx.z;
			}
		}
		pEnemy[nCnt].MaxColBox = pEnemy[nCnt].pos + pEnemy[nCnt].MaxColBox;
		pEnemy[nCnt].MinColBox = pEnemy[nCnt].pos + pEnemy[nCnt].MinColBox;//minbox‚Ì’l‚Í•‰”

		pEnemy[nCnt].Xfile_Mesh->UnlockVertexBuffer();//unlock
	}

	return S_OK;
}

void SetEnemy(void)
{
	for (int nCnt = 0; nCnt < ENEMY_NUM; nCnt++)
	{
		pEnemy[nCnt].bUse = true;
		pEnemy[nCnt].bMove = true;
		pEnemy[nCnt].pos.x = (float)(rand() % ENEMY_BORN_RANGE - ENEMY_BORN_RANGE / 2);
		pEnemy[nCnt].pos.z = (float)(rand() % ENEMY_BORN_RANGE - ENEMY_BORN_RANGE / 2);
		pEnemy[nCnt].pos.y = 0.0f;
		pEnemy[nCnt].fMoveSpeed = rand() % 3 + 1.f;
		pEnemy[nCnt].nMoveRange = rand() % 250 + 500;
		pEnemy[nCnt].move = D3DXVECTOR3(0.f, 0.f, 0.f);
		pEnemy[nCnt].rot = D3DXVECTOR3(0.f, 0.f, 0.f);
		pEnemy[nCnt].rot.y = (rand() % 314) / 100.f * D3DX_PI;
	}
}

void UninitEnemy(void)
{
	free(pEnemy);
}

void UninitEnemyM(void)
{
	free(pEnemyM);
}

void UpdateEnemy(void)
{
	g_nCntTime++;
	MODE mode = GetMode();
	if (mode == MODE_GAME || mode == MODE_RANKING)
	{
		for (int nCnt = 0; nCnt < ENEMY_NUM; nCnt++)
		{
			if (pEnemy[nCnt].bUse == true && pEnemy[nCnt].bMove == true)
			{
				pEnemy[nCnt].move.x = sinf(pEnemy[nCnt].rot.y) * pEnemy[nCnt].fMoveSpeed;
				pEnemy[nCnt].move.z = cosf(pEnemy[nCnt].rot.y) * pEnemy[nCnt].fMoveSpeed;
				int nCntRange = (int)sqrt(pEnemy[nCnt].move.x * pEnemy[nCnt].move.x + pEnemy[nCnt].move.z * pEnemy[nCnt].move.z);
				pEnemy[nCnt].nMoveRange -= nCntRange;
				pEnemy[nCnt].pos += pEnemy[nCnt].move;
				pEnemy[nCnt].MaxColBox += pEnemy[nCnt].move;
				pEnemy[nCnt].MinColBox += pEnemy[nCnt].move;
				if (pEnemy[nCnt].nMoveRange <= 0)
				{
					pEnemy[nCnt].nMoveRange = rand() % 250 + 500;
					pEnemy[nCnt].rot.y = (rand() % 314) / 100.f * D3DX_PI;
				}
			}
		}
	}
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

void DrawEnemyM(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans, mtxWorld;
	D3DMATERIAL9 matDef;
	D3DXMATERIAL *pMat;

	for (int nCnt = 0; nCnt < ENEMY_NUM; nCnt++)
	{
		if (pEnemyM[nCnt].bUse == true)
		{
			D3DXMatrixIdentity(&mtxWorld);//’PˆÊmatrix
			D3DXMatrixRotationYawPitchRoll(&mtxRot, pEnemyM[nCnt].rot.y, pEnemyM[nCnt].rot.x, pEnemyM[nCnt].rot.z);//‰ñ“]Šp“x
			D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);//‡ŽZ
			D3DXMatrixTranslation(&mtxTrans, pEnemyM[nCnt].pos.x, pEnemyM[nCnt].pos.y, pEnemyM[nCnt].pos.z); //¢ŠEmatrix‘S‘Ì@ˆÚ“®‚µ‚½‚¢‹——£‚Æ‚¢‚¤matrix‚Ì‡ŽZ
			D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);//‡ŽZ
			pDevice->SetTransform(D3DTS_WORLD, &mtxWorld); //set the world into Map
			pDevice->GetMaterial(&matDef);
			pMat = (D3DXMATERIAL*)pEnemyM[nCnt].Xfile_Materials->GetBufferPointer();
			for (int nCntMat = 0; nCntMat < (int)pEnemyM[nCnt].Xfile_MaterialNum; nCntMat++)
			{
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				pDevice->SetTexture(0, NULL);
				pEnemyM[nCnt].Xfile_Mesh->DrawSubset(nCntMat);
			}
			pDevice->SetMaterial(&matDef);
		}
	}
}

MODEL *GetEnemy(void)
{
	return &pEnemy[0];
}