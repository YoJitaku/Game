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
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;//頂点情報を取る
		pVtxBuff += sizeFvF;//次に行く

		if (pCol_Box.MaxCollisionBox == pCol_Box.MinCollisionBox)//初めの頂点
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

D3DXVECTOR3 g_Pos[8];//当たり判定box八つの頂点
D3DXVECTOR3 g_aColVec[8];//当たり判定box八つの辺のvector定義
D3DXVECTOR3 g_ColVec2;//外積計算し必要Vector

bool CollisionDetection(D3DXVECTOR3 posvtx, D3DXVECTOR3 ColBoxMin, D3DXVECTOR3 ColBoxMax)
{

	//x,z平面頂点
	g_Pos[0] = D3DXVECTOR3(ColBoxMin.x, 0.0f, ColBoxMax.z);
	g_Pos[1] = D3DXVECTOR3(ColBoxMax.x, 0.0f, ColBoxMax.z);
	g_Pos[2] = D3DXVECTOR3(ColBoxMax.x, 0.0f, ColBoxMin.z);
	g_Pos[3] = D3DXVECTOR3(ColBoxMin.x, 0.0f, ColBoxMin.z);

	//x,y平面頂点
	g_Pos[4] = D3DXVECTOR3(ColBoxMin.x, ColBoxMax.y, 0.0f);
	g_Pos[5] = D3DXVECTOR3(ColBoxMax.x, ColBoxMax.y, 0.0f);
	g_Pos[6] = D3DXVECTOR3(ColBoxMax.x, ColBoxMin.y, 0.0f);
	g_Pos[7] = D3DXVECTOR3(ColBoxMin.x, ColBoxMin.y, 0.0f);

	//x,z平面vector
	g_aColVec[0] = g_Pos[1] - g_Pos[0];
	g_aColVec[1] = g_Pos[2] - g_Pos[1];
	g_aColVec[2] = g_Pos[3] - g_Pos[2];
	g_aColVec[3] = g_Pos[0] - g_Pos[3];

	//x,y平面vector
	g_aColVec[4] = g_Pos[5] - g_Pos[4];
	g_aColVec[5] = g_Pos[6] - g_Pos[5];
	g_aColVec[6] = g_Pos[7] - g_Pos[6];
	g_aColVec[7] = g_Pos[4] - g_Pos[7];

	//x,z平面 当たり判定
	int nCntNum = 0;
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		g_ColVec2 = posvtx - g_Pos[nCnt];
		if (g_aColVec[nCnt].z * g_ColVec2.x - g_aColVec[nCnt].x * g_ColVec2.z > 0)
			nCntNum++;
	}

	//x,y平面 当たり判定
	for (int nCnt = 4; nCnt < 8; nCnt++)
	{
		g_ColVec2 = posvtx - g_Pos[nCnt];
		if (g_aColVec[nCnt].y * g_ColVec2.x - g_aColVec[nCnt].x * g_ColVec2.y > 0)
			nCntNum++;
	}

	//判定頂点はxz面とxy面の中にいる時
	if (nCntNum == 8) 
		return true;
	else return false;

}