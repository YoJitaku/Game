#define _CRT_SECURE_NO_WARNINGS
#include "Player.h"
#include "Dinput8.h"
KEY aKeyDiff[10];//10パーツ
LPD3DXMESH g_pMeshPlayer = NULL;
LPD3DXBUFFER g_pBuffMatPlayer = NULL;
DWORD g_nNumMatPlayer = 0;
PLAYER *pPlayer;

KEY KeyPosRot(float posX, float posY, float posZ, float rotX, float rotY, float rotZ)
{
	KEY key;

	key.fPosX = posX;
	key.fPosY = posY;
	key.fPosZ = posZ;

	key.fRotX = rotX;
	key.fRotY = rotY;
	key.fRotZ = rotZ;

	return key;
}
HRESULT InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pPlayer = (PLAYER*)malloc(1 * sizeof(PLAYER));
	pPlayer[0].nNumModel = 10;//パーツ数=10
	if (FAILED(D3DXLoadMeshFromX("data/MODEL/3Dgame_body.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &pPlayer[0].aModel[0].Xfile_Materials, NULL, &pPlayer[0].aModel[0].Xfile_MaterialNum, &pPlayer[0].aModel[0].Xfile_Mesh))) return E_FAIL;
	if (FAILED(D3DXLoadMeshFromX("data/MODEL/3Dgame_head.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &pPlayer[0].aModel[1].Xfile_Materials, NULL, &pPlayer[0].aModel[1].Xfile_MaterialNum, &pPlayer[0].aModel[1].Xfile_Mesh))) return E_FAIL;
	if (FAILED(D3DXLoadMeshFromX("data/MODEL/3Dgame_armR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &pPlayer[0].aModel[2].Xfile_Materials, NULL, &pPlayer[0].aModel[2].Xfile_MaterialNum, &pPlayer[0].aModel[2].Xfile_Mesh))) return E_FAIL;
	if (FAILED(D3DXLoadMeshFromX("data/MODEL/3Dgame_handR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &pPlayer[0].aModel[3].Xfile_Materials, NULL, &pPlayer[0].aModel[3].Xfile_MaterialNum, &pPlayer[0].aModel[3].Xfile_Mesh))) return E_FAIL;
	if (FAILED(D3DXLoadMeshFromX("data/MODEL/3Dgame_armL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &pPlayer[0].aModel[4].Xfile_Materials, NULL, &pPlayer[0].aModel[4].Xfile_MaterialNum, &pPlayer[0].aModel[4].Xfile_Mesh))) return E_FAIL;
	if (FAILED(D3DXLoadMeshFromX("data/MODEL/3Dgame_handL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &pPlayer[0].aModel[5].Xfile_Materials, NULL, &pPlayer[0].aModel[5].Xfile_MaterialNum, &pPlayer[0].aModel[5].Xfile_Mesh))) return E_FAIL;
	if (FAILED(D3DXLoadMeshFromX("data/MODEL/3Dgame_legR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &pPlayer[0].aModel[6].Xfile_Materials, NULL, &pPlayer[0].aModel[6].Xfile_MaterialNum, &pPlayer[0].aModel[6].Xfile_Mesh))) return E_FAIL;
	if (FAILED(D3DXLoadMeshFromX("data/MODEL/3Dgame_footR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &pPlayer[0].aModel[7].Xfile_Materials, NULL, &pPlayer[0].aModel[7].Xfile_MaterialNum, &pPlayer[0].aModel[7].Xfile_Mesh))) return E_FAIL;
	if (FAILED(D3DXLoadMeshFromX("data/MODEL/3Dgame_legL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &pPlayer[0].aModel[8].Xfile_Materials, NULL, &pPlayer[0].aModel[8].Xfile_MaterialNum, &pPlayer[0].aModel[8].Xfile_Mesh))) return E_FAIL;
	if (FAILED(D3DXLoadMeshFromX("data/MODEL/3Dgame_footL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &pPlayer[0].aModel[9].Xfile_Materials, NULL, &pPlayer[0].aModel[9].Xfile_MaterialNum, &pPlayer[0].aModel[9].Xfile_Mesh))) return E_FAIL;
	//親子関係の設定
	//pPlayer[0].aModel[0].nIdxModelParent = -1;
	//pPlayer[0].aModel[1].nIdxModelParent = 0;
	//pPlayer[0].aModel[2].nIdxModelParent = 0;
	//pPlayer[0].aModel[3].nIdxModelParent = 2;
	//pPlayer[0].aModel[4].nIdxModelParent = 0;
	//pPlayer[0].aModel[5].nIdxModelParent = 4;
	//pPlayer[0].aModel[6].nIdxModelParent = 0;
	//pPlayer[0].aModel[7].nIdxModelParent = 6;
	//pPlayer[0].aModel[8].nIdxModelParent = 0;
	//pPlayer[0].aModel[9].nIdxModelParent = 8;

	//pPlayer[0].aModel[0].pos = D3DXVECTOR3(0.0f, 45.f, 0.0f);
	//pPlayer[0].aModel[1].pos = D3DXVECTOR3(0.0f, 15.f, 0.0f);
	//pPlayer[0].aModel[2].pos = D3DXVECTOR3(-7.5f, 12.0f, 0.0f);
	//pPlayer[0].aModel[3].pos = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);
	//pPlayer[0].aModel[4].pos = D3DXVECTOR3(7.5f, 12.0f, 0.0f);
	//pPlayer[0].aModel[5].pos = D3DXVECTOR3(10.0f, 0.0f, 0.0f);
	//pPlayer[0].aModel[6].pos = D3DXVECTOR3(-4.0f, 0.0f, 0.0f);
	//pPlayer[0].aModel[7].pos = D3DXVECTOR3(0.0f, -10.0f, 0.0f);
	//pPlayer[0].aModel[8].pos = D3DXVECTOR3(4.0f, 0.0f, 0.0f);
	//pPlayer[0].aModel[9].pos = D3DXVECTOR3(0.0f, -10.0f, 0.0f);

	//pPlayer[0].aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//pPlayer[0].aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//pPlayer[0].aModel[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//pPlayer[0].aModel[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//pPlayer[0].aModel[4].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//pPlayer[0].aModel[5].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//pPlayer[0].aModel[6].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//pPlayer[0].aModel[7].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//pPlayer[0].aModel[8].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//pPlayer[0].aModel[9].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	for (int nCnt = 0; nCnt < 10; nCnt++) pPlayer[0].aModel[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pPlayer[0].pos = D3DXVECTOR3(0.f, 0.f, 0.f);
	pPlayer[0].rot = D3DXVECTOR3(0.f, 0.f, 0.f);
	//pPlayer[0].ID = 0;
	pPlayer[0].fMoveSpeed = 0.f;
	pPlayer[0].nCntMotion = 0;
	pPlayer[0].motionType = MOTIONTYPE_NEUTRAL;
	pPlayer[0].aMotionInfo[MOTIONTYPE_NEUTRAL].bLoop = true;
	pPlayer[0].aMotionInfo[MOTIONTYPE_WALK].bLoop = true;
	ReadMotion();

	for (int nCnt = 0; nCnt < 8; nCnt++) pPlayer[0].aMotionInfo[nCnt].nNumkey = 0;
	
	return S_OK;
}
void UninitPlayer(void)
{

}
void UpdatePlayer(void)
{

#if 0
	switch (pPlayer[0].motionType)
	{
	case 0:
		//if move ->
		//pPlayer[0].motionType = MOTIONTYPE_WALK
		//if shift move ->
		//pPlayer[0].motionType = MOTIONTYPE_RUN
		//if JUMP(space) ->
		//pPlayer[0].motionType = MOTIONTYPE_JUMP
		//if squat(ctrl) ->
		//pPlayer[0].motionType = MOTIONTYPE_SQUAT
		//if Shooting(Mouse left click && hold = 1) ->
		//pPlayer[0].motionType = MOTIONTYPE_SHOOT1
		//if Shooting(Mouse left click && hold = 2) ->
		//pPlayer[0].motionType = MOTIONTYPE_SHOOT2
		//if Reloading(R) ->
		//pPlayer[0].motionType = MOTIONTYPE_RELOAD
		//if Throw((Mouse left click && hold = 2)) ->
		//pPlayer[0].motionType = MOTIONTYPE_THROW
		break;
	case 1:
		//pPlayer[0].motionType = MOTIONTYPE_RUN
		//if JUMP(space) ->
		//pPlayer[0].motionType = MOTIONTYPE_JUMP
		//if squat(ctrl) ->
		//pPlayer[0].motionType = MOTIONTYPE_SQUAT
		//if Shooting(Mouse left click && hold = 1) ->
		//pPlayer[0].motionType = MOTIONTYPE_SHOOT1
		//if Shooting(Mouse left click && hold = 2) ->
		//pPlayer[0].motionType = MOTIONTYPE_SHOOT2
		//if Reloading(R) ->
		//pPlayer[0].motionType = MOTIONTYPE_RELOAD
		//if Throw((Mouse left click && hold = 2)) ->
		//pPlayer[0].motionType = MOTIONTYPE_THROW
		break;
	case 2:

		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	case 8:
		break;
	default:
		break;
	}
#endif // 1

	PlayMotion(pPlayer[0].motionType);

	//pPlayer[0].motionType = PlayMotion(pPlayer[0].motionType);
}
void DrawPlayer(void)
{
	//LPDIRECT3DDEVICE9 pDevice = GetDevice();
	////Player bodyの座標と向きの基準計算
	//D3DXMATRIX mtxRot, mtxTrans;
	//D3DMATERIAL9 matDef;
	//D3DXMATERIAL *pMat;
	//D3DXMatrixIdentity(&pPlayer[0].mtxworld);
	//D3DXMatrixRotationYawPitchRoll(&mtxRot, pPlayer[0].rot.y, pPlayer[0].rot.x, pPlayer[0].rot.z);
	//D3DXMatrixMultiply(&pPlayer[0].mtxworld, &pPlayer[0].mtxworld, &mtxRot);
	//D3DXMatrixTranslation(&mtxTrans, pPlayer[0].pos.x, pPlayer[0].pos.y, pPlayer[0].pos.z); //世界matrix全体　移動したい距離というmatrixの合算
	//D3DXMatrixMultiply(&pPlayer[0].mtxworld, &pPlayer[0].mtxworld, &mtxTrans); //世界matrixの移動
	//pDevice->SetTransform(D3DTS_WORLD, &pPlayer[0].mtxworld);
	//pDevice->GetMaterial(&matDef);

	////Playe各部パーツの座標と向き計算
	//for (int nCntModel = 0; nCntModel < pPlayer[0].nNumModel; nCntModel++)
	//{
	//	D3DXMATRIX mtxRotModel, mtxTransModel;
	//	D3DXMATRIX mtxParent;
	//	D3DXMatrixIdentity(&pPlayer[0].aModel[nCntModel].mtxworld);
	//	D3DXMatrixRotationYawPitchRoll(&mtxRotModel, pPlayer[0].aModel[nCntModel].rot.y, pPlayer[0].aModel[nCntModel].rot.x, pPlayer[0].aModel[nCntModel].rot.z);
	//	D3DXMatrixMultiply(&pPlayer[0].aModel[nCntModel].mtxworld, &pPlayer[0].aModel[nCntModel].mtxworld, &mtxRotModel);
	//	D3DXMatrixTranslation(&mtxTransModel, pPlayer[0].aModel[nCntModel].pos.x, pPlayer[0].aModel[nCntModel].pos.y, pPlayer[0].aModel[nCntModel].pos.z); //世界matrix全体　移動したい距離というmatrixの合算
	//	D3DXMatrixMultiply(&pPlayer[0].aModel[nCntModel].mtxworld, &pPlayer[0].aModel[nCntModel].mtxworld, &mtxTransModel); //世界matrixの移動
	//																														//親からの座標matrixの設定
	//	if (pPlayer[0].aModel[nCntModel].nIdxModelParent != -1)
	//		mtxParent = pPlayer[0].aModel[pPlayer[0].aModel[nCntModel].nIdxModelParent].mtxworld;//
	//	else mtxParent = pPlayer[0].mtxworld;
	//	//合算
	//	D3DXMatrixMultiply(&pPlayer[0].aModel[nCntModel].mtxworld, &pPlayer[0].aModel[nCntModel].mtxworld, &mtxParent);
	//	//描画
	//	pDevice->SetTransform(D3DTS_WORLD, &pPlayer[0].aModel[nCntModel].mtxworld); //set the world into Map

	//	pMat = (D3DXMATERIAL*)pPlayer[0].aModel[nCntModel].Xfile_Materials->GetBufferPointer();
	//	for (int nCntMat = 0; nCntMat < (int)pPlayer[0].aModel[nCntModel].Xfile_MaterialNum; nCntMat++)
	//	{
	//		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
	//		pDevice->SetTexture(0, NULL);
	//		pPlayer[0].aModel[nCntModel].Xfile_Mesh->DrawSubset(nCntMat);
	//	}
	//}
	//pDevice->SetMaterial(&matDef);
}

PLAYER *GetPlayer(void)
{
	return pPlayer;
}

void ReadMotion(void)
{
	FILE *pFile;
	pFile = fopen("Motion.txt", "r");
	pPlayer[0].nNumMotion = 2;//motionの数
	pPlayer[0].nNumModel = 11;//parts数
	
	for (int nCnt0 = 0; nCnt0 < pPlayer[0].nNumModel; nCnt0++)
	{
		fscanf(pFile, "%d", &pPlayer[0].aModel[nCnt0].nIdxModelParent);
		fscanf(pFile, "%f %f %f",
			&pPlayer[0].aModel[nCnt0].pos.x,
			&pPlayer[0].aModel[nCnt0].pos.y,
			&pPlayer[0].aModel[nCnt0].pos.z);
		fscanf(pFile, "%f %f %f",
			&pPlayer[0].aModel[nCnt0].rot.x,
			&pPlayer[0].aModel[nCnt0].rot.y,
			&pPlayer[0].aModel[nCnt0].rot.z);
	}
	for (int nCnt1 = 0; nCnt1 < pPlayer[0].nNumMotion; nCnt1++)
	{
		fscanf(pFile, "%d", &pPlayer[0].aMotionInfo[nCnt1].nMAXkey);//motionのkeyframeの数を読み込む
		for (int nCnt2 = 0; nCnt2 < pPlayer[0].aMotionInfo[nCnt1].nMAXkey; nCnt2++)
		{
			fscanf(pFile, "%d", &pPlayer[0].aMotionInfo[nCnt1].akeyInfo[nCnt2].nFrame);//motionのkeyframeの再生speedを読み込む
			for (int nCnt3 = 0; nCnt3 < 10; nCnt3++)
			{
				fscanf(pFile,
					"%f %f %f",
					&pPlayer[0].aMotionInfo[nCnt1].akeyInfo[nCnt2].akey[nCnt3].fPosX,
					&pPlayer[0].aMotionInfo[nCnt1].akeyInfo[nCnt2].akey[nCnt3].fPosY,
					&pPlayer[0].aMotionInfo[nCnt1].akeyInfo[nCnt2].akey[nCnt3].fPosZ);
				fscanf(pFile,
					"%f %f %f",
					&pPlayer[0].aMotionInfo[nCnt1].akeyInfo[nCnt2].akey[nCnt3].fRotX,
					&pPlayer[0].aMotionInfo[nCnt1].akeyInfo[nCnt2].akey[nCnt3].fRotY,
					&pPlayer[0].aMotionInfo[nCnt1].akeyInfo[nCnt2].akey[nCnt3].fRotZ);
			}
		}
	}
	fclose(pFile);
}

MOTIONTYPE PlayMotion(int PlayerMotion)
{
	pPlayer[0].nCntMotion++;

	if (pPlayer[0].aMotionInfo[PlayerMotion].nNumkey == 1 && pPlayer[0].nCntMotion == 1)
	//if (pPlayer[0].aMotionInfo[PlayerMotion].nNumkey == (pPlayer[0].aMotionInfo[PlayerMotion].nMAXkey - 1)
	//	&& pPlayer[0].nCntMotion == 1)//最後のkeyframeに行った時
	{
 		if (pPlayer[0].aMotionInfo[PlayerMotion].bLoop == true)
		{
			for (int nCnt = 0; nCnt < 10; nCnt++)//10パーツを別々計算 
			{
				//差分=次のkeyframe - 今のkeyframe
				aKeyDiff[nCnt].fPosX = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[0].akey[nCnt].fPosX - pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nMAXkey - 1].akey[nCnt].fPosX;
				aKeyDiff[nCnt].fPosY = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[0].akey[nCnt].fPosY - pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nMAXkey - 1].akey[nCnt].fPosY;
				aKeyDiff[nCnt].fPosZ = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[0].akey[nCnt].fPosZ - pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nMAXkey - 1].akey[nCnt].fPosZ;
				aKeyDiff[nCnt].fRotX = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[0].akey[nCnt].fRotX - pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nMAXkey - 1].akey[nCnt].fRotX;
				aKeyDiff[nCnt].fRotY = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[0].akey[nCnt].fRotY - pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nMAXkey - 1].akey[nCnt].fRotY;
				aKeyDiff[nCnt].fRotZ = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[0].akey[nCnt].fRotZ - pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nMAXkey - 1].akey[nCnt].fRotZ;
			}
		}

		pPlayer[0].aMotionInfo[PlayerMotion].nNumkey = 0;
	}
	//else if (pPlayer[0].aMotionInfo[PlayerMotion].nNumkey != (pPlayer[0].aMotionInfo[PlayerMotion].nMAXkey - 1)
	//	&& pPlayer[0].nCntMotion == 1)
	else if (pPlayer[0].nCntMotion == 1)
	{
		for (int nCnt = 0; nCnt < 10; nCnt++)//10パーツを別々計算 
		{
			//差分=次のkeyframe - 今のkeyframe
			aKeyDiff[nCnt].fPosX = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey + 1].akey[nCnt].fPosX - pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].akey[nCnt].fPosX;
			aKeyDiff[nCnt].fPosY = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey + 1].akey[nCnt].fPosY - pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].akey[nCnt].fPosY;
			aKeyDiff[nCnt].fPosZ = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey + 1].akey[nCnt].fPosZ - pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].akey[nCnt].fPosZ;
			aKeyDiff[nCnt].fRotX = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey + 1].akey[nCnt].fRotX - pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].akey[nCnt].fRotX;
			aKeyDiff[nCnt].fRotY = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey + 1].akey[nCnt].fRotY - pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].akey[nCnt].fRotY;
			aKeyDiff[nCnt].fRotZ = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey + 1].akey[nCnt].fRotZ - pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].akey[nCnt].fRotZ;
		}
		pPlayer[0].aMotionInfo[PlayerMotion].nNumkey++;
	}
	//update
	if (pPlayer[0].nCntMotion == pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].nFrame)//今のkeyframeを再生の最後frameの時
	{
		pPlayer[0].nCntMotion = 0;

		for (int nCnt = 0; nCnt < 10; nCnt++)
		{
			float fMotionSpeed = (float)pPlayer[0].nCntMotion / (float)pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].nFrame;//再生speed
			//今のrotは前keyframeに基づいて差分を加える
			//前keyframeのrot
			pPlayer[0].aModel[nCnt].rot.x = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].akey[nCnt].fRotX;
			pPlayer[0].aModel[nCnt].rot.y = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].akey[nCnt].fRotY;
			pPlayer[0].aModel[nCnt].rot.z = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].akey[nCnt].fRotZ;
			//差分を加える
			pPlayer[0].aModel[nCnt].pos.x += aKeyDiff[nCnt].fPosX * fMotionSpeed;
			//pPlayer[0].aModel[nCnt].pos.y += aKeyDiff[nCnt].fPosY * fMotionSpeed;
			pPlayer[0].aModel[nCnt].pos.z += aKeyDiff[nCnt].fPosZ * fMotionSpeed;
			pPlayer[0].aModel[nCnt].rot.x = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].akey[nCnt].fRotX + aKeyDiff[nCnt].fRotX * fMotionSpeed;
			pPlayer[0].aModel[nCnt].rot.y = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].akey[nCnt].fRotY + aKeyDiff[nCnt].fRotY * fMotionSpeed;
			pPlayer[0].aModel[nCnt].rot.z = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].akey[nCnt].fRotZ + aKeyDiff[nCnt].fRotZ * fMotionSpeed;
		}
	}
	else
	{
		for (int nCnt = 0; nCnt < 10; nCnt++)
		{
		
			pPlayer[0].aModel[nCnt].rot.x = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].akey[nCnt].fRotX;
			pPlayer[0].aModel[nCnt].rot.y = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].akey[nCnt].fRotY;
			pPlayer[0].aModel[nCnt].rot.z = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].akey[nCnt].fRotZ;
			float fMotionSpeed = (float)pPlayer[0].nCntMotion / (float)pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].nFrame;//再生speed
			pPlayer[0].aModel[nCnt].pos.x += aKeyDiff[nCnt].fPosX * fMotionSpeed;
		//	pPlayer[0].aModel[nCnt].pos.y += aKeyDiff[nCnt].fPosY * fMotionSpeed;
			pPlayer[0].aModel[nCnt].pos.z += aKeyDiff[nCnt].fPosZ * fMotionSpeed;
			pPlayer[0].aModel[nCnt].rot.x = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].akey[nCnt].fRotX + aKeyDiff[nCnt].fRotX * fMotionSpeed;
			pPlayer[0].aModel[nCnt].rot.y = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].akey[nCnt].fRotY + aKeyDiff[nCnt].fRotY * fMotionSpeed;
			pPlayer[0].aModel[nCnt].rot.z = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].akey[nCnt].fRotZ + aKeyDiff[nCnt].fRotZ * fMotionSpeed;
		}
	}

