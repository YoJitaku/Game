//=============================================================================
//
// [WorldBillboard.cpp]
// Author : JITAKU YO
//
//=============================================================================

#if 1
#define _CRT_SECURE_NO_WARNINGS
#include "WorldBillboard.h"

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWorldBillboard = NULL; //���_buffer��pointer
LPDIRECT3DTEXTURE9 g_pTextureWorldBillboard[WORLDBILLBOARD_TEX_NUM] = {}; //texture��pointer
BILLBOARD *pWorldBillboard;

void ReadFile(void)
{
	FILE *pFile;
	pFile = fopen("WorldBillboard.txt", "r");
	for (int nCnt = 0; nCnt < WORLDBILLBOARD_NUM; nCnt++)
	{
		fscanf(pFile, "%d %d", 
			&pWorldBillboard[nCnt].nID, 
			&pWorldBillboard[nCnt].nTextureID);
		fscanf(pFile, "%f %f %f",
			&pWorldBillboard[nCnt].pos.x,
			&pWorldBillboard[nCnt].pos.y,
			&pWorldBillboard[nCnt].pos.z);

		pWorldBillboard[nCnt].size = D3DXVECTOR2(20, 40);
		pWorldBillboard[nCnt].pos.y += pWorldBillboard[nCnt].size.y;
		pWorldBillboard[nCnt].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pWorldBillboard[nCnt].bUse = true;
	}
		
#if 0
	pFile = fopen("WorldBillboard.csv", "r");

	char aline[1000];//�s�̏��
	int nCntColumn = 0;//��Count
	int nCntRow = 0;//�sCount

	while (fgets(aline, 1000, pFile) != NULL)//�Ō�܂�
	{
		char *pToken = strtok(aline, ",");//�Ǔ_�ŕ�����Ă���
		while (pToken != NULL)//�Ō�܂�
		{
			int nNum = atoi(pToken);//data��ޕϊ�
			g_aMapData[nCntRow][nCntColumn] = nNum;//�ۑ�
			pToken = strtok(NULL, ",");//reset
			nCntColumn++;
		}
		nCntRow++;
	}
#endif // 0
	fclose(pFile);
}

void SetWorldBillboard(void)
{
#if 0
	//srand((int)time(0));
	int nCntColumn = 0;//��Count
	int nCntRow = 0;//�sCount
	int nCntNum = 0;//����Count
	for (int nCntR = 0; nCntR < 100; nCntR++)
	{
		for (int nCntC = 0; nCntC < 100; nCntC++)
		{
			switch (g_aMapData[nCntRow][nCntColumn])
			{
			case 1://tree1
				pWorldBillboard[nCntNum].bUse = true;
				pWorldBillboard[nCntNum].bAnime = false;
				pWorldBillboard[nCntNum].nTextureID = 1;
				pWorldBillboard[nCntNum].size = D3DXVECTOR2();
				pWorldBillboard[nCntNum].nor = D3DXVECTOR3();
				pWorldBillboard[nCntNum].move = D3DXVECTOR3(0.f, 0.f, 0.f);
				break;
			case 2://tree2
				pWorldBillboard[nCntNum].bUse = true;
				pWorldBillboard[nCntNum].bAnime = false;
				pWorldBillboard[nCntNum].nTextureID = 2;
				pWorldBillboard[nCntNum].size = D3DXVECTOR2();
				pWorldBillboard[nCntNum].nor = D3DXVECTOR3();
				pWorldBillboard[nCntNum].move = D3DXVECTOR3(0.f, 0.f, 0.f);
				break;
			case 3://tree3
				pWorldBillboard[nCntNum].bUse = true;
				pWorldBillboard[nCntNum].bAnime = false;
				pWorldBillboard[nCntNum].nTextureID = 3;
				pWorldBillboard[nCntNum].size = D3DXVECTOR2();
				pWorldBillboard[nCntNum].nor = D3DXVECTOR3();
				pWorldBillboard[nCntNum].move = D3DXVECTOR3(0.f, 0.f, 0.f);
				break;
			case 4://grass1
				pWorldBillboard[nCntNum].bUse = true;
				pWorldBillboard[nCntNum].bAnime = false;
				pWorldBillboard[nCntNum].nTextureID = 4;
				pWorldBillboard[nCntNum].size = D3DXVECTOR2();
				pWorldBillboard[nCntNum].nor = D3DXVECTOR3();
				pWorldBillboard[nCntNum].move = D3DXVECTOR3(0.f, 0.f, 0.f);
				break;
			case 5://grass2
				pWorldBillboard[nCntNum].bUse = true;
				pWorldBillboard[nCntNum].bAnime = false;
				pWorldBillboard[nCntNum].nTextureID = 5;
				pWorldBillboard[nCntNum].size = D3DXVECTOR2();
				pWorldBillboard[nCntNum].nor = D3DXVECTOR3();
				pWorldBillboard[nCntNum].move = D3DXVECTOR3(0.f, 0.f, 0.f);
				break;
			default:
				break;
			}
		}
	}

#endif // 0

}

