//=============================================================================
//
// [Fade.cpp]
// Author : Yo Jitaku
//
//=============================================================================
#include "Fade.h"

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL;//���_buff��pointer
float g_fFadeCnt = (float)0.03;//fade speed �� control
FADE g_fade;//fade mode���L�^����
MODE g_modeNext;//����mode���L�^����
D3DXCOLOR g_colorFade;//fade effect�̓����x

HRESULT InitFade(MODE modeNext)
{
	LPDIRECT3DDEVICE9 pDeviceFd = GetDevice();
	VERTEX_2D *pVtx;

	//������
	g_fade = FADE_IN;
	g_modeNext = modeNext;
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	//create vertex buffer
	if (FAILED(pDeviceFd->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffFade, NULL))) return E_FAIL;

	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);
	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(WIDTH_SCREEN, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0, HEIGHT_SCREEN, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(WIDTH_SCREEN, HEIGHT_SCREEN, 0.0f);
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	pVtx[0].col = g_colorFade;
	pVtx[1].col = g_colorFade;
	pVtx[2].col = g_colorFade;
	pVtx[3].col = g_colorFade;
	pVtx[0].tex = D3DXVECTOR2(0.0, 0.0);
	pVtx[1].tex = D3DXVECTOR2(1.0, 0.0);
	pVtx[2].tex = D3DXVECTOR2(0.0, 1.0);
	pVtx[3].tex = D3DXVECTOR2(1.0, 1.0);
	g_pVtxBuffFade->Unlock();
	return S_OK;
}

void UninitFade(void)
{
	if (g_pVtxBuffFade != NULL)
	{
		g_pVtxBuffFade->Release();
		g_pVtxBuffFade = NULL;
	}
}

void UpdateFade(void)
{
	LPDIRECT3DDEVICE9 pDeviceFd = GetDevice();
	VERTEX_2D *pVtx;

	if (g_fade == FADE_IN)//fade in ����
	{
		if (g_colorFade.a <= 0)
		{
			//����������Ԃ�
			g_fade = FADE_NONE;
			g_colorFade.a = 0;
		}
		else
		{
			g_colorFade.a -= g_fFadeCnt;//�����x�̍X�V
			g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);
			pVtx[0].col = g_colorFade;
			pVtx[1].col = g_colorFade;
			pVtx[2].col = g_colorFade;
			pVtx[3].col = g_colorFade;
			g_pVtxBuffFade->Unlock();
		}
	}
	else if (g_fade == FADE_OUT)//fade out ����
	{
		if (g_colorFade.a >= 1)
		{
			//����mode�ֈڂ�
			g_colorFade.a = 1;
			SetMode(g_modeNext);
			g_fade = FADE_IN;
		}
		else
		{
			//if (GetkeyboardTrigger(DIK_RETURN) == true) g_colorFade.a = (float)0.95;//enter�L�[��fade������skip����
			g_colorFade.a += g_fFadeCnt;//�����x�̍X�V
			g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);
			pVtx[0].col = g_colorFade;
			pVtx[1].col = g_colorFade;
			pVtx[2].col = g_colorFade;
			pVtx[3].col = g_colorFade;
			g_pVtxBuffFade->Unlock();
		}
	}
}

void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDeviceFd = GetDevice();
	pDeviceFd->SetStreamSource(0, g_pVtxBuffFade, 0, sizeof(VERTEX_2D));//���_Data flow�̐ݒ�
	pDeviceFd->SetFVF(FVF_VERTEX_2D);//���_mod�̐ݒ�
	pDeviceFd->SetTexture(0, NULL);//Texture�̐ݒ�
	pDeviceFd->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);//���_�̕`��
}

//mode��]�����������A�悸fade��active����
void SetFade(FADE fade, MODE modeNext)
{
	g_fade = fade;//fade out��������
	g_modeNext = modeNext;
}

FADE GetFade(void)
{
	return g_fade;
}