#if 0

			pPlayer[0].aModel[nCnt].pos.x = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].akey[nCnt].fPosX;
			pPlayer[0].aModel[nCnt].pos.y = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].akey[nCnt].fPosY;
			pPlayer[0].aModel[nCnt].pos.z = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].akey[nCnt].fPosZ;
    //毎回motion再生の初めている時、keyの差分を計算する && 今のkeyFrameは最後のkeyFrameではない
	if (pPlayer[0].nCntMotion == 0 && pPlayer[0].aMotionInfo[PlayerMotion].nNumkey != (pPlayer[0].aMotionInfo[PlayerMotion].nMAXkey))
	{
		for (int nCnt = 0; nCnt < 10; nCnt++)//10パーツを別々計算 
		{
			//差分=次のkeyframe - 今のkeyframe
			aKeyDiff[nCnt].fPosX = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey + 1].akey[nCnt].fPosX
				- pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].akey[nCnt].fPosX;
			aKeyDiff[nCnt].fPosY = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey + 1].akey[nCnt].fPosY
				- pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].akey[nCnt].fPosY;
			aKeyDiff[nCnt].fPosZ = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey + 1].akey[nCnt].fPosZ
				- pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].akey[nCnt].fPosZ;
			aKeyDiff[nCnt].fRotX = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey + 1].akey[nCnt].fRotX
				- pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].akey[nCnt].fRotX;
			aKeyDiff[nCnt].fRotY = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey + 1].akey[nCnt].fRotY
				- pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].akey[nCnt].fRotY;
			aKeyDiff[nCnt].fRotZ = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey + 1].akey[nCnt].fRotZ
				- pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].akey[nCnt].fRotZ;

			pPlayer[0].aModel[nCnt].rot.x = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].akey[nCnt].fRotX;
			pPlayer[0].aModel[nCnt].rot.y = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].akey[nCnt].fRotY;
			pPlayer[0].aModel[nCnt].rot.z = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].akey[nCnt].fRotZ;

			float fMotionSpeed = (float)pPlayer[0].nCntMotion / (float)pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].nFrame;//再生speed
			pPlayer[0].aModel[nCnt].rot.x = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].akey[nCnt].fRotX + aKeyDiff[nCnt].fRotX * fMotionSpeed;
			pPlayer[0].aModel[nCnt].rot.y = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].akey[nCnt].fRotY + aKeyDiff[nCnt].fRotY * fMotionSpeed;
			pPlayer[0].aModel[nCnt].rot.z = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].akey[nCnt].fRotZ + aKeyDiff[nCnt].fRotZ * fMotionSpeed;
		}
	}
	else if (pPlayer[0].aMotionInfo[PlayerMotion].nNumkey == pPlayer[0].aMotionInfo[PlayerMotion].nMAXkey - 1)
	{
		pPlayer[0].aMotionInfo[PlayerMotion].nNumkey = 0;
	}
	else if (pPlayer[0].nCntMotion == pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].nFrame)//今のkeyframeを再生の最後frameの時
	{
		//loopするためにのreset
		if (pPlayer[0].aMotionInfo[PlayerMotion].nNumkey == (pPlayer[0].aMotionInfo[PlayerMotion].nMAXkey - 1) && pPlayer[0].aMotionInfo[PlayerMotion].bLoop == true)
		{
			pPlayer[0].aMotionInfo[PlayerMotion].nNumkey = 0;
			//return MOTIONTYPE_WALK;
		}
		else
		{
			pPlayer[0].aMotionInfo[PlayerMotion].nNumkey++;//次のkeyframeに行く
			//return MOTIONTYPE_NEUTRAL;
		}
		pPlayer[0].nCntMotion = -1;//frameのreset
	}
