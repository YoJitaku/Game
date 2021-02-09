//=============================================================================
//
// [Ground.cpp] Main Game`s Terrain (use meshfield to draw)
// Author : JITAKU YO
//
//=============================================================================
#include "Ground.h"

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGround = NULL; //頂点bufferのpointer
LPDIRECT3DTEXTURE9 g_pTextureGround = NULL; //textureのpointer
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffGround = NULL; //index bufferのpointer
D3DXMATRIX g_WorldMtxGround;//単位行列
POLYGON_3D *pGround;

HRESULT InitGround(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_3D *pVtx;
	WORD *pIdx;
	
	pGround = (POLYGON_3D *)malloc(1 * sizeof(POLYGON_3D));
	pGround[0].pos = D3DXVECTOR3(0.f, 0.f, 0.f);
	pGround[0].rot = D3DXVECTOR3(0.f, 0.f, 0.f);
	pGround[0].nor = D3DXVECTOR3(0.f, 1.f, 0.f);

	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/SnowGround.jpg", &g_pTextureGround);

	//pVtx
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_3D) * (int)((ROW_NUM + 1) * (COLUMN_NUM + 1)),//実際に描画する頂点数（全て違う）
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGround,
		NULL)))
		return E_FAIL;

	g_pVtxBuffGround->Lock(0, 0, (void**)&pVtx, 0);
	int nCntNum = 0;
	for (int nCntRow = 0; nCntRow < ROW_NUM + 1; nCntRow++)
	{
		for (int nCntColumn = 0; nCntColumn < COLUMN_NUM + 1; nCntColumn++)
		{
			pVtx[nCntNum].col = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
			//pVtx[nCntNum].nor = pGround[0].nor;
			pVtx[nCntNum].nor = D3DXVECTOR3(0.f, 1.f, 0.f);
			pVtx[nCntNum].tex = D3DXVECTOR2((float)nCntRow, (float)nCntColumn);
			pVtx[nCntNum].pos = D3DXVECTOR3(
				(-MAP_SIZE_X + (nCntColumn) * ((MAP_SIZE_X * 2.f) / (COLUMN_NUM))),//一番左から右に計算する,毎回の増量は　今の列×(全幅/列数)
				0.0f,//地面と平行
				(MAP_SIZE_Y - nCntRow * (MAP_SIZE_Y * 2.f) / (ROW_NUM))//一番上から下に計算する,毎回の増量は　今の行×(全長/行数)
			);
			nCntNum++;
		}
	}
	g_pVtxBuffGround->Unlock();

	//index
	if (FAILED(pDevice->CreateIndexBuffer
	(sizeof(WORD) * (2 * (int)(ROW_NUM * COLUMN_NUM + 2 * ROW_NUM - 1)),//描画必要の最低の頂点数(重複の頂点がある) (頂点数＝2×行数×(列数+1)+2×(行数-1)) -> 2(xy+2x-1)
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16, D3DPOOL_MANAGED,
		&g_pIdxBuffGround,
		NULL)))
		return E_FAIL;

	g_pIdxBuffGround->Lock(0, 0, (void**)&pIdx, 0);
	int nCntIndex = 0;
	int nCntRow = 0;//今の行
	int nCntColumn = 0;//今の列
	//index頂点はpVtx頂点に全部を対応する
	while (nCntIndex < (2 * (int)(ROW_NUM * COLUMN_NUM + 2 * ROW_NUM - 1)))
	{
		//先ず、描画ないのTriangle頂点かどうかを判断する
		if (nCntIndex == ((2 * (COLUMN_NUM + 1) * (nCntRow + 1)) + (2 * nCntRow)))//行末で隠している頂点 (今の行*2×列数+2　+　2×行数)
		{
			int nCnt = (nCntRow + 1) * (int)(COLUMN_NUM + 1) - 1;
			pIdx[nCntIndex] = (nCntRow + 1) * (int)(COLUMN_NUM + 1) - 1;//今の行×列数-1
			nCntRow++;//次の行へいく
			nCntIndex++;

			//行頭で隠している頂点
			int nCnt1 = (nCntRow + 1) * (int)(COLUMN_NUM + 1);
			pIdx[nCntIndex] = (nCntRow + 1) * (int)(COLUMN_NUM + 1);//(今の行+1)×列数
			nCntColumn = 0;//列をreset
		}
		//描画Triangle
		else
		{
			//偶数行 Index = 0 2 4 6 8 ...
			if (nCntIndex % 2 == 0)
			{
				int nCnt = (nCntRow + 1) * (int)(COLUMN_NUM + 1) + nCntColumn;
				pIdx[nCntIndex] = (nCntRow + 1) * (int)(COLUMN_NUM + 1)  + nCntColumn;//(今の行+1)×列数 + 1 + 今の列
			}
			//奇数行 Index = 1 3 5 7 9 ...
			else
			{
				int nCnt = (nCntRow) * (int)(COLUMN_NUM + 1) + nCntColumn;
				pIdx[nCntIndex] = (nCntRow) * (int)(COLUMN_NUM + 1) + nCntColumn; //(今の行)×列数 + 今の列
				nCntColumn++;//次の列へいく
			}
		}
		nCntIndex++;
	}
	g_pIdxBuffGround->Unlock();

	return S_OK;
}
void UninitGround(void)
{
	if (g_pVtxBuffGround != NULL)
		g_pVtxBuffGround = NULL;
	if (g_pTextureGround != NULL)
		g_pTextureGround = NULL;
	if (g_pIdxBuffGround != NULL)
		g_pIdxBuffGround = NULL;
}
void UpdateGround(void)
{

}
void DrawGround(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans; //計算用のmatrix
	D3DXMatrixIdentity(&g_WorldMtxGround); //単位行列
	D3DXMatrixRotationYawPitchRoll(&mtxRot, pGround[0].rot.y, pGround[0].rot.x, pGround[0].rot.z); //the opreation is Roll->Pitch->Yaw 最後output回されたmatrix
	D3DXMatrixMultiply(&g_WorldMtxGround, &g_WorldMtxGround, &mtxRot); //世界matrixの周り　Param1 out put matrix = 世界matrix * 回されたmatrix
	D3DXMatrixTranslation(&mtxTrans, pGround[0].pos.x, pGround[0].pos.y, pGround[0].pos.z); //世界matrix全体　移動したい距離というmatrixの合算
	D3DXMatrixMultiply(&g_WorldMtxGround, &g_WorldMtxGround, &mtxTrans); //世界matrixの移動
	pDevice->SetTransform(D3DTS_WORLD, &g_WorldMtxGround); //set the world into Map
	pDevice->SetStreamSource(0, g_pVtxBuffGround, 0, sizeof(VERTEX_3D));
	pDevice->SetIndices(g_pIdxBuffGround);//
	pDevice->SetFVF(FVF_VERTEX_3D);
	pDevice->SetTexture(0, g_pTextureGround);
	pDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		0,
		(2 * (int)(ROW_NUM * COLUMN_NUM + 2 * ROW_NUM - 1)),//indexの総数
		0,
		(int)((2 * ROW_NUM * COLUMN_NUM) + (4 * (ROW_NUM - 1))));
	//important!! 最後のpramaは三角形数、隠している描画しないのは（線状）計数する必要！(4 * (行数-1))
}