HRESULT InitWorldBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_3D *pVtx;
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Billboard/tree1.png", &g_pTextureWorldBillboard[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Billboard/tree2.png", &g_pTextureWorldBillboard[1]);
	//D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/tree3.png", &g_pTextureWorldBillboard[2]);
	//D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/grass1.png", &g_pTextureWorldBillboard[3]);
	//D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/grass2.png", &g_pTextureWorldBillboard[4]);

	pWorldBillboard = (BILLBOARD *)malloc(WORLDBILLBOARD_NUM * sizeof(BILLBOARD)); //��������`
	ReadFile();

	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_3D) * WORLDBILLBOARD_NUM * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWorldBillboard,
		NULL)))
		return E_FAIL;
	g_pVtxBuffWorldBillboard->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < WORLDBILLBOARD_NUM; nCnt++, pVtx += 4)
	{
		pVtx[0].pos = D3DXVECTOR3(-pWorldBillboard[nCnt].size.x, pWorldBillboard[nCnt].size.y, 0.f);
		pVtx[1].pos = D3DXVECTOR3(pWorldBillboard[nCnt].size.x, pWorldBillboard[nCnt].size.y, 0.f);
		pVtx[2].pos = D3DXVECTOR3(-pWorldBillboard[nCnt].size.x, -pWorldBillboard[nCnt].size.y, 0.f);
		pVtx[3].pos = D3DXVECTOR3(pWorldBillboard[nCnt].size.x, -pWorldBillboard[nCnt].size.y, 0.f);
		pVtx[0].nor = pWorldBillboard[nCnt].nor;
		pVtx[1].nor = pWorldBillboard[nCnt].nor;
		pVtx[2].nor = pWorldBillboard[nCnt].nor;
		pVtx[3].nor = pWorldBillboard[nCnt].nor;
		pVtx[0].col = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
		pVtx[1].col = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
		pVtx[2].col = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
		pVtx[3].col = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
		pVtx[0].tex = D3DXVECTOR2(0.f, 0.f);
		pVtx[1].tex = D3DXVECTOR2(1.f, 0.f);
		pVtx[2].tex = D3DXVECTOR2(0.f, 1.f);
		pVtx[3].tex = D3DXVECTOR2(1.f, 1.f);
	}
	g_pVtxBuffWorldBillboard->Unlock();
	return S_OK;
}

void UninitWorldBillboard(void)
{
	if (g_pVtxBuffWorldBillboard != NULL)
		g_pVtxBuffWorldBillboard = NULL;
	for (int nCnt = 0; nCnt < WORLDBILLBOARD_TEX_NUM; nCnt++)
	{
		if (g_pTextureWorldBillboard[nCnt] != NULL)
			g_pTextureWorldBillboard[nCnt] = NULL;
	}
	free(pWorldBillboard);
}

void UpdateWorldBillboard(void)
{

}

void DrawWorldBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxTrans, WorldBillboard; //�v�Z�p��matrix
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE); //close the lighting and diffuse effect
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER); //alpha test function
	pDevice->SetRenderState(D3DRS_ALPHAREF, 100); //alpha number
	for (int nCnt = 0; nCnt < WORLDBILLBOARD_NUM; nCnt++)
	{
		if (pWorldBillboard[nCnt].bUse == true)
		{
			D3DXMatrixIdentity(&WorldBillboard); //�P�ʍs��
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);
			//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
			D3DXMatrixInverse(&WorldBillboard, NULL, &mtxView);
			//���s�ړ��̕����͖�������
			WorldBillboard._41 = 0.0f;
			WorldBillboard._42 = 0.0f;
			WorldBillboard._43 = 0.0f;
			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, pWorldBillboard[nCnt].pos.x, pWorldBillboard[nCnt].pos.y, pWorldBillboard[nCnt].pos.z); //���Ematrix�S�́@�ړ������������Ƃ���matrix�̍��Z
			D3DXMatrixMultiply(&WorldBillboard, &WorldBillboard, &mtxTrans); //���Ematrix�̈ړ�
			
			pDevice->SetTransform(D3DTS_WORLD, &WorldBillboard); //set the world into Map
			pDevice->SetStreamSource(0, g_pVtxBuffWorldBillboard, 0, sizeof(VERTEX_3D));
			pDevice->SetFVF(FVF_VERTEX_3D);
			pDevice->SetTexture(0, g_pTextureWorldBillboard[pWorldBillboard[nCnt].nTextureID]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}
	//reset
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	//���e�X�g�𖳌�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);
}

#endif // 1