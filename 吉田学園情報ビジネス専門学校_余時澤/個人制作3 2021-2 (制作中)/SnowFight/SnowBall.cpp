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
				//描画有効に
				pSnowBall[nCnt].bUse = true;
				//座標初期化
				pSnowBall[nCnt].pos.x = pCamera->posR.x + 20.f;
				pSnowBall[nCnt].pos.y = pCamera->posR.y + 20.f;
				pSnowBall[nCnt].pos.z = pCamera->posR.z;
				//移動速度
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
		////弾とカメラの間距離MAX_DISTANCEより遠い場合は弾を消す
		//D3DXVECTOR3 Distance = pSnowBall[nCnt].pos - pCamera->posV;
		//float fDistance = sqrtf(Distance.x * Distance.x + Distance.y * Distance.y + Distance.z * Distance.z);
		//if (fDistance > MAX_DISTANCE) pSnowBall[nCnt].bUse = false;
	}

	//当たり判定 snowballとmodelを当た時消す
	//BYTE *pVtxBuff;//頂点bufferへのpointer
	//D3DXVECTOR3 Sphere_Radius;
	//for (int nCnt = 0; nCnt < SNOWBALL_MAX_NUM; nCnt++)
	//{
	//	if (pSnowBall[nCnt].bUse == true)
	//	{
	//		pSnowBall[nCnt].Xfile_Mesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);//頂点buffをlock
	//		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;//頂点情報を取る
	//		Sphere_Radius = vtx - pSnowBall[nCnt].pos;//球半径のvector
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
			D3DXMatrixIdentity(&mtxworld);//単位matrix
			D3DXMatrixTranslation(&mtxTrans, pSnowBall[nCnt].pos.x, pSnowBall[nCnt].pos.y, pSnowBall[nCnt].pos.z); //世界matrix全体　移動したい距離というmatrixの合算
			D3DXMatrixMultiply(&mtxworld, &mtxworld, &mtxTrans); //合算　世界matrixの移動
			pDevice->SetTransform(D3DTS_WORLD, &mtxworld); //set the world into Map
			pDevice->GetMaterial(&matDef);//材質を取る
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
			//描画有効に
			pSnowBall[nCnt].bUse = true;
			//座標初期化
			pSnowBall[nCnt].pos = pos;
			//移動速度
			pSnowBall[nCnt].move = move;
			
			break;
		}
	}
}