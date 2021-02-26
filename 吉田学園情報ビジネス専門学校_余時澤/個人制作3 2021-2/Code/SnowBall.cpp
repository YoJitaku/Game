#include "SnowBall.h"
#include "Dinput8.h"
#include "Camera.h"
#include "WorldModel.h"
#include "Collision.h"
#include "Enemy.h"
#include "UI.h"
#include "Player.h"

MODEL *pSnowBall;
float g_fGravity = 0.05f;
float g_fCol_Range;
HRESULT InitSnowBall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pSnowBall = (MODEL*)malloc(SNOWBALL_MAX_NUM * sizeof(MODEL));

	for (int nCnt = 0; nCnt < SNOWBALL_MAX_NUM; nCnt++)
	{
		D3DXLoadMeshFromX("data/MODEL/SnowBall.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &pSnowBall[nCnt].Xfile_Materials, NULL, &pSnowBall[nCnt].Xfile_MaterialNum, &pSnowBall[nCnt].Xfile_Mesh);
		pSnowBall[nCnt].bUse = false;
		pSnowBall[nCnt].pos = D3DXVECTOR3(0.f, 0.f, 0.f);
	}

	//BYTE *pVtxBuff;//���_buffer�ւ�pointer
	//D3DXVECTOR3 Sphere_Radius;
	//pSnowBall[0].Xfile_Mesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);//���_buff��lock
	//D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;//���_�������
	//Sphere_Radius = vtx - pSnowBall[0].pos;//�����a��vector
	//pSnowBall[0].Xfile_Mesh->UnlockVertexBuffer();//unlock
	//g_fCol_Range = sqrt(Sphere_Radius.x * Sphere_Radius.x + Sphere_Radius.y * Sphere_Radius.y + Sphere_Radius.z * Sphere_Radius.z);

	return S_OK;
}

void UninitSnowBall(void)
{
	free(pSnowBall);
}

void UpdateSnowBall(void)
{
	PLAYER *pPLayer = GetPlayer();

	for (int nCnt = 0; nCnt < SNOWBALL_MAX_NUM; nCnt++)
	{
		if (pSnowBall[nCnt].bUse == true)
		{
			pSnowBall[nCnt].move.y -= g_fGravity;
			pSnowBall[nCnt].pos += pSnowBall[nCnt].move;

			if (pSnowBall[nCnt].pos.y <= 0)
			{
				pSnowBall[nCnt].bUse = false;
			}
		}
		////�e�ƃJ�����̊ԋ���MAX_DISTANCE��艓���ꍇ�͒e������
		//D3DXVECTOR3 Distance = pSnowBall[nCnt].pos - pCamera->posV;
		//float fDistance = sqrtf(Distance.x * Distance.x + Distance.y * Distance.y + Distance.z * Distance.z);
		//if (fDistance > MAX_DISTANCE) pSnowBall[nCnt].bUse = false;
	}

	//�����蔻�� snowball��model�𓖂�������
	MODEL *pModel = GetWorldModel();
	for (int nCntBall = 0; nCntBall < SNOWBALL_MAX_NUM; nCntBall++)
	{
		bool bCol = false;
		if (pSnowBall[nCntBall].bUse == true)
		{
			for (int nCntMod = 0; nCntMod < WORLDMODEL_NUM; nCntMod++, pModel++)
			{
				bCol = CollisionDetection(pSnowBall[nCntBall].pos, pModel->MinColBox, pModel->MaxColBox);
				if (bCol == true) 
					pSnowBall[nCntBall].bUse = false;		
			}
		}
	}
	MODEL *pEnemy = GetEnemy();
	for (int nCntBall = 0; nCntBall < SNOWBALL_MAX_NUM; nCntBall++)
	{
		bool bCol = false;
		if (pSnowBall[nCntBall].bUse == true)
		{
			for (int nCntEnemy = 0; nCntEnemy < ENEMY_NUM; nCntEnemy++, pEnemy++)
			{
				if (pEnemy->bMove == true)
				{
					bCol = CollisionDetection(pSnowBall[nCntBall].pos, pEnemy->MinColBox, pEnemy->MaxColBox);
					if (bCol == true)
					{
						pSnowBall[nCntBall].bUse = false;
						pEnemy->pos.x -= -sinf(pEnemy->rot.y) * pEnemy->fMoveSpeed * 2;
						pEnemy->pos.z -= -cosf(pEnemy->rot.y) * pEnemy->fMoveSpeed * 2;
						pEnemy->pos.y += 10.f;
						pEnemy->bMove = false;
						pPLayer->nScore++;
						if (nCntEnemy % 2 == 0)
						{
							pEnemy->rot.x = -D3DX_PI / 2;
						}
						else
						{
							pEnemy->rot.x = D3DX_PI / 2;
						}
					}
				}
			}
		}
	}

}

void DrawSnowBall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans, mtxworld;
	D3DMATERIAL9 matDef;
	D3DXMATERIAL *pMaterials;
	for (int nCnt = 0; nCnt < SNOWBALL_MAX_NUM; nCnt++)
	{
		if (pSnowBall[nCnt].bUse == true)
		{
			D3DXMatrixIdentity(&mtxworld);//�P��matrix
			D3DXMatrixTranslation(&mtxTrans, pSnowBall[nCnt].pos.x, pSnowBall[nCnt].pos.y, pSnowBall[nCnt].pos.z); //���Ematrix�S�́@�ړ������������Ƃ���matrix�̍��Z
			D3DXMatrixMultiply(&mtxworld, &mtxworld, &mtxTrans); //���Z�@���Ematrix�̈ړ�
			pDevice->SetTransform(D3DTS_WORLD, &mtxworld); //set the world into Map
			pDevice->GetMaterial(&matDef);//�ގ������
			pMaterials = (D3DXMATERIAL*)pSnowBall[nCnt].Xfile_Materials->GetBufferPointer();
			for (DWORD nCntMat = 0; nCntMat < (int)pSnowBall[nCnt].Xfile_MaterialNum; nCntMat++)
			{
				pDevice->SetMaterial(&pMaterials[nCntMat].MatD3D);
				pDevice->SetTexture(0, NULL);
				pSnowBall[nCnt].Xfile_Mesh->DrawSubset(nCntMat);
			}
			pDevice->SetMaterial(&matDef);
		}
	}
}

void SetSnowBall(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	for (int nCnt = 0; nCnt < SNOWBALL_MAX_NUM; nCnt++)
	{
		if (pSnowBall[nCnt].bUse == false)
		{
			//�`��L����
			pSnowBall[nCnt].bUse = true;
			//���W������
			pSnowBall[nCnt].pos = pos;
			//�ړ����x
			pSnowBall[nCnt].move = move / SPEED_RADIO;
			pSnowBall[nCnt].move.y += 2.f;
			break;
		}
	}
}