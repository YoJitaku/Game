//=============================================================================
//
// [Item.cpp]
// Author : Yo Jitaku
//
//=============================================================================
#include "Item.h"
#include "Player.h"

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;//bullet���_buff��pointer
LPDIRECT3DTEXTURE9 g_pTextureItem[ITEM_TYPE] = {};//bullet�摜��pointer
ITEM g_aItem[ITEM_NUMBER];//bullet���ʂ̍ő吔

void SetItem(void)
{
	ITEM *pItem = &g_aItem[0];
	//������
	for (int nCnt = 0; nCnt < ITEM_NUMBER; nCnt++, pItem++)
	{
		pItem->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		if (nCnt < 3)//bullet upgrade �O��
		{
			pItem->move = D3DXVECTOR3(-5.0f, -5.0f, 0.0f);
			pItem->nTypeItem = 0;
			pItem->size = D3DXVECTOR2(30.0f, 30.0f);
		}
		else//bomb number plus ����
		{
			pItem->move = D3DXVECTOR3(-3.0f, -3.0f, 0.0f);
			pItem->nTypeItem = 1;
			pItem->size = D3DXVECTOR2(35.0f, 35.0f);
		}
		pItem->bUse = false;
	}
}

HRESULT InitItem(void)
{
	VERTEX_2D *pVtx;//2D���_���\���̂�pointer�ݒ�
	LPDIRECT3DDEVICE9 pDeviceIt = GetDevice();
	ITEM *pItem = &g_aItem[0];

	SetItem();//������

	D3DXCreateTextureFromFile(pDeviceIt, "data/TEXTURE/Item1.png", &g_pTextureItem[0]);
	D3DXCreateTextureFromFile(pDeviceIt, "data/TEXTURE/Item2.png", &g_pTextureItem[1]);

	//bullet���_buff�̐ݒ�
	if (FAILED(pDeviceIt->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * ITEM_NUMBER, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffItem, NULL))) return E_FAIL;
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntItem = 0; nCntItem < ITEM_NUMBER; nCntItem++, pVtx += 4, pItem++)
	{
		pVtx[0].pos = D3DXVECTOR3(pItem->pos.x - pItem->size.x, pItem->pos.y - pItem->size.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(pItem->pos.x + pItem->size.x, pItem->pos.y - pItem->size.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(pItem->pos.x - pItem->size.x, pItem->pos.y + pItem->size.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(pItem->pos.x + pItem->size.x, pItem->pos.y + pItem->size.y, 0.0f);
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[0].tex = D3DXVECTOR2(0.0, 0.0);
		pVtx[1].tex = D3DXVECTOR2(1.0, 0.0);
		pVtx[2].tex = D3DXVECTOR2(0.0, 1.0);
		pVtx[3].tex = D3DXVECTOR2(1.0, 1.0);
	}
	g_pVtxBuffItem->Unlock();

	return S_OK;
}

void UninitItem(void)
{
	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem->Release();
		g_pVtxBuffItem = NULL;
	}
	for (int nCnt = 0; nCnt < ITEM_TYPE; nCnt++)
	{
		if (g_pTextureItem[nCnt] != NULL)
		{
			g_pTextureItem[nCnt]->Release();
			g_pTextureItem[nCnt] = NULL;
		}
	}
}

void UpdateItem(void)
{
	VERTEX_2D *pVtx;
	ITEM *pItem = &g_aItem[0];
	PLAYER *pPlayer = GetPlayer();

	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < ITEM_NUMBER; nCnt++, pItem++, pVtx += 4)
	{
		if (pItem->bUse == true)
		{
			pItem->pos += pItem->move;
			//item��ʓ����ړ��̌���
			if (pItem->pos.x < 0 || pItem->pos.x > 1500) pItem->move.x = -pItem->move.x;
			if (pItem->pos.y < 0 || pItem->pos.y > 800) pItem->move.y = -pItem->move.y;
			pVtx[0].pos = D3DXVECTOR3(pItem->pos.x - pItem->size.x, pItem->pos.y - pItem->size.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(pItem->pos.x + pItem->size.x, pItem->pos.y - pItem->size.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(pItem->pos.x - pItem->size.x, pItem->pos.y + pItem->size.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(pItem->pos.x + pItem->size.x, pItem->pos.y + pItem->size.y, 0.0f);

			//item and player �����蔻��
			if (abs(pPlayer->pos.x - pItem->pos.x) < (pPlayer->size.x - 15 + pItem->size.x) && abs(pPlayer->pos.y - pItem->pos.y) < (pPlayer->size.y - 15 + pItem->size.y))
			{
				switch (pItem->nTypeItem)
				{
				case 0://bullet upgrade
					pPlayer->nBulletLevel++;
					break;
				case 1://bomb number plus
					pPlayer->nBomb++;
					break;
				}
				pItem->bUse = false;
			}
		}
	}
	g_pVtxBuffItem->Unlock();
}

void DrawItem(void)
{
	LPDIRECT3DDEVICE9 pDeviceIt = GetDevice();
	ITEM *pItem = &g_aItem[0];

	pDeviceIt->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX_2D));//���_Data flow�̐ݒ�
	pDeviceIt->SetFVF(FVF_VERTEX_2D);//���_mod�̐ݒ�

	for (int nCnt = 0; nCnt < ITEM_NUMBER; nCnt++, pItem++)
	{
		if (pItem->bUse == true)
		{
			pDeviceIt->SetTexture(0, g_pTextureItem[pItem->nTypeItem]);//Texture�̐ݒ�
			pDeviceIt->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);//���_�̕`��
		}
	}
}

//when enemy dead , item��active
void SetItem(D3DXVECTOR3 pos, int nType)
{
	VERTEX_2D *pVtx;
	ITEM *pItem = &g_aItem[0];

	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < ITEM_NUMBER; nCnt++, pItem++, pVtx += 4)
	{
		if (pItem->bUse == false)
		{
			switch (nType)
			{
			case 0://item�����Ă��Ȃ�enemy
				break;
			case 1://bullet item�����Ă���enemy
				pItem->bUse = true;
				pItem->nTypeItem = 0;
				break;
			case 2://bomb item�����Ă���enemy
				pItem->bUse = true;
				pItem->nTypeItem = 1;
				break;
			}
			pItem->pos = pos;//���W��������
			pVtx[0].pos = D3DXVECTOR3(pItem->pos.x - pItem->size.x, pItem->pos.y - pItem->size.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(pItem->pos.x + pItem->size.x, pItem->pos.y - pItem->size.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(pItem->pos.x - pItem->size.x, pItem->pos.y + pItem->size.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(pItem->pos.x + pItem->size.x, pItem->pos.y + pItem->size.y, 0.0f);
			break;
		}
	}
	g_pVtxBuffItem->Unlock();
}

ITEM *GetItem(void)
{
	return &g_aItem[0];
}