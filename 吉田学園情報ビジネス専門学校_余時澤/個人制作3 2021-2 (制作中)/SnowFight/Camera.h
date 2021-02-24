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
	D3DXVECTOR3 posV; //éãì_
	D3DXVECTOR3 posR; //íçéãì_
	D3DXVECTOR3 vecV; //â∫Ç©ÇÁè„Ç…éwÇµÇƒÇ¢ÇÈvector
	D3DXMATRIX mtxProjection; //ìäâematrix
	D3DXMATRIX mtxView; //view matrix
	D3DXVECTOR2 fRot; //rotYaw and rotPitch
	float fVR;//version and target ÇÃãóó£
	float fSpeed;
}CAMERA;
HRESULT InitCamera(void);
void UpdateCamera(void);
void SetCamera(void);
CAMERA *GetCamera(void);
#endif