#endif // 0
	//else//motion再生中
	//{
		//for (int nCnt = 0; nCnt < 10; nCnt++)
		//{
		//	float fMotionSpeed = (float)pPlayer[0].nCntMotion / (float)pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].nFrame;//再生speed
		//	pPlayer[0].aModel[nCnt].rot.x = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].akey[nCnt].fRotX;
		//	pPlayer[0].aModel[nCnt].rot.y = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].akey[nCnt].fRotY;
		//	pPlayer[0].aModel[nCnt].rot.z = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].akey[nCnt].fRotZ;
		//	 /*pPlayer[0].aModel[nCnt].pos.x += aKeyDiff[nCnt].fPosX * (pPlayer[0].nCntMotion / pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].nFrame);
		//	pPlayer[0].aModel[nCnt].pos.y += aKeyDiff[nCnt].fPosY * (pPlayer[0].nCntMotion / pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].nFrame);
		//	pPlayer[0].aModel[nCnt].pos.z += aKeyDiff[nCnt].fPosZ * (pPlayer[0].nCntMotion / pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].nFrame);*/
		//	pPlayer[0].aModel[nCnt].rot.x += aKeyDiff[nCnt].fRotX * ((float)pPlayer[0].nCntMotion / (float)pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].nFrame);
		//	pPlayer[0].aModel[nCnt].rot.y += aKeyDiff[nCnt].fRotY * ((float)pPlayer[0].nCntMotion / (float)pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].nFrame);
		//	pPlayer[0].aModel[nCnt].rot.z += aKeyDiff[nCnt].fRotZ * ((float)pPlayer[0].nCntMotion / (float)pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].nFrame);
		///*	pPlayer[0].aModel[nCnt].rot.x = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].akey[nCnt].fRotX + aKeyDiff[nCnt].fRotX * fMotionSpeed;
		//	pPlayer[0].aModel[nCnt].rot.y = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].akey[nCnt].fRotY + aKeyDiff[nCnt].fRotY * fMotionSpeed;
		//	pPlayer[0].aModel[nCnt].rot.z = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].akey[nCnt].fRotZ + aKeyDiff[nCnt].fRotZ * fMotionSpeed;*/
		//}

	//}
	return pPlayer[0].motionType;
}

