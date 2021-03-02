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
	D3DXVECTOR3 MinCollisionBox, MaxCollisionBox;//Ç†ÇΩÇËîªíËboxópÅ@AABB
}COLLISION_BOX;

bool CollisionDetection(D3DXVECTOR3 pos, D3DXVECTOR3 ColBoxMin, D3DXVECTOR3 ColBoxMax);