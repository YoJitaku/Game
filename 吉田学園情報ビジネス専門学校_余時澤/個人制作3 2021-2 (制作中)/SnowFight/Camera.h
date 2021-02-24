//=============================================================================
//
// [Camera.h]
// Author : JITAKU YO
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "DirectX.h"

#define DISTANCE_V_R 150.f
#define CAMERA_SPIN_SPEED (D3DX_PI / 2000.f)
typedef struct
{
	D3DXVECTOR3 posV; //���_
	D3DXVECTOR3 posR; //�����_
	D3DXVECTOR3 vecV; //�������Ɏw���Ă���vector
	D3DXMATRIX mtxProjection; //���ematrix
	D3DXMATRIX mtxView; //view matrix
	D3DXVECTOR2 fRot; //rotYaw and rotPitch
	float fVR;//version and target �̋���
	float fSpeed;
}CAMERA;
HRESULT InitCamera(void);
void UpdateCamera(void);
void SetCamera(void);
CAMERA *GetCamera(void);
#endif