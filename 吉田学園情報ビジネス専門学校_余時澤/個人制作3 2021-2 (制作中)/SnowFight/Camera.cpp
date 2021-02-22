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

CAMERA *pCamera;
int nnnnn = 0;
HRESULT InitCameraMenu(void)
{
	pCamera = (CAMERA *)malloc(1 * sizeof(CAMERA));
	pCamera[0].fVR = DISTANCE_V_R;
	pCamera[0].fRot = D3DXVECTOR2(0.0f, 0.0f);
	pCamera[0].posV = D3DXVECTOR3(0.f, 20.0f, -pCamera[0].fVR -850.f); //視点
	pCamera[0].posR = D3DXVECTOR3(0.f, 20.f, -850.f); //注視点
	pCamera[0].vecV = D3DXVECTOR3(0.f, 1.f, 0.f); //法線
	pCamera[0].fSpeed = 1.0f;
	return S_OK;
}

HRESULT InitCamera(void)
{
	pCamera = (CAMERA *)malloc(1 * sizeof(CAMERA));
	pCamera[0].fVR = DISTANCE_V_R;
	pCamera[0].fRot = D3DXVECTOR2(0.0f, 0.0f);
	pCamera[0].posV = D3DXVECTOR3(0.f, 20.0f, -pCamera[0].fVR); //視点
	pCamera[0].posR = D3DXVECTOR3(0.f, 0.f, 0.0f);//注視点
	//pCamera[0].posV = D3DXVECTOR3(0.f, 10.0f, 0);//視点
	//pCamera[0].posR = D3DXVECTOR3(pCamera[0].posV.x, pCamera[0].posV.y, -DISTANCE_V_R); //注視点
	pCamera[0].vecV = D3DXVECTOR3(0.f, 1.f, 0.f); //法線
	pCamera[0].fSpeed = 1.0f;
	return S_OK;
}
void UpdateCamera(void)
{
	D3DXVECTOR2 pMoveMouse = GetMouseVelocity();
	MODE mode = GetMode();
	if (mode == MODE_MENU)
	{
		pCamera[0].posR.z += 0.2f;
		pCamera[0].posV.z += 0.2f;
		if (pCamera[0].posR.z >= 500)
		{
			SetFade(FADE_OUT, MODE_COMPANY);
		}
	}
	else if (mode == MODE_GAME)
	{
		//MouseMove
		pCamera[0].posR.y -= pMoveMouse.y * 0.8f;
		if (pMoveMouse.x > 0)
		{
			pCamera[0].fRot.x -= pMoveMouse.x / D3DX_PI * 0.01f;
			pCamera[0].posR.x = pCamera[0].posV.x + sinf(D3DX_PI + pCamera[0].fRot.x) * pCamera[0].fVR;
			pCamera[0].posR.z = pCamera[0].posV.z - cosf(D3DX_PI + pCamera[0].fRot.x) * pCamera[0].fVR;
		}
		else if (pMoveMouse.x < 0)
		{
			pCamera[0].fRot.x -= pMoveMouse.x / D3DX_PI * 0.01f;
			pCamera[0].posR.x = pCamera[0].posV.x + sinf(D3DX_PI + pCamera[0].fRot.x) * pCamera[0].fVR;
			pCamera[0].posR.z = pCamera[0].posV.z - cosf(D3DX_PI + pCamera[0].fRot.x) * pCamera[0].fVR;
		}

		//camera 自分移動
		if (GetkeyboardPress(DIK_W) == true)
		{
			if (GetkeyboardPress(DIK_D) == true)
			{
				pCamera[0].posV.x += +sinf(D3DX_PI + pCamera[0].fRot.x) * (sinf(D3DX_PI / 4) * pCamera[0].fSpeed);
				pCamera[0].posV.x -= cosf(D3DX_PI + pCamera[0].fRot.x) * (sinf(D3DX_PI / 4) * pCamera[0].fSpeed);
				pCamera[0].posV.z += -cosf(D3DX_PI + pCamera[0].fRot.x) * (sinf(D3DX_PI / 4) * pCamera[0].fSpeed);
				pCamera[0].posV.z -= sinf(D3DX_PI + pCamera[0].fRot.x) * (sinf(D3DX_PI / 4) * pCamera[0].fSpeed);
				pCamera[0].posR.x += +sinf(D3DX_PI + pCamera[0].fRot.x) * (sinf(D3DX_PI / 4) * pCamera[0].fSpeed);
				pCamera[0].posR.x -= cosf(D3DX_PI + pCamera[0].fRot.x) * (sinf(D3DX_PI / 4) * pCamera[0].fSpeed);
				pCamera[0].posR.z += -cosf(D3DX_PI + pCamera[0].fRot.x) * (sinf(D3DX_PI / 4) * pCamera[0].fSpeed);
				pCamera[0].posR.z -= sinf(D3DX_PI + pCamera[0].fRot.x) * (sinf(D3DX_PI / 4) * pCamera[0].fSpeed);
			}
			else if (GetkeyboardPress(DIK_A) == true)
			{
				pCamera[0].posV.x += +sinf(D3DX_PI + pCamera[0].fRot.x) * (sinf(D3DX_PI / 4) * pCamera[0].fSpeed);
				pCamera[0].posV.z += -cosf(D3DX_PI + pCamera[0].fRot.x) * (sinf(D3DX_PI / 4) * pCamera[0].fSpeed);
				pCamera[0].posR.x += +sinf(D3DX_PI + pCamera[0].fRot.x) * (sinf(D3DX_PI / 4) * pCamera[0].fSpeed);
				pCamera[0].posR.z += -cosf(D3DX_PI + pCamera[0].fRot.x) * (sinf(D3DX_PI / 4) * pCamera[0].fSpeed);
				pCamera[0].posV.x += cosf(D3DX_PI + pCamera[0].fRot.x) * (sinf(D3DX_PI / 4) * pCamera[0].fSpeed);
				pCamera[0].posV.z += sinf(D3DX_PI + pCamera[0].fRot.x) * (sinf(D3DX_PI / 4) * pCamera[0].fSpeed);
				pCamera[0].posR.x += cosf(D3DX_PI + pCamera[0].fRot.x) * (sinf(D3DX_PI / 4) * pCamera[0].fSpeed);
				pCamera[0].posR.z += sinf(D3DX_PI + pCamera[0].fRot.x) * (sinf(D3DX_PI / 4) * pCamera[0].fSpeed);
			}
			else
			{
				pCamera[0].posV.x += +sinf(D3DX_PI + pCamera[0].fRot.x) * pCamera[0].fSpeed;
				pCamera[0].posV.z += -cosf(D3DX_PI + pCamera[0].fRot.x) * pCamera[0].fSpeed;
				pCamera[0].posR.x += +sinf(D3DX_PI + pCamera[0].fRot.x) * pCamera[0].fSpeed;
				pCamera[0].posR.z += -cosf(D3DX_PI + pCamera[0].fRot.x) * pCamera[0].fSpeed;
			}
		}
		else if (GetkeyboardPress(DIK_S) == true)
		{
			if (GetkeyboardPress(DIK_A) == true)
			{
				pCamera[0].posV.x -= sinf(D3DX_PI + pCamera[0].fRot.x) * (sinf(D3DX_PI / 4) * pCamera[0].fSpeed);
				pCamera[0].posV.z -= -cosf(D3DX_PI + pCamera[0].fRot.x) * (sinf(D3DX_PI / 4) * pCamera[0].fSpeed);
				pCamera[0].posR.x -= sinf(D3DX_PI + pCamera[0].fRot.x) * (sinf(D3DX_PI / 4) * pCamera[0].fSpeed);
				pCamera[0].posR.z -= -cosf(D3DX_PI + pCamera[0].fRot.x) * (sinf(D3DX_PI / 4) * pCamera[0].fSpeed);
				pCamera[0].posV.x += cosf(D3DX_PI + pCamera[0].fRot.x) * (sinf(D3DX_PI / 4) * pCamera[0].fSpeed);
				pCamera[0].posV.z += sinf(D3DX_PI + pCamera[0].fRot.x) * (sinf(D3DX_PI / 4) * pCamera[0].fSpeed);
				pCamera[0].posR.x += cosf(D3DX_PI + pCamera[0].fRot.x) * (sinf(D3DX_PI / 4) * pCamera[0].fSpeed);
				pCamera[0].posR.z += sinf(D3DX_PI + pCamera[0].fRot.x) * (sinf(D3DX_PI / 4) * pCamera[0].fSpeed);
			}
			else if (GetkeyboardPress(DIK_D) == true)
			{
				pCamera[0].posV.x -= sinf(D3DX_PI + pCamera[0].fRot.x) * (sinf(D3DX_PI / 4) * pCamera[0].fSpeed);
				pCamera[0].posV.z -= -cosf(D3DX_PI + pCamera[0].fRot.x) * (sinf(D3DX_PI / 4) * pCamera[0].fSpeed);
				pCamera[0].posR.x -= sinf(D3DX_PI + pCamera[0].fRot.x) * (sinf(D3DX_PI / 4) * pCamera[0].fSpeed);
				pCamera[0].posR.z -= -cosf(D3DX_PI + pCamera[0].fRot.x) * (sinf(D3DX_PI / 4) * pCamera[0].fSpeed);
				pCamera[0].posV.x -= cosf(D3DX_PI + pCamera[0].fRot.x) * (sinf(D3DX_PI / 4) * pCamera[0].fSpeed);
				pCamera[0].posV.z -= sinf(D3DX_PI + pCamera[0].fRot.x) * (sinf(D3DX_PI / 4) * pCamera[0].fSpeed);
				pCamera[0].posR.x -= cosf(D3DX_PI + pCamera[0].fRot.x) * (sinf(D3DX_PI / 4) * pCamera[0].fSpeed);
				pCamera[0].posR.z -= sinf(D3DX_PI + pCamera[0].fRot.x) * (sinf(D3DX_PI / 4) * pCamera[0].fSpeed);
			}
			else
			{
				pCamera[0].posV.x -= sinf(D3DX_PI + pCamera[0].fRot.x) * pCamera[0].fSpeed;
				pCamera[0].posV.z -= -cosf(D3DX_PI + pCamera[0].fRot.x) * pCamera[0].fSpeed;
				pCamera[0].posR.x -= sinf(D3DX_PI + pCamera[0].fRot.x) * pCamera[0].fSpeed;
				pCamera[0].posR.z -= -cosf(D3DX_PI + pCamera[0].fRot.x) * pCamera[0].fSpeed;
			}
		}
		else if (GetkeyboardPress(DIK_A) == true)
		{
			pCamera[0].posV.x += cosf(D3DX_PI + pCamera[0].fRot.x) * pCamera[0].fSpeed;
			pCamera[0].posV.z += sinf(D3DX_PI + pCamera[0].fRot.x) * pCamera[0].fSpeed;
			pCamera[0].posR.x += cosf(D3DX_PI + pCamera[0].fRot.x) * pCamera[0].fSpeed;
			pCamera[0].posR.z += sinf(D3DX_PI + pCamera[0].fRot.x) * pCamera[0].fSpeed;
		}
		else if (GetkeyboardPress(DIK_D) == true)
		{
			pCamera[0].posV.x -= cosf(D3DX_PI + pCamera[0].fRot.x) * pCamera[0].fSpeed;
			pCamera[0].posV.z -= sinf(D3DX_PI + pCamera[0].fRot.x) * pCamera[0].fSpeed;
			pCamera[0].posR.x -= cosf(D3DX_PI + pCamera[0].fRot.x) * pCamera[0].fSpeed;
			pCamera[0].posR.z -= sinf(D3DX_PI + pCamera[0].fRot.x) * pCamera[0].fSpeed;
		}

		//camera JUMP
		//snowball shoot
		//if (GetkeyboardRelease(DIK_SPACE) == true)
		//{
		//	SetSnowBall(pCamera[0].posR, (pCamera->posR - pCamera->posV) / SPEED_RADIO);
		//}


		//cameraとmodelの当たり判定
		MODEL *pModel = GetWorldModel();
		bool bCol = false;
		for (int nCntMod = 0; nCntMod < WORLDMODEL_NUM; nCntMod++, pModel++)
		{
			bCol = CollisionDetection(pCamera[0].posV, pModel->MinColBox, pModel->MaxColBox);
			if (bCol == true)
				nnnnn = 1;
			else nnnnn = 0;
		}
	}	
}
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMatrixIdentity(&pCamera[0].mtxProjection); //cameraの単位行列
	//今のmatrixはprojection matrixにする. Param2　y軸上の視角size -0.1f->1.0f, Param3 高さ/横さ, 
	D3DXMatrixPerspectiveFovLH(&pCamera[0].mtxProjection, D3DXToRadian(45.0f), 1920.0f / 1080.0f, 10.0f, 1000000000000.0f);
	pDevice->SetTransform(D3DTS_PROJECTION, &pCamera[0].mtxProjection);
	D3DXMatrixIdentity(&pCamera[0].mtxView);
	D3DXMatrixLookAtLH(&pCamera[0].mtxView, &pCamera[0].posV, &pCamera[0].posR, &pCamera[0].vecV);
	pDevice->SetTransform(D3DTS_VIEW, &pCamera[0].mtxView);
}

CAMERA *GetCamera(void)
{
	return &pCamera[0];
}

int Getnnn(void)
{
	return nnnnn;
}