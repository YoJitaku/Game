#include "SnowBall.h"
#include "Dinput8.h"
#include "Camera.h"
#include "WorldModel.h"
#include "Collision.h"

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

	//BYTE *pVtxBuff;//í∏ì_bufferÇ÷ÇÃpointer
	//D3DXVECTOR3 Sphere_Radius;
	//pSnowBall[0].Xfile_Mesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);//í∏ì_buffÇlock
	//D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;//í∏ì_èÓïÒÇéÊÇÈ
	//Sphere_Radius = vtx - pSnowBall[0].pos;//ãÖîºåaÇÃvector
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
	CAMERA *pCamera = GetCamera();

	if (GetkeyboardRelease(DIK_SPACE) == true)
	{
		for (int nCnt = 0; nCnt < SNOWBALL_MAX_NUM; nCnt++)
		{
			if (pSnowBall[nCnt].bUse == false)
			{
				//ï`âÊóLå¯Ç…
				pSnowBall[nCnt].bUse = true;
				//ç¿ïWèâä˙âª
				pSnowBall[nCnt].pos.x = pCamera->posR.x + 20.f;
				pSnowBall[nCnt].pos.y = pCamera->posR.y + 20.f;
				pSnowBall[nCnt].pos.z = pCamera->posR.z;
				//à⁄ìÆë¨ìx
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
		////íeÇ∆ÉJÉÅÉâÇÃä‘ãóó£MAX_DISTANCEÇÊÇËâìÇ¢èÍçáÇÕíeÇè¡Ç∑
		//D3DXVECTOR3 Distance = pSnowBall[nCnt].pos - pCamera->posV;
		//float fDistance = sqrtf(Distance.x * Distance.x + Distance.y * Distance.y + Distance.z * Distance.z);
		//if (fDistance > MAX_DISTANCE) pSnowBall[nCnt].bUse = false;
	}

	//ìñÇΩÇËîªíË snowballÇ∆modelÇìñÇΩéûè¡Ç∑
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
			D3DXMatrixIdentity(&mtxworld);//íPà matrix
			D3DXMatrixTranslation(&mtxTrans, pSnowBall[nCnt].pos.x, pSnowBall[nCnt].pos.y, pSnowBall[nCnt].pos.z); //ê¢äEmatrixëSëÃÅ@à⁄ìÆÇµÇΩÇ¢ãóó£Ç∆Ç¢Ç§matrixÇÃçáéZ
			D3DXMatrixMultiply(&mtxworld, &mtxworld, &mtxTrans); //çáéZÅ@ê¢äEmatrixÇÃà⁄ìÆ
			pDevice->SetTransform(D3DTS_WORLD, &mtxworld); //set the world into Map
			pDevice->GetMaterial(&matDef);//çﬁéøÇéÊÇÈ
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
			//ï`âÊóLå¯Ç…
			pSnowBall[nCnt].bUse = true;
			//ç¿ïWèâä˙âª
			pSnowBall[nCnt].pos = pos;
			//à⁄ìÆë¨ìx
			pSnowBall[nCnt].move = move;
			
			break;
		}
	}
}