void PlayFrame(void)
{
	for (int nCnt = 0; nCnt < 10; nCnt++)
	{
		float fMotionSpeed = (float)pPlayer[0].nCntMotion / (float)pPlayer[0].aMotionInfo[pPlayer[0].motionType].akeyInfo[pPlayer[0].aMotionInfo[pPlayer[0].motionType].nNumkey].nFrame;//再生speed
		pPlayer[0].aModel[nCnt].rot.x = pPlayer[0].aMotionInfo[pPlayer[0].motionType].akeyInfo[pPlayer[0].aMotionInfo[pPlayer[0].motionType].nNumkey].akey[nCnt].fRotX;
		pPlayer[0].aModel[nCnt].rot.y = pPlayer[0].aMotionInfo[pPlayer[0].motionType].akeyInfo[pPlayer[0].aMotionInfo[pPlayer[0].motionType].nNumkey].akey[nCnt].fRotY;
		pPlayer[0].aModel[nCnt].rot.z = pPlayer[0].aMotionInfo[pPlayer[0].motionType].akeyInfo[pPlayer[0].aMotionInfo[pPlayer[0].motionType].nNumkey].akey[nCnt].fRotZ;
		pPlayer[0].aModel[nCnt].rot.x += aKeyDiff[nCnt].fRotX * ((float)pPlayer[0].nCntMotion / (float)pPlayer[0].aMotionInfo[pPlayer[0].motionType].akeyInfo[pPlayer[0].aMotionInfo[pPlayer[0].motionType].nNumkey].nFrame);
		pPlayer[0].aModel[nCnt].rot.y += aKeyDiff[nCnt].fRotY * ((float)pPlayer[0].nCntMotion / (float)pPlayer[0].aMotionInfo[pPlayer[0].motionType].akeyInfo[pPlayer[0].aMotionInfo[pPlayer[0].motionType].nNumkey].nFrame);
		pPlayer[0].aModel[nCnt].rot.z += aKeyDiff[nCnt].fRotZ * ((float)pPlayer[0].nCntMotion / (float)pPlayer[0].aMotionInfo[pPlayer[0].motionType].akeyInfo[pPlayer[0].aMotionInfo[pPlayer[0].motionType].nNumkey].nFrame);
	}
	pPlayer[0].nCntMotion++;//次のframeに行く (not KeyFrame)
}

