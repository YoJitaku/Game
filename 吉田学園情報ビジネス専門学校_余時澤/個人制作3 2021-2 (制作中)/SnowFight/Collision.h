//=============================================================================
//
// [Collision.h]
// Author : JITAKU YO
//
//=============================================================================
#pragma once
#include "DirectX.h"

typedef struct
{
	D3DXVECTOR3 MinCollisionBox, MaxCollisionBox;//�����蔻��box�p�@AABB
}COLLISION_BOX;

COLLISION_BOX *SetCollisionBox(int nNumVtx, DWORD sizeFvF, BYTE *pVtxBuff);