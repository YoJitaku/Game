//=============================================================================
//
// [WorldModel.cpp]
// Author : JITAKU YO
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include "WorldModel.h"
#include "Camera.h"
#include "Collision.h"
//#include "Shadow.h"

MODEL *pWorldModel;
D3DXMATERIAL *pMaterials;
COLLISION_BOX *pCol_Box;
void InitWorldModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//VERTEX_3D *pVtx;
	pWorldModel = (MODEL*)malloc(WORLDMODEL_NUM * sizeof(MODEL));
	pCol_Box = (COLLISION_BOX*)malloc(WORLDMODEL_NUM * sizeof(COLLISION_BOX));
	SetWorldModel();

	//�ގ���UV�e�N�X�`����ǂݍ���
	for (int nCnt1 = 0; nCnt1 < WORLDMODEL_NUM; nCnt1++)
	{
		pMaterials = (D3DXMATERIAL*)pWorldModel[nCnt1].Xfile_Materials->GetBufferPointer();
		for (DWORD nCnt = 0; nCnt < (int)pWorldModel[nCnt1].Xfile_MaterialNum; nCnt++)
		{
			if (pMaterials[nCnt].pTextureFilename != NULL)
			{
				char* file_name = pMaterials[nCnt].pTextureFilename;
				LPDIRECT3DTEXTURE9 texture = NULL;
				D3DXCreateTextureFromFileA(pDevice,
					file_name,
					&pWorldModel[nCnt1].g_Textures[nCnt]);
			}
			else
			{
				pWorldModel[nCnt1].g_Textures[nCnt] = nullptr;
			}
		}
	}

	//�����蔻��pbox�̐ݒ�
	int nNumVtx;//���_��
	DWORD sizeFvF;//����_format��size
	BYTE *pVtxBuff;//���_buffer�ւ�pointer
	for (int nCnt = 0; nCnt < WORLDMODEL_NUM; nCnt++)
	{
		nNumVtx = pWorldModel[nCnt].Xfile_Mesh->GetNumVertices();//���_�������
		sizeFvF = D3DXGetFVFVertexSize(pWorldModel[nCnt].Xfile_Mesh->GetFVF());//format�̑傫��
		pWorldModel[nCnt].Xfile_Mesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);//���_buff��lock
		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;//���_�������
			
			//�����蔻��pbox�̒��_��T��
			if (nCntVtx == 0)//���߂̒��_
			{
				pWorldModel[nCnt].MaxColBox = vtx;
				pWorldModel[nCnt].MinColBox = vtx;
			}
			else
			{
				if (vtx.x > pWorldModel[nCnt].MaxColBox.x) pWorldModel[nCnt].MaxColBox.x = vtx.x;
				else if (vtx.x < pWorldModel[nCnt].MinColBox.x) pWorldModel[nCnt].MinColBox.x = vtx.x;
				if (vtx.y > pWorldModel[nCnt].MaxColBox.y) pWorldModel[nCnt].MaxColBox.y = vtx.y;
				else if (vtx.y < pWorldModel[nCnt].MinColBox.y) pWorldModel[nCnt].MinColBox.y = vtx.y;
				if (vtx.z > pWorldModel[nCnt].MaxColBox.z) pWorldModel[nCnt].MaxColBox.z = vtx.z;
				else if (vtx.z < pWorldModel[nCnt].MinColBox.z) pWorldModel[nCnt].MinColBox.z = vtx.z;
			}

			pVtxBuff += sizeFvF;//���ɍs��
		}
		pWorldModel[nCnt].MaxColBox = pWorldModel[nCnt].pos + pWorldModel[nCnt].MaxColBox;
		pWorldModel[nCnt].MinColBox = pWorldModel[nCnt].pos + pWorldModel[nCnt].MinColBox;//minbox�̒l�͕���
		pWorldModel[nCnt].Xfile_Mesh->UnlockVertexBuffer();//unlock
	}
}

void SetWorldModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int nCnt = 0; nCnt < WORLDMODEL_NUM; nCnt++)
	{
		if (nCnt % 2 == 0)
		{
			pWorldModel[nCnt].rot = D3DXVECTOR3(0.f, 0.f, 0.f);
			pWorldModel[nCnt].pos.x = (float)(rand() % WORLDMODEL_POS_RANGE_X + WORLDMODEL_POS_RANGE_X);
		}
		else
		{
			pWorldModel[nCnt].rot = D3DXVECTOR3(0.f, D3DX_PI, 0.f);
			pWorldModel[nCnt].pos.x = (float)(rand() % WORLDMODEL_POS_RANGE_X - 2 * WORLDMODEL_POS_RANGE_X);
		}
	
		pWorldModel[nCnt].pos.z = (float)(rand() % WORLDMODEL_POS_RANGE_Z - WORLDMODEL_POS_RANGE_Z / 2);
		pWorldModel[nCnt].pos.y = 0;
		pWorldModel[nCnt].move = D3DXVECTOR3(0.f, 0.f, 0.f);
		pWorldModel[nCnt].nID = rand () % 4;
		switch (pWorldModel[nCnt].nID)
		{
		case 0:
			D3DXLoadMeshFromX("data/MODEL/Car/Car0.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &pWorldModel[nCnt].Xfile_Materials, NULL, &pWorldModel[nCnt].Xfile_MaterialNum, &pWorldModel[nCnt].Xfile_Mesh);
			break;
		case 1:
			D3DXLoadMeshFromX("data/MODEL/Car/Car1.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &pWorldModel[nCnt].Xfile_Materials, NULL, &pWorldModel[nCnt].Xfile_MaterialNum, &pWorldModel[nCnt].Xfile_Mesh);
			break;
		case 2:
			D3DXLoadMeshFromX("data/MODEL/Car/Car2.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &pWorldModel[nCnt].Xfile_Materials, NULL, &pWorldModel[nCnt].Xfile_MaterialNum, &pWorldModel[nCnt].Xfile_Mesh);
			break;
		case 3:
			D3DXLoadMeshFromX("data/MODEL/Car/Car3.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &pWorldModel[nCnt].Xfile_Materials, NULL, &pWorldModel[nCnt].Xfile_MaterialNum, &pWorldModel[nCnt].Xfile_Mesh);
			break;
		default:
			break;
		}
		pWorldModel[nCnt].bMove = true;
		pWorldModel[nCnt].bUse = true;
		pWorldModel[nCnt].fMoveSpeed = 0.f;
	}
}

void UninitWorldModel(void)
{
	free(pWorldModel);
}

void UpdateWorldModel(void)
{
	for (int nCnt = 0; nCnt < WORLDMODEL_NUM; nCnt++)
	{
		if (pWorldModel[nCnt].bMove == true)
		{
			if (nCnt % 2 == 0)
			{
				if (pWorldModel[nCnt].pos.x <= -WORLDMODEL_POS_RANGE_X)
				{
					pWorldModel[nCnt].pos.x = WORLDMODEL_POS_RANGE_X;
					pWorldModel[nCnt].pos.z = (float)(rand() % WORLDMODEL_POS_RANGE_Z - WORLDMODEL_POS_RANGE_Z / 2);

					//�����蔻��pbox�̐ݒ�
					int nNumVtx;//���_��
					DWORD sizeFvF;//����_format��size
					BYTE *pVtxBuff;//���_buffer�ւ�pointer
					nNumVtx = pWorldModel[nCnt].Xfile_Mesh->GetNumVertices();//���_�������
					sizeFvF = D3DXGetFVFVertexSize(pWorldModel[nCnt].Xfile_Mesh->GetFVF());//format�̑傫��
					pWorldModel[nCnt].Xfile_Mesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);//���_buff��lock
					for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
					{
						D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;//���_�������
						pVtxBuff += sizeFvF;//���ɍs��

						//�����蔻��pbox�̒��_��T��
						if (nCntVtx == 0)//���߂̒��_
						{
							pWorldModel[nCnt].MaxColBox = vtx;
							pWorldModel[nCnt].MinColBox = vtx;
						}
						else
						{
							if (vtx.x > pWorldModel[nCnt].MaxColBox.x) pWorldModel[nCnt].MaxColBox.x = vtx.x;
							else if (vtx.x < pWorldModel[nCnt].MinColBox.x) pWorldModel[nCnt].MinColBox.x = vtx.x;
							if (vtx.y > pWorldModel[nCnt].MaxColBox.y) pWorldModel[nCnt].MaxColBox.y = vtx.y;
							else if (vtx.x < pWorldModel[nCnt].MinColBox.x) pWorldModel[nCnt].MinColBox.y = vtx.y;
							if (vtx.z > pWorldModel[nCnt].MaxColBox.z) pWorldModel[nCnt].MaxColBox.z = vtx.z;
							else if (vtx.x < pWorldModel[nCnt].MinColBox.x) pWorldModel[nCnt].MinColBox.z = vtx.z;
						}
					}
					pWorldModel[nCnt].MaxColBox = pWorldModel[nCnt].pos + pWorldModel[nCnt].MaxColBox;
					pWorldModel[nCnt].MinColBox = pWorldModel[nCnt].pos + pWorldModel[nCnt].MinColBox;//minbox�̒l�͕���
					pWorldModel[nCnt].Xfile_Mesh->UnlockVertexBuffer();//unlock
				}
				switch (pWorldModel[nCnt].nID)
				{
				case 0:
					pWorldModel[nCnt].move.x = 5.f;
					break;
				case 1:
					pWorldModel[nCnt].move.x = 10.f;
					break;
				case 2:
					pWorldModel[nCnt].move.x = 15.f;
					break;
				case 3:
					pWorldModel[nCnt].move.x = 20.f;
					break;
				}
			}
			else
			{
				if (pWorldModel[nCnt].pos.x >= WORLDMODEL_POS_RANGE_X)
				{
					pWorldModel[nCnt].pos.x = -WORLDMODEL_POS_RANGE_X;
					pWorldModel[nCnt].pos.z = (float)(rand() % WORLDMODEL_POS_RANGE_Z - WORLDMODEL_POS_RANGE_Z / 2);

					//�����蔻��pbox�̐ݒ�
					int nNumVtx;//���_��
					DWORD sizeFvF;//����_format��size
					BYTE *pVtxBuff;//���_buffer�ւ�pointer
	
					nNumVtx = pWorldModel[nCnt].Xfile_Mesh->GetNumVertices();//���_�������
					sizeFvF = D3DXGetFVFVertexSize(pWorldModel[nCnt].Xfile_Mesh->GetFVF());//format�̑傫��
					pWorldModel[nCnt].Xfile_Mesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);//���_buff��lock
					for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
					{
						D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;//���_�������
						pVtxBuff += sizeFvF;//���ɍs��

											//�����蔻��pbox�̒��_��T��
						if (nCntVtx == 0)//���߂̒��_
						{
							pWorldModel[nCnt].MaxColBox = vtx;
							pWorldModel[nCnt].MinColBox = vtx;
						}
						else
						{
							if (vtx.x > pWorldModel[nCnt].MaxColBox.x) pWorldModel[nCnt].MaxColBox.x = vtx.x;
							else if (vtx.x < pWorldModel[nCnt].MinColBox.x) pWorldModel[nCnt].MinColBox.x = vtx.x;
							if (vtx.y > pWorldModel[nCnt].MaxColBox.y) pWorldModel[nCnt].MaxColBox.y = vtx.y;
							else if (vtx.x < pWorldModel[nCnt].MinColBox.x) pWorldModel[nCnt].MinColBox.y = vtx.y;
							if (vtx.z > pWorldModel[nCnt].MaxColBox.z) pWorldModel[nCnt].MaxColBox.z = vtx.z;
							else if (vtx.x < pWorldModel[nCnt].MinColBox.x) pWorldModel[nCnt].MinColBox.z = vtx.z;
						}
					}
					pWorldModel[nCnt].MaxColBox = pWorldModel[nCnt].pos + pWorldModel[nCnt].MaxColBox;
					pWorldModel[nCnt].MinColBox = pWorldModel[nCnt].pos + pWorldModel[nCnt].MinColBox;//minbox�̒l�͕���
					pWorldModel[nCnt].Xfile_Mesh->UnlockVertexBuffer();//unlock
				}
				switch (pWorldModel[nCnt].nID)
				{
				case 0:
					pWorldModel[nCnt].move.x = 5.f;
					break;
				case 1:
					pWorldModel[nCnt].move.x = 10.f;
					break;
				case 2:
					pWorldModel[nCnt].move.x = 15.f;
					break;
				case 3:
					pWorldModel[nCnt].move.x = 20.f;
					break;
				}
			}
			pWorldModel[nCnt].pos += pWorldModel[nCnt].move;
			pWorldModel[nCnt].MaxColBox += pWorldModel[nCnt].move;
			pWorldModel[nCnt].MinColBox += pWorldModel[nCnt].move;
		}
		else
		{

		}
	}
}

void DrawWorldModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans, mtxworld;
	D3DMATERIAL9 matDef;

	for (int nCnt = 0; nCnt < WORLDMODEL_NUM; nCnt++)
	{
		D3DXMatrixIdentity(&mtxworld);//�P��matrix
		D3DXMatrixRotationYawPitchRoll(&mtxRot, pWorldModel[nCnt].rot.y, pWorldModel[nCnt].rot.x, pWorldModel[nCnt].rot.z);//��]�p�x
		D3DXMatrixMultiply(&mtxworld, &mtxworld, &mtxRot);//���Z
		D3DXMatrixTranslation(&mtxTrans, pWorldModel[nCnt].pos.x, pWorldModel[nCnt].pos.y, pWorldModel[nCnt].pos.z); //���Ematrix�S�́@�ړ������������Ƃ���matrix�̍��Z
		D3DXMatrixMultiply(&mtxworld, &mtxworld, &mtxTrans); //���Z�@���Ematrix�̈ړ�
		pDevice->SetTransform(D3DTS_WORLD, &mtxworld); //set the world into Map
		pDevice->GetMaterial(&matDef);//�ގ������
		for (DWORD nCntMat = 0; nCntMat < (int)pWorldModel[nCnt].Xfile_MaterialNum; nCntMat++)
		{
			pDevice->SetMaterial(&pMaterials[nCntMat].MatD3D);
			pDevice->SetTexture(0, pWorldModel[nCnt].g_Textures[nCntMat]);
			pWorldModel[nCnt].Xfile_Mesh->DrawSubset(nCntMat);
		}
		pDevice->SetMaterial(&matDef);
	}
}

MODEL *GetWorldModel(void)
{
	return pWorldModel;
}