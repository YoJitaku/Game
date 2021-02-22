//=============================================================================
//
// [WorldModel.cpp]
// Author : JITAKU YO
//
//=============================================================================
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
	D3DXLoadMeshFromX("data/MODEL/Car/Car0.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &pWorldModel[0].Xfile_Materials, NULL, &pWorldModel[0].Xfile_MaterialNum, &pWorldModel[0].Xfile_Mesh);
	//D3DXLoadMeshFromX("data/MODEL/Car/Car1.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &pWorldModel[1].Xfile_Materials, NULL, &pWorldModel[1].Xfile_MaterialNum, &pWorldModel[1].Xfile_Mesh);
	//D3DXLoadMeshFromX("data/MODEL/Car/Car2.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &pWorldModel[2].Xfile_Materials, NULL, &pWorldModel[2].Xfile_MaterialNum, &pWorldModel[2].Xfile_Mesh);
	//D3DXLoadMeshFromX("data/MODEL/Car/Car3.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &pWorldModel[3].Xfile_Materials, NULL, &pWorldModel[3].Xfile_MaterialNum, &pWorldModel[3].Xfile_Mesh);
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
}

void SetWorldModel(void)
{
	pWorldModel[0].pos = D3DXVECTOR3(20.f, 0.f, 20.f);
	pWorldModel[0].rot = D3DXVECTOR3(0.f, 0.f, 0.f);
	pWorldModel[0].ID = 0;
	pWorldModel[0].fMoveSpeed = 0.f;
	//pWorldModel[1].pos = D3DXVECTOR3(25.f, 0.f, 200.f);
	//pWorldModel[1].rot = D3DXVECTOR3(0.f, D3DX_PI / 2, 0.f);
	//pWorldModel[1].ID = 1;
	//pWorldModel[1].fMoveSpeed = 0.f;
	//pWorldModel[2].pos = D3DXVECTOR3(-25.f, 0.f, 100.f);
	//pWorldModel[2].rot = D3DXVECTOR3(0.f, -D3DX_PI / 2, 0.f);
	//pWorldModel[2].ID = 2;
	//pWorldModel[2].fMoveSpeed = 0.f;
	//pWorldModel[3].pos = D3DXVECTOR3(-25.f, 0.f, 300.f);
	//pWorldModel[3].rot = D3DXVECTOR3(0.f, D3DX_PI / 2, 0.f);
	//pWorldModel[3].ID = 3;
	//pWorldModel[3].fMoveSpeed = 0.f;
}

void UninitWorldModel(void)
{
	free(pWorldModel);
}

void UpdateWorldModel(void)
{


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