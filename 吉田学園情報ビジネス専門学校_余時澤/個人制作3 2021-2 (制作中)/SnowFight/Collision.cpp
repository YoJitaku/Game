//=============================================================================
//
// [Collision.cpp]
// Author : JITAKU YO
//
//=============================================================================
#include "Collision.h"

COLLISION_BOX pCol_Box;
COLLISION_BOX *SetCollisionBox(int nNumVtx, DWORD sizeFvF, BYTE *pVtxBuff)
{
	pCol_Box.MinCollisionBox = D3DXVECTOR3(0.f, 0.f, 0.f);
	pCol_Box.MaxCollisionBox = D3DXVECTOR3(0.f, 0.f, 0.f);
	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;//’¸“_î•ñ‚ðŽæ‚é
		pVtxBuff += sizeFvF;//ŽŸ‚És‚­

		if (pCol_Box.MaxCollisionBox == pCol_Box.MinCollisionBox)//‰‚ß‚Ì’¸“_
			pCol_Box.MaxCollisionBox = vtx;
		else
		{
			if (vtx.x >pCol_Box.MaxCollisionBox.x) pCol_Box.MaxCollisionBox.x = vtx.x;
			else if (vtx.x < pCol_Box.MinCollisionBox.x) pCol_Box.MinCollisionBox.x = vtx.x;
			if (vtx.y > pCol_Box.MaxCollisionBox.y) pCol_Box.MaxCollisionBox.y = vtx.y;
			else if (vtx.x < pCol_Box.MinCollisionBox.x) pCol_Box.MinCollisionBox.y = vtx.y;
			if (vtx.z > pCol_Box.MaxCollisionBox.z) pCol_Box.MaxCollisionBox.z = vtx.z;
			else if (vtx.x < pCol_Box.MinCollisionBox.x) pCol_Box.MinCollisionBox.z = vtx.z;
		}
	}

	return &pCol_Box;
}