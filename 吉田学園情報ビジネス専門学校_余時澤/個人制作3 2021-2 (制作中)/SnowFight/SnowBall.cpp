#include "SnowBall.h"
#include "Dinput8.h"
#include "Camera.h"
#include "WorldModel.h"

MODEL *pSnowBall;
float g_fGravity = 0.05f;
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

	return S_OK;
}

void UninitSnowBall(void)
{
	free(pSnowBall);
}

void UpdateSnowBall(void)
{
	CAMERA *pCamera = GetCamera();

	if (GetkeyboardRelease(DIK_SPACE) == true)
	{
		for (int nCnt = 0; nCnt < SNOWBALL_MAX_NUM; nCnt++)
		{
			if (pSnowBall[nCnt].bUse == false)
			{
				//�`��L����
				pSnowBall[nCnt].bUse = true;
				//���W������
				pSnowBall[nCnt].pos.x = pCamera->posR.x + 20.f;
				pSnowBall[nCnt].pos.y = pCamera->posR.y + 20.f;
				pSnowBall[nCnt].pos.z = pCamera->posR.z;
				//�ړ����x
				pSnowBall[nCnt].move = (pCamera->posR - pCamera->posV) / SPEED_RADIO;
				pSnowBall[nCnt].move.y += 2.f;
				break;
			}
		}
	}
	
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
	//BYTE *pVtxBuff;//���_buffer�ւ�pointer
	//D3DXVECTOR3 Sphere_Radius;
	//for (int nCnt = 0; nCnt < SNOWBALL_MAX_NUM; nCnt++)
	//{
	//	if (pSnowBall[nCnt].bUse == true)
	//	{
	//		pSnowBall[nCnt].Xfile_Mesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);//���_buff��lock
	//		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;//���_�������
	//		Sphere_Radius = vtx - pSnowBall[nCnt].pos;//�����a��vector
	//		pSnowBall[nCnt].Xfile_Mesh->UnlockVertexBuffer();//unlock

	//		for (int nCnt = 0; nCnt < WORLDMODEL_NUM; nCnt++)
	//		{

	//		}
	//	}
	//}
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
			pSnowBall[nCnt].move = move;
			
			break;
		}
	}
}