void GetKeyDifference(int FrameNow, int FrameNext)
{
	for (int nCnt = 0; nCnt < 10; nCnt++)
	{
		aKeyDiff[nCnt].fPosX = pPlayer[0].aMotionInfo[pPlayer[0].motionType].akeyInfo[FrameNext].akey[nCnt].fPosX
			- pPlayer[0].aMotionInfo[pPlayer[0].motionType].akeyInfo[FrameNow].akey[nCnt].fPosX;
		aKeyDiff[nCnt].fPosX = pPlayer[0].aMotionInfo[pPlayer[0].motionType].akeyInfo[FrameNext].akey[nCnt].fPosY
			- pPlayer[0].aMotionInfo[pPlayer[0].motionType].akeyInfo[FrameNow].akey[nCnt].fPosY;
		aKeyDiff[nCnt].fPosX = pPlayer[0].aMotionInfo[pPlayer[0].motionType].akeyInfo[FrameNext].akey[nCnt].fPosZ
			- pPlayer[0].aMotionInfo[pPlayer[0].motionType].akeyInfo[FrameNow].akey[nCnt].fPosZ;
		aKeyDiff[nCnt].fPosX = pPlayer[0].aMotionInfo[pPlayer[0].motionType].akeyInfo[FrameNext].akey[nCnt].fRotX
			- pPlayer[0].aMotionInfo[pPlayer[0].motionType].akeyInfo[FrameNow].akey[nCnt].fRotX;
		aKeyDiff[nCnt].fPosX = pPlayer[0].aMotionInfo[pPlayer[0].motionType].akeyInfo[FrameNext].akey[nCnt].fRotY
			- pPlayer[0].aMotionInfo[pPlayer[0].motionType].akeyInfo[FrameNow].akey[nCnt].fRotY;
		aKeyDiff[nCnt].fPosX = pPlayer[0].aMotionInfo[pPlayer[0].motionType].akeyInfo[FrameNext].akey[nCnt].fRotZ
			- pPlayer[0].aMotionInfo[pPlayer[0].motionType].akeyInfo[FrameNow].akey[nCnt].fRotZ;
	}
}
