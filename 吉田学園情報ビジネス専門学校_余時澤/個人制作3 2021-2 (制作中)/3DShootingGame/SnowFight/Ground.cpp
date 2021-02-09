//=============================================================================
//
// [Ground.cpp] Main Game`s Terrain (use meshfield to draw)
// Author : JITAKU YO
//
//=============================================================================
#include "Ground.h"

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGround = NULL; //���_buffer��pointer
LPDIRECT3DTEXTURE9 g_pTextureGround = NULL; //texture��pointer
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffGround = NULL; //index buffer��pointer
D3DXMATRIX g_WorldMtxGround;//�P�ʍs��
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
	(sizeof(VERTEX_3D) * (int)((ROW_NUM + 1) * (COLUMN_NUM + 1)),//���ۂɕ`�悷�钸�_���i�S�ĈႤ�j
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
				(-MAP_SIZE_X + (nCntColumn) * ((MAP_SIZE_X * 2.f) / (COLUMN_NUM))),//��ԍ�����E�Ɍv�Z����,����̑��ʂ́@���̗�~(�S��/��)
				0.0f,//�n�ʂƕ��s
				(MAP_SIZE_Y - nCntRow * (MAP_SIZE_Y * 2.f) / (ROW_NUM))//��ԏォ�牺�Ɍv�Z����,����̑��ʂ́@���̍s�~(�S��/�s��)
			);
			nCntNum++;
		}
	}
	g_pVtxBuffGround->Unlock();

	//index
	if (FAILED(pDevice->CreateIndexBuffer
	(sizeof(WORD) * (2 * (int)(ROW_NUM * COLUMN_NUM + 2 * ROW_NUM - 1)),//�`��K�v�̍Œ�̒��_��(�d���̒��_������) (���_����2�~�s���~(��+1)+2�~(�s��-1)) -> 2(xy+2x-1)
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16, D3DPOOL_MANAGED,
		&g_pIdxBuffGround,
		NULL)))
		return E_FAIL;

	g_pIdxBuffGround->Lock(0, 0, (void**)&pIdx, 0);
	int nCntIndex = 0;
	int nCntRow = 0;//���̍s
	int nCntColumn = 0;//���̗�
	//index���_��pVtx���_�ɑS����Ή�����
	while (nCntIndex < (2 * (int)(ROW_NUM * COLUMN_NUM + 2 * ROW_NUM - 1)))
	{
		//�悸�A�`��Ȃ���Triangle���_���ǂ����𔻒f����
		if (nCntIndex == ((2 * (COLUMN_NUM + 1) * (nCntRow + 1)) + (2 * nCntRow)))//�s���ŉB���Ă��钸�_ (���̍s*2�~��+2�@+�@2�~�s��)
		{
			int nCnt = (nCntRow + 1) * (int)(COLUMN_NUM + 1) - 1;
			pIdx[nCntIndex] = (nCntRow + 1) * (int)(COLUMN_NUM + 1) - 1;//���̍s�~��-1
			nCntRow++;//���̍s�ւ���
			nCntIndex++;

			//�s���ŉB���Ă��钸�_
			int nCnt1 = (nCntRow + 1) * (int)(COLUMN_NUM + 1);
			pIdx[nCntIndex] = (nCntRow + 1) * (int)(COLUMN_NUM + 1);//(���̍s+1)�~��
			nCntColumn = 0;//���reset
		}
		//�`��Triangle
		else
		{
			//�����s Index = 0 2 4 6 8 ...
			if (nCntIndex % 2 == 0)
			{
				int nCnt = (nCntRow + 1) * (int)(COLUMN_NUM + 1) + nCntColumn;
				pIdx[nCntIndex] = (nCntRow + 1) * (int)(COLUMN_NUM + 1)  + nCntColumn;//(���̍s+1)�~�� + 1 + ���̗�
			}
			//��s Index = 1 3 5 7 9 ...
			else
			{
				int nCnt = (nCntRow) * (int)(COLUMN_NUM + 1) + nCntColumn;
				pIdx[nCntIndex] = (nCntRow) * (int)(COLUMN_NUM + 1) + nCntColumn; //(���̍s)�~�� + ���̗�
				nCntColumn++;//���̗�ւ���
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
	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p��matrix
	D3DXMatrixIdentity(&g_WorldMtxGround); //�P�ʍs��
	D3DXMatrixRotationYawPitchRoll(&mtxRot, pGround[0].rot.y, pGround[0].rot.x, pGround[0].rot.z); //the opreation is Roll->Pitch->Yaw �Ō�output�񂳂ꂽmatrix
	D3DXMatrixMultiply(&g_WorldMtxGround, &g_WorldMtxGround, &mtxRot); //���Ematrix�̎���@Param1 out put matrix = ���Ematrix * �񂳂ꂽmatrix
	D3DXMatrixTranslation(&mtxTrans, pGround[0].pos.x, pGround[0].pos.y, pGround[0].pos.z); //���Ematrix�S�́@�ړ������������Ƃ���matrix�̍��Z
	D3DXMatrixMultiply(&g_WorldMtxGround, &g_WorldMtxGround, &mtxTrans); //���Ematrix�̈ړ�
	pDevice->SetTransform(D3DTS_WORLD, &g_WorldMtxGround); //set the world into Map
	pDevice->SetStreamSource(0, g_pVtxBuffGround, 0, sizeof(VERTEX_3D));
	pDevice->SetIndices(g_pIdxBuffGround);//
	pDevice->SetFVF(FVF_VERTEX_3D);
	pDevice->SetTexture(0, g_pTextureGround);
	pDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		0,
		(2 * (int)(ROW_NUM * COLUMN_NUM + 2 * ROW_NUM - 1)),//index�̑���
		0,
		(int)((2 * ROW_NUM * COLUMN_NUM) + (4 * (ROW_NUM - 1))));
	//important!! �Ō��prama�͎O�p�`���A�B���Ă���`�悵�Ȃ��̂́i����j�v������K�v�I(4 * (�s��-1))
}