//=============================================================================
//
// [Score.cpp]
// Author : Yo Jitaku
//
//=============================================================================
#include "Score.h"
#include <math.h>

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;//Score���_buff��pointer
LPDIRECT3DTEXTURE9 g_pTextureScore = NULL;//Score���_buff��pointer
D3DXVECTOR3 g_posScore;//Score���W
SCORE g_aScore[MAX_COMPONENT_SCORE];//Score�̈ʐ�

int g_nScoreGet;//���_����

HRESULT InitScore(void)
{
	VERTEX_2D *pVtx;//2D���_���\���̂�pointer�ݒ�
	LPDIRECT3DDEVICE9 pDeviceSc;
	pDeviceSc = GetDevice();//�ݔ�interface

	SCORE *pScore;//Score�\���̂ւ�pointer���
	pScore = &g_aScore[0];
	g_nScoreGet = 0;
	//����������
	for (int nCntNumber = 0; nCntNumber < MAX_COMPONENT_SCORE; nCntNumber++, pScore++)
	{
		pScore->bUse = true;
		pScore->pos.x = 1150 + (float)nCntNumber * 40;
		pScore->pos.y = 75;
		pScore->pos.z = 0;
		pScore->nDisplayNumber = 0;//�\��������number
		pScore->nZeroNumber = MAX_COMPONENT_SCORE - 1 - nCntNumber;//�v�Z����Ƃ��@���̈ʂ̌���0�̌�
		pScore->nMultipleNumber = 0;//�����Ƃ��Ă̐���1->00000
	}

	//�摜data�����
	D3DXCreateTextureFromFile(pDeviceSc, "data/TEXTURE/RankScore.png", &g_pTextureScore);

	//���_buff�����
	if (FAILED(pDeviceSc->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_COMPONENT_SCORE, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffScore, NULL))) return E_FAIL;

	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntNumber = 0; nCntNumber < MAX_COMPONENT_SCORE; nCntNumber++, pVtx += 4)
	{
		pVtx[0].pos = D3DXVECTOR3(g_aScore[nCntNumber].pos.x - SCORE_SIZE_X, g_aScore[nCntNumber].pos.y - SCORE_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aScore[nCntNumber].pos.x + SCORE_SIZE_X, g_aScore[nCntNumber].pos.y - SCORE_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aScore[nCntNumber].pos.x - SCORE_SIZE_X, g_aScore[nCntNumber].pos.y + SCORE_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aScore[nCntNumber].pos.x + SCORE_SIZE_X, g_aScore[nCntNumber].pos.y + SCORE_SIZE_Y, 0.0f);
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[0].tex = D3DXVECTOR2(0.0, 0.0);
		pVtx[1].tex = D3DXVECTOR2(((float)0.1), 0.0);
		pVtx[2].tex = D3DXVECTOR2(0.0, 1.0);
		pVtx[3].tex = D3DXVECTOR2(((float)0.1), 1.0);
	}
	g_pVtxBuffScore->Unlock();
	return S_OK;
}

void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDeviceSc = GetDevice();
	pDeviceSc->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));//���_Data flow�̐ݒ�
	pDeviceSc->SetFVF(FVF_VERTEX_2D);//���_mod�̐ݒ�
	pDeviceSc->SetTexture(0, g_pTextureScore);//�摜�̐ݒ�
	for (int nCntEnemy = 0; nCntEnemy < MAX_COMPONENT_SCORE; nCntEnemy++) pDeviceSc->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnemy * 4, 2);
}

void UninitScore(void)
{
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}
void UpdateScore(void)
{
	LPDIRECT3DDEVICE9 pDeviceSc = GetDevice();
	SCORE *pScore = &g_aScore[0];

	for (int nCntNumber = 0; nCntNumber < MAX_COMPONENT_SCORE; nCntNumber++, pScore++)
	{
		//pow function -> headfile<math.h>
		pScore->nMultipleNumber = (unsigned int)pow(10.0, pScore->nZeroNumber);
		//(1.%��� 2./�ʎ��)
		pScore->nDisplayNumber = g_nScoreGet % (pScore->nMultipleNumber * 10) / pScore->nMultipleNumber;
		SetTextureScore(nCntNumber, pScore->nDisplayNumber);
	}
}

//���R�`�悵����number��texture�ݒ�
void SetTextureScore(int nIdx, int nDisplayNumber)
{
	VERTEX_2D *pVtx;
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);
	pVtx += (nIdx * 4);
	pVtx[0].tex = D3DXVECTOR2((float)(nDisplayNumber * 0.1), 0.0);
	pVtx[1].tex = D3DXVECTOR2((float)(nDisplayNumber * 0.1 + 0.1), 0.0);
	pVtx[2].tex = D3DXVECTOR2((float)(nDisplayNumber * 0.1), 1.0);
	pVtx[3].tex = D3DXVECTOR2((float)(nDisplayNumber * 0.1 + 0.1), 1.0);
	g_pVtxBuffScore->Unlock();
}

//score���Z�Ƃ����֐�
void AddScore(int nValue)
{
	g_nScoreGet += nValue;
}

int GetScore(void)
{
	return g_nScoreGet;
}