#define _CRT_SECURE_NO_WARNINGS
#include "Player.h"
#include "Dinput8.h"
#include "Camera.h"
#include "SnowBall.h"
#include "WorldModel.h"
#include "Collision.h"
#include "Enemy.h"
#include "Fade.h"
#include "Ground.h"
#include "sound.h"

KEY aKeyDiff[10];//10パーツ
LPD3DXMESH g_pMeshPlayer = NULL;
LPD3DXBUFFER g_pBuffMatPlayer = NULL;
DWORD g_nNumMatPlayer = 0;
PLAYER *pPlayer;

float g_fGravityPlayer = 2.0f;
int nCntTime = 0;
bool bCarAlert = false;
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
	nCntTime = 0;
	g_fGravityPlayer = 2.0f;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pPlayer = (PLAYER*)malloc(1 * sizeof(PLAYER));
	pPlayer[0].nNumModel = 10;//パーツ数=9
	if (FAILED(D3DXLoadMeshFromX("data/MODEL/Player/3Dgame_body.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &pPlayer[0].aModel[0].Xfile_Materials, NULL, &pPlayer[0].aModel[0].Xfile_MaterialNum, &pPlayer[0].aModel[0].Xfile_Mesh))) return E_FAIL;
	if (FAILED(D3DXLoadMeshFromX("data/MODEL/Player/3Dgame_head.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &pPlayer[0].aModel[1].Xfile_Materials, NULL, &pPlayer[0].aModel[1].Xfile_MaterialNum, &pPlayer[0].aModel[1].Xfile_Mesh))) return E_FAIL;
	if (FAILED(D3DXLoadMeshFromX("data/MODEL/Player/3Dgame_armR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &pPlayer[0].aModel[2].Xfile_Materials, NULL, &pPlayer[0].aModel[2].Xfile_MaterialNum, &pPlayer[0].aModel[2].Xfile_Mesh))) return E_FAIL;
	if (FAILED(D3DXLoadMeshFromX("data/MODEL/Player/3Dgame_handR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &pPlayer[0].aModel[3].Xfile_Materials, NULL, &pPlayer[0].aModel[3].Xfile_MaterialNum, &pPlayer[0].aModel[3].Xfile_Mesh))) return E_FAIL;
	if (FAILED(D3DXLoadMeshFromX("data/MODEL/Player/3Dgame_armL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &pPlayer[0].aModel[4].Xfile_Materials, NULL, &pPlayer[0].aModel[4].Xfile_MaterialNum, &pPlayer[0].aModel[4].Xfile_Mesh))) return E_FAIL;
	if (FAILED(D3DXLoadMeshFromX("data/MODEL/Player/3Dgame_handL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &pPlayer[0].aModel[5].Xfile_Materials, NULL, &pPlayer[0].aModel[5].Xfile_MaterialNum, &pPlayer[0].aModel[5].Xfile_Mesh))) return E_FAIL;
	if (FAILED(D3DXLoadMeshFromX("data/MODEL/Player/3Dgame_legR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &pPlayer[0].aModel[6].Xfile_Materials, NULL, &pPlayer[0].aModel[6].Xfile_MaterialNum, &pPlayer[0].aModel[6].Xfile_Mesh))) return E_FAIL;
	if (FAILED(D3DXLoadMeshFromX("data/MODEL/Player/3Dgame_footR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &pPlayer[0].aModel[7].Xfile_Materials, NULL, &pPlayer[0].aModel[7].Xfile_MaterialNum, &pPlayer[0].aModel[7].Xfile_Mesh))) return E_FAIL;
	if (FAILED(D3DXLoadMeshFromX("data/MODEL/Player/3Dgame_legL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &pPlayer[0].aModel[8].Xfile_Materials, NULL, &pPlayer[0].aModel[8].Xfile_MaterialNum, &pPlayer[0].aModel[8].Xfile_Mesh))) return E_FAIL;
	if (FAILED(D3DXLoadMeshFromX("data/MODEL/Player/3Dgame_footL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &pPlayer[0].aModel[9].Xfile_Materials, NULL, &pPlayer[0].aModel[9].Xfile_MaterialNum, &pPlayer[0].aModel[9].Xfile_Mesh))) return E_FAIL;

	//親子関係の設定
	pPlayer[0].aModel[0].nIdxModelParent = -1;
	pPlayer[0].aModel[1].nIdxModelParent = 0;
	pPlayer[0].aModel[2].nIdxModelParent = 0;
	pPlayer[0].aModel[3].nIdxModelParent = 2;
	pPlayer[0].aModel[4].nIdxModelParent = 0;
	pPlayer[0].aModel[5].nIdxModelParent = 4;
	pPlayer[0].aModel[6].nIdxModelParent = 0;
	pPlayer[0].aModel[7].nIdxModelParent = 6;
	pPlayer[0].aModel[8].nIdxModelParent = 0;
	pPlayer[0].aModel[9].nIdxModelParent = 8;

	pPlayer[0].aModel[0].pos = D3DXVECTOR3(0.0f, 15.f, 0.0f);
	pPlayer[0].aModel[1].pos = D3DXVECTOR3(0.0f, 15.f, 0.0f);
	pPlayer[0].aModel[2].pos = D3DXVECTOR3(-7.5f, 12.0f, 0.0f);
	pPlayer[0].aModel[3].pos = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);
	pPlayer[0].aModel[4].pos = D3DXVECTOR3(7.5f, 12.0f, 0.0f);
	pPlayer[0].aModel[5].pos = D3DXVECTOR3(10.0f, 0.0f, 0.0f);
	pPlayer[0].aModel[6].pos = D3DXVECTOR3(-4.0f, 0.0f, 0.0f);
	pPlayer[0].aModel[7].pos = D3DXVECTOR3(0.0f, -10.0f, 0.0f);
	pPlayer[0].aModel[8].pos = D3DXVECTOR3(4.0f, 0.0f, 0.0f);
	pPlayer[0].aModel[9].pos = D3DXVECTOR3(0.0f, -10.0f, 0.0f);

	for (int nCnt = 0; nCnt < 10; nCnt++) pPlayer[0].aModel[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	pPlayer[0].pos = D3DXVECTOR3(0.f, 0.f, 0.f);
	pPlayer[0].move = D3DXVECTOR3(0.f, 0.f, 0.f);
	pPlayer[0].rot = D3DXVECTOR3(0.f, D3DX_PI, 0.f);
	pPlayer[0].ID = 0;
	pPlayer[0].fMoveSpeed = 5.f;
	pPlayer[0].nScore = 0;
	ReadMotion();
	InitGameCamera();
	return S_OK;
}
void UninitPlayer(void)
{
	free(pPlayer);
}

void UpdatePlayer(void)
{
	D3DXVECTOR2 pMoveMouse = GetMouseVelocity();
	CAMERA *pCamera = GetCamera();
	nCntTime++;
	//snowball set
	D3DXVECTOR3 Hand_pos = pPlayer[0].pos + pPlayer[0].aModel[0].pos + pPlayer[0].aModel[4].pos + pPlayer[0].aModel[5].pos;
	Hand_pos.z += (pPlayer[0].aModel[4].pos.x + pPlayer[0].aModel[5].pos.x) * sinf(-pCamera->fRot.y);
	Hand_pos.x = pPlayer[0].pos.x + pPlayer[0].aModel[0].pos.x - (pPlayer[0].aModel[4].pos.x + pPlayer[0].aModel[5].pos.x) * cosf(-pCamera->fRot.y);
	D3DXVECTOR3 SnowBall_Move = pCamera->posR - pPlayer[0].pos;

	pPlayer[0].move.x = 0.0f;
	pPlayer[0].move.z = 0.0f;
	if (pPlayer[0].pos.y >= 0) pPlayer[0].move.y -= g_fGravityPlayer;
	else pPlayer[0].move.y = 0;

	if (pPlayer[0].state == P_NEUTRAL)
	{
		if (GetkeyboardPress(DIK_W) == true)
		{
			if (GetkeyboardPress(DIK_D) == true)
			{
				pPlayer[0].rot.y = D3DX_PI / 4 - pCamera[0].fRot.y;
				pPlayer[0].move.x = -sinf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed;
				pPlayer[0].move.z = -cosf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed;
				pPlayer[0].state = P_RUN;
				pPlayer[0].nCntMotion = 0;
			}
			else if (GetkeyboardPress(DIK_A) == true)
			{
				pPlayer[0].rot.y = -D3DX_PI / 4 - pCamera[0].fRot.y;
				pPlayer[0].move.x = -sinf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed;
				pPlayer[0].move.z = -cosf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed;
				pPlayer[0].state = P_RUN;
				pPlayer[0].nCntMotion = 0;
			}
			else
			{
				pPlayer[0].rot.y = -pCamera[0].fRot.y;
				pPlayer[0].move.x = -sinf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed;
				pPlayer[0].move.z = -cosf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed;
				pPlayer[0].state = P_RUN;
				pPlayer[0].nCntMotion = 0;
			}
		}
		else if (GetkeyboardPress(DIK_S) == true)
		{
			if (GetkeyboardPress(DIK_A) == true)
			{
				pPlayer[0].rot.y = D3DX_PI / 4 - pCamera[0].fRot.y;
				pPlayer[0].move.x = +sinf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed / 4;
				pPlayer[0].move.z = +cosf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed / 4;
				pPlayer[0].state = P_BACK;
				pPlayer[0].nCntMotion = 0;
			}
			else if (GetkeyboardPress(DIK_D) == true)
			{
				pPlayer[0].rot.y = -D3DX_PI / 4 - pCamera[0].fRot.y;
				pPlayer[0].move.x = sinf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed / 4;
				pPlayer[0].move.z = cosf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed / 4;
				pPlayer[0].state = P_BACK;
				pPlayer[0].nCntMotion = 0;
			}
			else
			{
				pPlayer[0].rot.y = -pCamera[0].fRot.y;
				pPlayer[0].move.x = sinf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed / 4;
				pPlayer[0].move.z = cosf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed / 4;
				pPlayer[0].state = P_BACK;
				pPlayer[0].nCntMotion = 0;
			}
		}
		else if (GetkeyboardPress(DIK_A) == true)
		{
			pPlayer[0].rot.y = -D3DX_PI / 2 - pCamera[0].fRot.y;
			pPlayer[0].move.x = -sinf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed;
			pPlayer[0].move.z = -cosf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed;
			pPlayer[0].state = P_RUN;
			pPlayer[0].nCntMotion = 0;
		}
		else if (GetkeyboardPress(DIK_D) == true)
		{
			pPlayer[0].rot.y = D3DX_PI / 2 - pCamera[0].fRot.y;
			pPlayer[0].move.x = -sinf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed;
			pPlayer[0].move.z = -cosf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed;
			pPlayer[0].state = P_RUN;
			pPlayer[0].nCntMotion = 0;
		}

		if (GetkeyboardTrigger(DIK_SPACE) == true)
		{
			pPlayer[0].state = P_THROW;
			pPlayer[0].nCntMotion = 0;
			pPlayer[0].aMotionInfo[P_THROW].bLock = true;
			pPlayer[0].rot.y = -pCamera[0].fRot.y;
		}
	}
	else if (pPlayer[0].state == P_RUN)
	{
		if (GetkeyboardPress(DIK_W) == true)
		{
			if (GetkeyboardPress(DIK_D) == true)
			{
				pPlayer[0].rot.y = D3DX_PI / 4 - pCamera[0].fRot.y;
				pPlayer[0].move.x = -sinf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed;
				pPlayer[0].move.z = -cosf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed;
			}
			else if (GetkeyboardPress(DIK_A) == true)
			{
				pPlayer[0].rot.y = -D3DX_PI / 4 - pCamera[0].fRot.y;
				pPlayer[0].move.x = -sinf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed;
				pPlayer[0].move.z = -cosf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed;
			}
			else
			{
				pPlayer[0].rot.y = -pCamera[0].fRot.y;
				pPlayer[0].move.x = -sinf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed;
				pPlayer[0].move.z = -cosf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed;
			}
		}
		else if (GetkeyboardPress(DIK_S) == true)
		{
			if (GetkeyboardPress(DIK_A) == true)
			{
				pPlayer[0].rot.y = D3DX_PI / 4 - pCamera[0].fRot.y;
				pPlayer[0].move.x = +sinf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed / 4;
				pPlayer[0].move.z = +cosf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed / 4;
				pPlayer[0].state = P_BACK;
				pPlayer[0].nCntMotion = 0;
			}
			else if (GetkeyboardPress(DIK_D) == true)
			{
				pPlayer[0].rot.y = -D3DX_PI / 4 - pCamera[0].fRot.y;
				pPlayer[0].move.x = sinf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed / 4;
				pPlayer[0].move.z = cosf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed / 4;
				pPlayer[0].state = P_BACK;
				pPlayer[0].nCntMotion = 0;
			}
			else
			{
				pPlayer[0].rot.y = -pCamera[0].fRot.y;
				pPlayer[0].move.x = sinf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed / 4;
				pPlayer[0].move.z = cosf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed / 4;
				pPlayer[0].state = P_BACK;
				pPlayer[0].nCntMotion = 0;
			}
		}
		else if (GetkeyboardPress(DIK_A) == true)
		{
			pPlayer[0].rot.y = -D3DX_PI / 2 - pCamera[0].fRot.y;
			pPlayer[0].move.x = -sinf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed;
			pPlayer[0].move.z = -cosf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed;

		}
		else if (GetkeyboardPress(DIK_D) == true)
		{
			pPlayer[0].rot.y = D3DX_PI / 2 - pCamera[0].fRot.y;
			pPlayer[0].move.x = -sinf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed;
			pPlayer[0].move.z = -cosf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed;
		}
		else
		{
			pPlayer[0].state = P_NEUTRAL;
			pPlayer[0].nCntMotion = 0;
		}


		if (GetkeyboardTrigger(DIK_SPACE) == true)
		{
			pPlayer[0].state = P_THROW;
			pPlayer[0].nCntMotion = 0;
			pPlayer[0].aMotionInfo[P_THROW].bLock = true;
			pPlayer[0].rot.y = -pCamera[0].fRot.y;
		}
	}
	else if (pPlayer[0].state == P_BACK)
	{
		if (GetkeyboardPress(DIK_W) == true)
		{
			if (GetkeyboardPress(DIK_D) == true)
			{
				pPlayer[0].rot.y = D3DX_PI / 4 - pCamera[0].fRot.y;
				pPlayer[0].move.x = -sinf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed;
				pPlayer[0].move.z = -cosf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed;
				pPlayer[0].state = P_RUN;
				pPlayer[0].nCntMotion = 0;
			}
			else if (GetkeyboardPress(DIK_A) == true)
			{
				pPlayer[0].rot.y = -D3DX_PI / 4 - pCamera[0].fRot.y;
				pPlayer[0].move.x = -sinf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed;
				pPlayer[0].move.z = -cosf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed;
				pPlayer[0].state = P_RUN;
				pPlayer[0].nCntMotion = 0;
			}
			else
			{
				pPlayer[0].rot.y = -pCamera[0].fRot.y;
				pPlayer[0].move.x = -sinf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed;
				pPlayer[0].move.z = -cosf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed;
				pPlayer[0].state = P_RUN;
				pPlayer[0].nCntMotion = 0;
			}
		}
		else if (GetkeyboardPress(DIK_S) == true)
		{
			if (GetkeyboardPress(DIK_A) == true)
			{
				pPlayer[0].rot.y = D3DX_PI / 4 - pCamera[0].fRot.y;
				pPlayer[0].move.x = +sinf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed / 4;
				pPlayer[0].move.z = +cosf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed / 4;
			}
			else if (GetkeyboardPress(DIK_D) == true)
			{
				pPlayer[0].rot.y = -D3DX_PI / 4 - pCamera[0].fRot.y;
				pPlayer[0].move.x = sinf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed / 4;
				pPlayer[0].move.z = cosf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed / 4;
			}
			else
			{
				pPlayer[0].rot.y = -pCamera[0].fRot.y;
				pPlayer[0].move.x = sinf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed / 4;
				pPlayer[0].move.z = cosf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed / 4;
			}
		}
		else if (GetkeyboardPress(DIK_A) == true)
		{
			pPlayer[0].rot.y = -D3DX_PI / 2 - pCamera[0].fRot.y;
			pPlayer[0].move.x = -sinf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed;
			pPlayer[0].move.z = -cosf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed;
			pPlayer[0].state = P_RUN;
			pPlayer[0].nCntMotion = 0;
		}
		else if (GetkeyboardPress(DIK_D) == true)
		{
			pPlayer[0].rot.y = D3DX_PI / 2 - pCamera[0].fRot.y;
			pPlayer[0].move.x = -sinf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed;
			pPlayer[0].move.z = -cosf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed;
			pPlayer[0].state = P_RUN;
			pPlayer[0].nCntMotion = 0;
		}
		else
		{
			pPlayer[0].state = P_NEUTRAL;
			pPlayer[0].nCntMotion = 0;
		}

		if (GetkeyboardTrigger(DIK_SPACE) == true)
		{
			pPlayer[0].state = P_THROW;
			pPlayer[0].nCntMotion = 0;
			pPlayer[0].aMotionInfo[P_THROW].bLock = true;
			pPlayer[0].rot.y = -pCamera[0].fRot.y;
		}
	}
	else if (pPlayer[0].state == P_THROW)
	{
		if (pPlayer[0].aMotionInfo[P_THROW].nNumkey == 2 && pPlayer[0].nCntMotion == 1)
		{
			SetSnowBall(Hand_pos, SnowBall_Move);
		}
		if (pPlayer[0].aMotionInfo[P_THROW].bLock == false)
		{
			if (GetkeyboardPress(DIK_W) == true)
			{
				if (GetkeyboardPress(DIK_D) == true)
				{
					pPlayer[0].rot.y = D3DX_PI / 4 - pCamera[0].fRot.y;
					pPlayer[0].move.x = -sinf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed;
					pPlayer[0].move.z = -cosf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed;
					pPlayer[0].state = P_RUN;
					pPlayer[0].nCntMotion = 0;
				}
				else if (GetkeyboardPress(DIK_A) == true)
				{
					pPlayer[0].rot.y = -D3DX_PI / 4 - pCamera[0].fRot.y;
					pPlayer[0].move.x = -sinf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed;
					pPlayer[0].move.z = -cosf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed;
					pPlayer[0].state = P_RUN;
					pPlayer[0].nCntMotion = 0;
				}
				else
				{
					pPlayer[0].rot.y = -pCamera[0].fRot.y;
					pPlayer[0].move.x = -sinf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed;
					pPlayer[0].move.z = -cosf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed;
					pPlayer[0].state = P_RUN;
					pPlayer[0].nCntMotion = 0;
				}
			}
			else if (GetkeyboardPress(DIK_S) == true)
			{
				if (GetkeyboardPress(DIK_A) == true)
				{
					pPlayer[0].rot.y = D3DX_PI / 4 - pCamera[0].fRot.y;
					pPlayer[0].move.x = +sinf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed / 4;
					pPlayer[0].move.z = +cosf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed / 4;
					pPlayer[0].state = P_BACK;
					pPlayer[0].nCntMotion = 0;
				}
				else if (GetkeyboardPress(DIK_D) == true)
				{
					pPlayer[0].rot.y = -D3DX_PI / 4 - pCamera[0].fRot.y;
					pPlayer[0].move.x = sinf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed / 4;
					pPlayer[0].move.z = cosf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed / 4;
					pPlayer[0].state = P_BACK;
					pPlayer[0].nCntMotion = 0;
				}
				else
				{
					pPlayer[0].rot.y = -pCamera[0].fRot.y;
					pPlayer[0].move.x = sinf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed / 4;
					pPlayer[0].move.z = cosf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed / 4;
					pPlayer[0].state = P_BACK;
					pPlayer[0].nCntMotion = 0;
				}
			}
			else if (GetkeyboardPress(DIK_A) == true)
			{
				pPlayer[0].rot.y = -D3DX_PI / 2 - pCamera[0].fRot.y;
				pPlayer[0].move.x = -sinf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed;
				pPlayer[0].move.z = -cosf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed;
				pPlayer[0].state = P_RUN;
				pPlayer[0].nCntMotion = 0;
			}
			else if (GetkeyboardPress(DIK_D) == true)
			{
				pPlayer[0].rot.y = D3DX_PI / 2 - pCamera[0].fRot.y;
				pPlayer[0].move.x = -sinf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed;
				pPlayer[0].move.z = -cosf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed;
				pPlayer[0].state = P_RUN;
				pPlayer[0].nCntMotion = 0;
			}
			else
			{
				pPlayer[0].state = P_NEUTRAL;
				pPlayer[0].nCntMotion = 0;
			}
		}	
		else
		{
			if (GetkeyboardPress(DIK_W) == true)
			{
				if (GetkeyboardPress(DIK_D) == true)
				{
					pPlayer[0].rot.y = D3DX_PI / 4 - pCamera[0].fRot.y;
					pPlayer[0].move.x = -sinf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed;
					pPlayer[0].move.z = -cosf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed;
				}
				else if (GetkeyboardPress(DIK_A) == true)
				{
					pPlayer[0].rot.y = -D3DX_PI / 4 - pCamera[0].fRot.y;
					pPlayer[0].move.x = -sinf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed;
					pPlayer[0].move.z = -cosf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed;
				}
				else
				{
					pPlayer[0].rot.y = -pCamera[0].fRot.y;
					pPlayer[0].move.x = -sinf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed;
					pPlayer[0].move.z = -cosf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed;
				}
			}
			else if (GetkeyboardPress(DIK_S) == true)
			{
				if (GetkeyboardPress(DIK_A) == true)
				{
					pPlayer[0].rot.y = D3DX_PI / 4 - pCamera[0].fRot.y;
					pPlayer[0].move.x = +sinf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed / 4;
					pPlayer[0].move.z = +cosf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed / 4;
				}
				else if (GetkeyboardPress(DIK_D) == true)
				{
					pPlayer[0].rot.y = -D3DX_PI / 4 - pCamera[0].fRot.y;
					pPlayer[0].move.x = sinf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed / 4;
					pPlayer[0].move.z = cosf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed / 4;
				}
				else
				{
					pPlayer[0].rot.y = -pCamera[0].fRot.y;
					pPlayer[0].move.x = sinf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed / 4;
					pPlayer[0].move.z = cosf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed / 4;
				}
			}
			else if (GetkeyboardPress(DIK_A) == true)
			{
				pPlayer[0].rot.y = -D3DX_PI / 2 - pCamera[0].fRot.y;
				pPlayer[0].move.x = -sinf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed;
				pPlayer[0].move.z = -cosf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed;
			}
			else if (GetkeyboardPress(DIK_D) == true)
			{
				pPlayer[0].rot.y = D3DX_PI / 2 - pCamera[0].fRot.y;
				pPlayer[0].move.x = -sinf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed;
				pPlayer[0].move.z = -cosf(pPlayer[0].rot.y) * pPlayer[0].fMoveSpeed;
			}
		}
	}
	else if (pPlayer[0].state == P_DEAD)
	{
		if (nCntTime % 300 == 0)
		{
			SetFade(FADE_OUT, MODE_RANKING);
		}
	}

	MODEL *pModel = GetWorldModel();
	bool bCol = false;
	
	for (int nCntMod = 0; nCntMod < WORLDMODEL_NUM; nCntMod++, pModel++)
	{
		if ((fabsf(pModel->pos.x - pPlayer[0].pos.x) <= 800) && fabsf(pModel->pos.z - pPlayer[0].pos.z) <= 100)
		{
			if (bCarAlert == false)
			{
				PlaySound(SOUND_LABEL_SE_CARHORN);
				bCarAlert = true;
			}
			else if (nCntTime % 100 == 0)
			{
				bCarAlert = false;
			}
		}
		bCol = CollisionDetection(D3DXVECTOR3(pPlayer[0].pos.x, pPlayer[0].pos.y + 30, pPlayer[0].pos.z), pModel->MinColBox, pModel->MaxColBox);
		if (bCol == true)
		{
			PlaySound(SOUND_LABEL_SE_CARSTRIKE);
			pPlayer[0].state = P_DEAD;
			pPlayer[0].move.x = pModel->move.x * 50.0f;
			pPlayer[0].move.z = pModel->move.x * 20.0f;
			pPlayer[0].move.y = pModel->move.x * 2.0f;
			pPlayer[0].rot.x = -D3DX_PI / 2;
		}
	}
	MODEL *pEnemy = GetEnemy();
	bCol = false;
	for (int nCntEnemy = 0; nCntEnemy < ENEMY_NUM; nCntEnemy++, pEnemy++)
	{
		if (pEnemy->bMove == true)
		{
			bCol = CollisionDetection(D3DXVECTOR3(pPlayer[0].pos.x, pPlayer[0].pos.y + 15, pPlayer[0].pos.z), pEnemy->MinColBox, pEnemy->MaxColBox);
			if (bCol == true)
			{
				PlaySound(SOUND_LABEL_SE_SNOWBALL);
				pEnemy->pos.x -= -sinf(pEnemy->rot.y) * pEnemy->fMoveSpeed * 2;
				pEnemy->pos.z -= -cosf(pEnemy->rot.y) * pEnemy->fMoveSpeed * 2;
				pEnemy->pos.y += 10.f;
				pEnemy->bMove = false;
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

	if (pPlayer[0].pos.x > (MAP_SIZE_X - 200)) pPlayer[0].pos.x = MAP_SIZE_X - 200;
	else if (pPlayer[0].pos.x < (-MAP_SIZE_X + 200)) pPlayer[0].pos.x = (-MAP_SIZE_X + 200);
	else if (pPlayer[0].pos.z > (MAP_SIZE_Y - 200)) pPlayer[0].pos.z = (MAP_SIZE_Y - 200);
	else if (pPlayer[0].pos.z < (-MAP_SIZE_Y + 200)) pPlayer[0].pos.z = (-MAP_SIZE_Y + 200);
	else
	{
		pPlayer[0].pos += pPlayer[0].move;
		pCamera->posV.x += pPlayer[0].move.x;
		pCamera->posV.y += pPlayer[0].move.y;
		pCamera->posV.z += pPlayer[0].move.z;
		pCamera->posR.x += pPlayer[0].move.x;
		pCamera->posR.z += pPlayer[0].move.z;
		pCamera->posR.y += pPlayer[0].move.y;
	}
	

	if (pPlayer[0].state != P_DEAD)
	{
		PlayMotion(pPlayer[0].state);
	}
}

void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//Player bodyの座標と向きの基準計算
	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;
	D3DXMATERIAL *pMat;
	D3DXMatrixIdentity(&pPlayer[0].mtxworld);
	D3DXMatrixRotationYawPitchRoll(&mtxRot, pPlayer[0].rot.y, pPlayer[0].rot.x, pPlayer[0].rot.z);
	D3DXMatrixMultiply(&pPlayer[0].mtxworld, &pPlayer[0].mtxworld, &mtxRot);
	D3DXMatrixTranslation(&mtxTrans, pPlayer[0].pos.x, pPlayer[0].pos.y, pPlayer[0].pos.z); //世界matrix全体　移動したい距離というmatrixの合算
	D3DXMatrixMultiply(&pPlayer[0].mtxworld, &pPlayer[0].mtxworld, &mtxTrans); //世界matrixの移動
	pDevice->SetTransform(D3DTS_WORLD, &pPlayer[0].mtxworld);
	pDevice->GetMaterial(&matDef);

	//Playe各部パーツの座標と向き計算
	for (int nCntModel = 0; nCntModel < pPlayer[0].nNumModel; nCntModel++)
	{
		D3DXMATRIX mtxRotModel, mtxTransModel;
		D3DXMATRIX mtxParent;
		D3DXMatrixIdentity(&pPlayer[0].aModel[nCntModel].Xfile_Mtxworld);
		D3DXMatrixRotationYawPitchRoll(&mtxRotModel, pPlayer[0].aModel[nCntModel].rot.y, pPlayer[0].aModel[nCntModel].rot.x, pPlayer[0].aModel[nCntModel].rot.z);
		D3DXMatrixMultiply(&pPlayer[0].aModel[nCntModel].Xfile_Mtxworld, &pPlayer[0].aModel[nCntModel].Xfile_Mtxworld, &mtxRotModel);
		D3DXMatrixTranslation(&mtxTransModel, pPlayer[0].aModel[nCntModel].pos.x, pPlayer[0].aModel[nCntModel].pos.y, pPlayer[0].aModel[nCntModel].pos.z); //世界matrix全体　移動したい距離というmatrixの合算
		D3DXMatrixMultiply(&pPlayer[0].aModel[nCntModel].Xfile_Mtxworld, &pPlayer[0].aModel[nCntModel].Xfile_Mtxworld, &mtxTransModel); //世界matrixの移動
		//親からの座標matrixの設定
		if (pPlayer[0].aModel[nCntModel].nIdxModelParent == -1) mtxParent = pPlayer[0].mtxworld;
		else mtxParent = pPlayer[0].aModel[pPlayer[0].aModel[nCntModel].nIdxModelParent].Xfile_Mtxworld;
		//合算
		D3DXMatrixMultiply(&pPlayer[0].aModel[nCntModel].Xfile_Mtxworld, &pPlayer[0].aModel[nCntModel].Xfile_Mtxworld, &mtxParent);
		//描画
		pDevice->SetTransform(D3DTS_WORLD, &pPlayer[0].aModel[nCntModel].Xfile_Mtxworld); //set the world into Map

		pMat = (D3DXMATERIAL*)pPlayer[0].aModel[nCntModel].Xfile_Materials->GetBufferPointer();
		for (int nCntMat = 0; nCntMat < (int)pPlayer[0].aModel[nCntModel].Xfile_MaterialNum; nCntMat++)
		{
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
			pDevice->SetTexture(0, NULL);
			pPlayer[0].aModel[nCntModel].Xfile_Mesh->DrawSubset(nCntMat);
		}
	}
	pDevice->SetMaterial(&matDef);
}

PLAYER *GetPlayer(void)
{
	return pPlayer;
}

void ReadMotion(void)
{
	FILE *pFile;
	pFile = fopen("Motion.txt", "r");
	pPlayer[0].nNumMotion = 4;//motionの数
	pPlayer[0].nNumModel = 10;//parts数
	pPlayer[0].nCntMotion = 0;
	pPlayer[0].state = P_NEUTRAL;
	pPlayer[0].aMotionInfo[P_RUN].bLoop = true;
	pPlayer[0].aMotionInfo[P_RUN].bLock = false;
	pPlayer[0].aMotionInfo[P_NEUTRAL].bLoop = true;
	pPlayer[0].aMotionInfo[P_NEUTRAL].bLock = false;
	pPlayer[0].aMotionInfo[P_BACK].bLoop = true;
	pPlayer[0].aMotionInfo[P_BACK].bLock = false;
	pPlayer[0].aMotionInfo[P_THROW].bLoop = false;
	pPlayer[0].aMotionInfo[P_THROW].bLock = false;

	for (int nCnt = 0; nCnt < P_MAX; nCnt++) pPlayer[0].aMotionInfo[nCnt].nNumkey = 1;

	for (int nCnt1 = 0; nCnt1 < pPlayer[0].nNumMotion; nCnt1++)
	{
		fscanf(pFile, "%d", &pPlayer[0].aMotionInfo[nCnt1].nMAXkey);//motionのkeyframeの数を読み込む
		for (int nCnt2 = 1; nCnt2 <= pPlayer[0].aMotionInfo[nCnt1].nMAXkey; nCnt2++)
		{
			fscanf(pFile, "%d", &pPlayer[0].aMotionInfo[nCnt1].akeyInfo[nCnt2].nFrame);//motionのkeyframeの再生speedを読み込む
			for (int nCnt3 = 0; nCnt3 < pPlayer[0].nNumModel; nCnt3++)
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

void PlayMotion(int PlayerMotion)
{
	pPlayer[0].nCntMotion++;
	CAMERA *pCamera = GetCamera();

	if (PlayerMotion == P_THROW)
	{
		if (pPlayer[0].nCntMotion == 1)
		{
			if (pPlayer[0].aMotionInfo[PlayerMotion].nNumkey == pPlayer[0].aMotionInfo[PlayerMotion].nMAXkey)
			{
				pPlayer[0].aMotionInfo[PlayerMotion].bLock = false;
				pPlayer[0].aMotionInfo[PlayerMotion].nNumkey = 1;
			}
			else
			{
				for (int nCnt = 0; nCnt < 6; nCnt++)//6パーツを別々計算  上半身！！
				{
					//差分=次のkeyframe - 今のkeyframe
					aKeyDiff[nCnt].fPosX = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey + 1].akey[nCnt].fPosX - pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].akey[nCnt].fPosX;
					aKeyDiff[nCnt].fPosY = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey + 1].akey[nCnt].fPosY - pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].akey[nCnt].fPosY;
					aKeyDiff[nCnt].fPosZ = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey + 1].akey[nCnt].fPosZ - pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].akey[nCnt].fPosZ;
					aKeyDiff[nCnt].fRotX = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey + 1].akey[nCnt].fRotX - pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].akey[nCnt].fRotX;
					aKeyDiff[nCnt].fRotY = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey + 1].akey[nCnt].fRotY - pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].akey[nCnt].fRotY;
					aKeyDiff[nCnt].fRotZ = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey + 1].akey[nCnt].fRotZ - pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].akey[nCnt].fRotZ;
				}
			}
		}
		if (pPlayer[0].aMotionInfo[PlayerMotion].nNumkey == pPlayer[0].aMotionInfo[PlayerMotion].nMAXkey)
		{
			for (int nCnt = 0; nCnt < 6; nCnt++)//上半身！！
			{
				float fMotionSpeed = (float)pPlayer[0].nCntMotion / (float)pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nMAXkey].nFrame;//再生speed
				pPlayer[0].aModel[nCnt].pos.x += aKeyDiff[nCnt].fPosX * fMotionSpeed;
				pPlayer[0].aModel[nCnt].pos.z += aKeyDiff[nCnt].fPosZ * fMotionSpeed;
				pPlayer[0].aModel[nCnt].rot.x = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nMAXkey].akey[nCnt].fRotX + aKeyDiff[nCnt].fRotX * fMotionSpeed;
				pPlayer[0].aModel[nCnt].rot.y = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nMAXkey].akey[nCnt].fRotY + aKeyDiff[nCnt].fRotY * fMotionSpeed;
				pPlayer[0].aModel[nCnt].rot.z = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nMAXkey].akey[nCnt].fRotZ + aKeyDiff[nCnt].fRotZ * fMotionSpeed;
			}
		}
		else//上半身！！
		{
			for (int nCnt = 0; nCnt < 6; nCnt++)
			{
				float fMotionSpeed = (float)pPlayer[0].nCntMotion / (float)pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].nFrame;//再生speed
				pPlayer[0].aModel[nCnt].pos.x += aKeyDiff[nCnt].fPosX * fMotionSpeed;
				pPlayer[0].aModel[nCnt].pos.z += aKeyDiff[nCnt].fPosZ * fMotionSpeed;
				pPlayer[0].aModel[nCnt].rot.x = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].akey[nCnt].fRotX + aKeyDiff[nCnt].fRotX * fMotionSpeed;
				pPlayer[0].aModel[nCnt].rot.y = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].akey[nCnt].fRotY + aKeyDiff[nCnt].fRotY * fMotionSpeed;
				pPlayer[0].aModel[nCnt].rot.z = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].akey[nCnt].fRotZ + aKeyDiff[nCnt].fRotZ * fMotionSpeed;
			}
		}

		//update
		if (pPlayer[0].nCntMotion == pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].nFrame)//今のkeyframeを再生の最後frameの時
		{
			if (pPlayer[0].aMotionInfo[PlayerMotion].nNumkey == pPlayer[0].aMotionInfo[PlayerMotion].nMAXkey)
				pPlayer[0].aMotionInfo[PlayerMotion].nNumkey = 1;
			else pPlayer[0].aMotionInfo[PlayerMotion].nNumkey++;

			pPlayer[0].nCntMotion = 0;
		}

	}
	else
	{
		if (pPlayer[0].nCntMotion == 1)
		{
			if (pPlayer[0].aMotionInfo[PlayerMotion].nNumkey == pPlayer[0].aMotionInfo[PlayerMotion].nMAXkey)
			{
				if (pPlayer[0].aMotionInfo[PlayerMotion].bLoop == true)
				{
					for (int nCnt = 0; nCnt < 10; nCnt++)//10パーツを別々計算 
					{
						//差分=次のkeyframe - 今のkeyframe
						aKeyDiff[nCnt].fPosX = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[1].akey[nCnt].fPosX - pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nMAXkey].akey[nCnt].fPosX;
						aKeyDiff[nCnt].fPosY = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[1].akey[nCnt].fPosY - pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nMAXkey].akey[nCnt].fPosY;
						aKeyDiff[nCnt].fPosZ = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[1].akey[nCnt].fPosZ - pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nMAXkey].akey[nCnt].fPosZ;
						aKeyDiff[nCnt].fRotX = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[1].akey[nCnt].fRotX - pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nMAXkey].akey[nCnt].fRotX;
						aKeyDiff[nCnt].fRotY = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[1].akey[nCnt].fRotY - pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nMAXkey].akey[nCnt].fRotY;
						aKeyDiff[nCnt].fRotZ = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[1].akey[nCnt].fRotZ - pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nMAXkey].akey[nCnt].fRotZ;
					}
					int nCnt = 0;
				}
				else
				{
					pPlayer[0].aMotionInfo[PlayerMotion].bLock = false;
					pPlayer[0].aMotionInfo[PlayerMotion].nNumkey = 1;
				}
			}
			else
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
			}
		}
		if (pPlayer[0].aMotionInfo[PlayerMotion].nNumkey == pPlayer[0].aMotionInfo[PlayerMotion].nMAXkey)
		{
			for (int nCnt = 0; nCnt < 10; nCnt++)
			{
				float fMotionSpeed = (float)pPlayer[0].nCntMotion / (float)pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nMAXkey].nFrame;//再生speed
				pPlayer[0].aModel[nCnt].pos.x += aKeyDiff[nCnt].fPosX * fMotionSpeed;
				pPlayer[0].aModel[nCnt].pos.z += aKeyDiff[nCnt].fPosZ * fMotionSpeed;
				pPlayer[0].aModel[nCnt].rot.x = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nMAXkey].akey[nCnt].fRotX + aKeyDiff[nCnt].fRotX * fMotionSpeed;
				pPlayer[0].aModel[nCnt].rot.y = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nMAXkey].akey[nCnt].fRotY + aKeyDiff[nCnt].fRotY * fMotionSpeed;
				pPlayer[0].aModel[nCnt].rot.z = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nMAXkey].akey[nCnt].fRotZ + aKeyDiff[nCnt].fRotZ * fMotionSpeed;
			}
		}
		else
		{
			for (int nCnt = 0; nCnt < 10; nCnt++)
			{
				float fMotionSpeed = (float)pPlayer[0].nCntMotion / (float)pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].nFrame;//再生speed
				pPlayer[0].aModel[nCnt].pos.x += aKeyDiff[nCnt].fPosX * fMotionSpeed;
				pPlayer[0].aModel[nCnt].pos.z += aKeyDiff[nCnt].fPosZ * fMotionSpeed;
				pPlayer[0].aModel[nCnt].rot.x = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].akey[nCnt].fRotX + aKeyDiff[nCnt].fRotX * fMotionSpeed;
				pPlayer[0].aModel[nCnt].rot.y = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].akey[nCnt].fRotY + aKeyDiff[nCnt].fRotY * fMotionSpeed;
				pPlayer[0].aModel[nCnt].rot.z = pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].akey[nCnt].fRotZ + aKeyDiff[nCnt].fRotZ * fMotionSpeed;
			}
		}

		//update
		if (pPlayer[0].nCntMotion == pPlayer[0].aMotionInfo[PlayerMotion].akeyInfo[pPlayer[0].aMotionInfo[PlayerMotion].nNumkey].nFrame)//今のkeyframeを再生の最後frameの時
		{
			if (pPlayer[0].aMotionInfo[PlayerMotion].nNumkey == pPlayer[0].aMotionInfo[PlayerMotion].nMAXkey)
				pPlayer[0].aMotionInfo[PlayerMotion].nNumkey = 1;
			else pPlayer[0].aMotionInfo[PlayerMotion].nNumkey++;

			pPlayer[0].nCntMotion = 0;
		}
	}
}