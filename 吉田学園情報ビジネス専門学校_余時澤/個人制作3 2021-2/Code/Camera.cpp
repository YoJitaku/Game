//=============================================================================
//
// [Camera.cpp]
// Author : JITAKU YO
//
//=============================================================================
#include "Camera.h"
#include "Dinput8.h"
#include "SnowBall.h"
#include "Collision.h"
#include "WorldModel.h"
#include "Fade.h"
#include "Player.h"

CAMERA *pCamera;
D3DXVECTOR3 g_PrePosVer;
D3DXVECTOR3 g_MovePosVer;

void InitGameCamera(void)
{
	PLAYER *player = GetPlayer();

	pCamera[0].fVR = DISTANCE_V_R;
	pCamera[0].fRot = D3DXVECTOR2(0.0f, D3DX_PI);
	pCamera[0].posV.x = player->pos.x + sinf(D3DX_PI + pCamera[0].fRot.y) * pCamera[0].fVR;
	pCamera[0].posV.z = player->pos.z - cosf(D3DX_PI + pCamera[0].fRot.y) * pCamera[0].fVR;
	pCamera[0].posV.y = 80.f;
	D3DXVECTOR3 SightVector = player->pos - pCamera[0].posV;
	g_MovePosVer = pCamera[0].posV + 2.f * SightVector;
	pCamera[0].posR.x = g_MovePosVer.x; //注視点
	pCamera[0].posR.z = g_MovePosVer.z;
	pCamera[0].posR.y = 0.0f;

	pCamera[0].vecV = D3DXVECTOR3(0.f, 1.f, 0.f); //法線
	pCamera[0].fSpeed = 1.0f;
}

HRESULT InitCamera(void)
{
	pCamera = (CAMERA *)malloc(3 * sizeof(CAMERA));

	//pCamera[0].fVR = DISTANCE_V_R;
	//pCamera[0].fRot = D3DXVECTOR2(0.0f, D3DX_PI);
	//pCamera[0].posV = D3DXVECTOR3(0.f, 50.0f, -pCamera[0].fVR); //視点
	//pCamera[0].posR = D3DXVECTOR3(0.f, 0.f, -0.f); //注視点
	//g_PrePosVer = pCamera[0].posR;
	//g_MovePosVer = D3DXVECTOR3(0.f, 0.f, 0.f);
	//pCamera[0].vecV = D3DXVECTOR3(0.f, 1.f, 0.f); //法線
	//pCamera[0].fSpeed = 1.0f;

	//rank
	pCamera[1].fVR = DISTANCE_V_R;
	pCamera[1].fRot = D3DXVECTOR2(0.0f, 0.0f);
	pCamera[1].posV = D3DXVECTOR3(2000.f, 300.0f, -2000.f); //視点
	pCamera[1].posR = D3DXVECTOR3(0.f, 0.f, -0.f); //注視点
	pCamera[1].vecV = D3DXVECTOR3(0.f, 1.f, 0.f); //法線
	pCamera[1].fSpeed = 1.0f;

	//menu
	pCamera[2].fVR = DISTANCE_V_R;
	pCamera[2].fRot = D3DXVECTOR2(0.0f, 0.0f);
	pCamera[2].posV = D3DXVECTOR3(0.f, 70.0f, -pCamera[2].fVR - 900.f); //視点
	pCamera[2].posR = D3DXVECTOR3(0.f, 20.f, -850.f); //注視点
	pCamera[2].vecV = D3DXVECTOR3(0.f, 1.f, 0.f); //法線
	pCamera[2].fSpeed = 1.0f;

	return S_OK;
}

void UpdateCamera(void)
{
	D3DXVECTOR2 pMoveMouse = GetMouseVelocity();
	MODE mode = GetMode();

	if (mode == MODE_MENU)
	{
		pCamera[2].posR.z += 0.2f;
		pCamera[2].posV.z += 0.2f;
		if (pCamera[2].posR.z >= 500)
		{
			SetFade(FADE_OUT, MODE_COMPANY);
		}
	}
	else if (mode == MODE_GAME)
	{
		PLAYER *player = GetPlayer();
		D3DXVECTOR3 SightVector = player->pos - pCamera[0].posV;
		g_MovePosVer = pCamera[0].posV + 2.f * SightVector - g_PrePosVer;
		if (pMoveMouse.x > MOUSE_LOSS)
		{
			pCamera[0].fRot.y -= pMoveMouse.x * CAMERA_SPIN_SPEED;
			if (pCamera[0].fRot.y < -D3DX_PI)
			{
				pCamera[0].fRot.y += 2.0f * D3DX_PI;
			}

			pCamera[0].posV.x = player->pos.x + sinf(D3DX_PI + pCamera[0].fRot.y) * pCamera[0].fVR;
			pCamera[0].posV.z = player->pos.z - cosf(D3DX_PI + pCamera[0].fRot.y) * pCamera[0].fVR;
		}
		else if (pMoveMouse.x < -MOUSE_LOSS)
		{
			pCamera[0].fRot.y -= pMoveMouse.x * CAMERA_SPIN_SPEED;
			if (pCamera[0].fRot.y > D3DX_PI)
			{
				pCamera[0].fRot.y -= 2.0f * D3DX_PI;
			}
			pCamera[0].posV.x = player->pos.x + sinf(D3DX_PI + pCamera[0].fRot.y) * pCamera[0].fVR;
			pCamera[0].posV.z = player->pos.z - cosf(D3DX_PI + pCamera[0].fRot.y) * pCamera[0].fVR;
		}

		if (pMoveMouse.x < -MOUSE_LOSS || pMoveMouse.x > MOUSE_LOSS)
		{
			pCamera[0].posR.x = g_PrePosVer.x + g_MovePosVer.x;
			pCamera[0].posR.z = g_PrePosVer.z + g_MovePosVer.z;
		}
		if (pMoveMouse.y < -MOUSE_LOSS || pMoveMouse.y > MOUSE_LOSS)
		{
			pCamera[0].posR.y -= pMoveMouse.y * 0.8f;
			pCamera[0].posV.y += pMoveMouse.y * 0.4f;
		}
	}
	g_PrePosVer = pCamera[0].posR;

}
void SetCamera(void)
{
	MODE mode = GetMode();
	int nCntMode = 2;
	if (mode == MODE_MENU)
	{
		nCntMode = 2;
	}
	else if (mode == MODE_GAME)
	{
		nCntMode = 0;
	}
	else if (mode == MODE_RANKING)
	{
		nCntMode = 1;
	}

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMatrixIdentity(&pCamera[nCntMode].mtxProjection); //cameraの単位行列
	//今のmatrixはprojection matrixにする. Param2　y軸上の視角size -0.1f->1.0f, Param3 高さ/横さ, 
	D3DXMatrixPerspectiveFovLH(&pCamera[nCntMode].mtxProjection, D3DXToRadian(45.0f), 1920.0f / 1080.0f, 10.0f, 1000000000000.0f);
	pDevice->SetTransform(D3DTS_PROJECTION, &pCamera[nCntMode].mtxProjection);
	D3DXMatrixIdentity(&pCamera[nCntMode].mtxView);
	D3DXMatrixLookAtLH(&pCamera[nCntMode].mtxView, &pCamera[nCntMode].posV, &pCamera[nCntMode].posR, &pCamera[nCntMode].vecV);
	pDevice->SetTransform(D3DTS_VIEW, &pCamera[nCntMode].mtxView);
}

CAMERA *GetCamera(void)
{
	return &pCamera[0];
}
