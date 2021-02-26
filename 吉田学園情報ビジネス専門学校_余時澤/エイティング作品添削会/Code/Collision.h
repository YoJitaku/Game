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
bool CollisionDetection(D3DXVECTOR3 pos, D3DXVECTOR3 ColBoxMin, D3DXVECTOR3 ColBoxMax);