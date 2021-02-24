//=============================================================================
//
// [Enemy.cpp]
// Author : JITAKU YO
//
//=============================================================================
#include "Enemy.h"

MODEL *pEnemy;
int g_nCntTime = 0;
HRESULT InitEnemyMenu(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pEnemy = (MODEL*)malloc(ENEMY_NUM * sizeof(MODEL));
	float nCntPosz1 = -900.0f;
	float nCntPosz2 = -900.0f;
	float nCntPosz3 = -900.0f;
	float nCntPosz4 = -900.0f;
	for (int nCnt = 0; nCnt < ENEMY_NUM; nCnt++)
	{
		D3DXLoadMeshFromX("data/MODEL/SnowMan.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &pEnemy[nCnt].Xfile_Materials, NULL, &pEnemy[nCnt].Xfile_MaterialNum, &pEnemy[nCnt].Xfile_Mesh);
		pEnemy[nCnt].bUse = true;
		pEnemy[nCnt].rot = D3DXVECTOR3(0.f, 0.f, 0.f);
		pEnemy[nCnt].pos.y = -2.0f;
		if (nCnt < 15)
		{
			pEnemy[nCnt].pos.x = -50.f;
			pEnemy[nCnt].pos.z = nCntPosz1;
			nCntPosz1 += 100.f;
			pEnemy[nCnt].rot.y = D3DX_PI * 3 / 4;
		}
		else if (nCnt < 30)
		{
			pEnemy[nCnt].pos.x = 50.f;
			pEnemy[nCnt].pos.z = nCntPosz2;
			nCntPosz2 += 100.f;
			pEnemy[nCnt].rot.y = -D3DX_PI * 3 / 4;
		}
		else if (nCnt < 40)
		{
			pEnemy[nCnt].pos.x = -100.f;
			pEnemy[nCnt].pos.z = nCntPosz3;
			nCntPosz3 += 200.f;
			pEnemy[nCnt].rot.y = D3DX_PI * 3 / 4;
		}
		else
		{
			pEnemy[nCnt].pos.x = 100.f;
			pEnemy[nCnt].pos.z = nCntPosz4;
			nCntPosz4 += 200.f;
			pEnemy[nCnt].rot.y = -D3DX_PI * 3 / 4;
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


	//当たり判定用boxの設定
	int nNumVtx;//頂点数
	DWORD sizeFvF;//一つ頂点formatのsize
	BYTE *pVtxBuff;//頂点bufferへのpointer
	for (int nCnt = 0; nCnt < ENEMY_NUM; nCnt++)
	{
		nNumVtx = pEnemy[nCnt].Xfile_Mesh->GetNumVertices();//頂点数を取る
		sizeFvF = D3DXGetFVFVertexSize(pEnemy[nCnt].Xfile_Mesh->GetFVF());//formatの大きさ
		pEnemy[nCnt].Xfile_Mesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);//頂点buffをlock
		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;//頂点情報を取る
			pVtxBuff += sizeFvF;//次に行く

								//当たり判定用boxの頂点を探す
			if (nCntVtx == 0)//初めの頂点
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
		pEnemy[nCnt].MinColBox = pEnemy[nCnt].pos + pEnemy[nCnt].MinColBox;//minboxの値は負数

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
			D3DXMatrixIdentity(&mtxWorld);//単位matrix
			D3DXMatrixRotationYawPitchRoll(&mtxRot, pEnemy[nCnt].rot.y, pEnemy[nCnt].rot.x, pEnemy[nCnt].rot.z);//回転角度
			D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);//合算
			D3DXMatrixTranslation(&mtxTrans, pEnemy[nCnt].pos.x, pEnemy[nCnt].pos.y, pEnemy[nCnt].pos.z); //世界matrix全体　移動したい距離というmatrixの合算
			D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);//合算
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

MODEL *GetEnemy(void)
{
	return &pEnemy[0];
}