//=============================================================================
//
// [Bullet.cpp]
// Author : Yo Jitaku
//
//=============================================================================
#include "bullet.h"
#include "score.h"
#include "enemy.h"
#include "Player.h"
#include "Sound.h"
#include "Explosion.h"
#include "Item.h"
#include "BossStage.h"
#include "OverAndClear.h"
#include "Fade.h"
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;//bullet���_buff��pointer
LPDIRECT3DTEXTURE9 g_pTextureBullet[BULLET_TEXTURE] = {};//bullet�摜��pointer
BULLET g_aBullet[PLAYER_BULLET_NUMBER];//bullet�̍ő吔
BULLET g_aEnemyBullet[ENEMY_BULLET_NUMBER];//enemybullet�̍ő吔

void SetBullet(void)
{
	BULLET *pBullet, *pEnBullet;
	pBullet = &g_aBullet[0];
	pEnBullet = &g_aEnemyBullet[0];
	//�S�Ă�bullet������
	for (int nCntBullet = 0; nCntBullet < PLAYER_BULLET_NUMBER; nCntBullet++, pBullet++)
	{
		pBullet->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pBullet->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pBullet->size = D3DXVECTOR2(50.0f, 25.0f);
		pBullet->bUse = false;
	}

	for (int nCnt = 0; nCnt < ENEMY_BULLET_NUMBER; nCnt++, pEnBullet++)
	{
		pEnBullet->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pEnBullet->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pEnBullet->size = D3DXVECTOR2(10.0f, 10.0f);
		pEnBullet->bUse = false;
	}
}

HRESULT InitBullet(void)
{
	VERTEX_2D *pVtx;//2D���_���\���̂�pointer�ݒ�
	LPDIRECT3DDEVICE9 pDeviceBt = GetDevice();
	BULLET *pBullet, *pEnBullet;
	pBullet = &g_aBullet[0];
	pEnBullet = &g_aEnemyBullet[0];
	SetBullet();

	D3DXCreateTextureFromFile(pDeviceBt, "data/TEXTURE/GunFire1Bullet.png", &g_pTextureBullet[0]);
	D3DXCreateTextureFromFile(pDeviceBt, "data/TEXTURE/EnemyBullet.png", &g_pTextureBullet[1]);

	//bullet���_buff�̐ݒ�
	if (FAILED(pDeviceBt->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * (PLAYER_BULLET_NUMBER + ENEMY_BULLET_NUMBER), D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffBullet, NULL))) return E_FAIL;
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);
	//player bullet
	for (int nCntBullet = 0; nCntBullet < PLAYER_BULLET_NUMBER; nCntBullet++, pVtx += 4, pBullet++)
	{
		pVtx[0].pos = D3DXVECTOR3(pBullet->pos.x - pBullet->size.x, pBullet->pos.y - pBullet->size.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(pBullet->pos.x + pBullet->size.x, pBullet->pos.y - pBullet->size.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(pBullet->pos.x - pBullet->size.x, pBullet->pos.y + pBullet->size.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(pBullet->pos.x + pBullet->size.x, pBullet->pos.y + pBullet->size.y, 0.0f);
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
	//enemy bullet
	for (int nCntBullet = 0; nCntBullet < ENEMY_BULLET_NUMBER; nCntBullet++, pVtx += 4, pEnBullet++)
	{
		pVtx[0].pos = D3DXVECTOR3(pEnBullet->pos.x - pEnBullet->size.x, pEnBullet->pos.y - pEnBullet->size.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(pEnBullet->pos.x + pEnBullet->size.x, pEnBullet->pos.y - pEnBullet->size.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(pEnBullet->pos.x - pEnBullet->size.x, pEnBullet->pos.y + pEnBullet->size.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(pEnBullet->pos.x + pEnBullet->size.x, pEnBullet->pos.y + pEnBullet->size.y, 0.0f);
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		pVtx[0].col = D3DCOLOR_RGBA(0, 255, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(0, 255, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(0, 255, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(0, 255, 0, 255);
		pVtx[0].tex = D3DXVECTOR2(0.0, 0.0);
		pVtx[1].tex = D3DXVECTOR2(1.0, 0.0);
		pVtx[2].tex = D3DXVECTOR2(0.0, 1.0);
		pVtx[3].tex = D3DXVECTOR2(1.0, 1.0);
	}
	g_pVtxBuffBullet->Unlock();

	return S_OK;
}

void UninitBullet(void)
{
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
	for (int nCnt = 0; nCnt < BULLET_TEXTURE; nCnt++)
	{
		if (g_pTextureBullet[nCnt] != NULL)
		{
			g_pTextureBullet[nCnt]->Release();
			g_pTextureBullet[nCnt] = NULL;
		}
	}
}

void UpdateBullet(void)
{
	VERTEX_2D *pVtx;//2D���_���\���̂�pointer�ݒ�
	//bullet pointer�̐ݒ�@create and init
	BULLET *pBullet, *pEnBullet;
	pBullet = &g_aBullet[0];
	pEnBullet = &g_aEnemyBullet[0];
	PLAYER *pPlayer = GetPlayer();
	BOMB *pBomb = GetBomb();
	BOSS *pBoss = GetBoss();
	BOSSEYE *pBossEyes = GetBossEyes();
	OAC *pOAC = GetOAC();//GAME OVER AND GAME CLEAR
	ENEMY *pEnemy;

	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);
	//player��bullet�ړ�
	for (int nCntBullet = 0; nCntBullet < PLAYER_BULLET_NUMBER; nCntBullet++, pBullet++, pVtx += 4)
	{
		if (pBullet->bUse == true)
		{
			pBullet->pos += pBullet->move;
			pVtx[0].pos = D3DXVECTOR3(pBullet->pos.x - pBullet->size.x, pBullet->pos.y - pBullet->size.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(pBullet->pos.x + pBullet->size.x, pBullet->pos.y - pBullet->size.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(pBullet->pos.x - pBullet->size.x, pBullet->pos.y + pBullet->size.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(pBullet->pos.x + pBullet->size.x, pBullet->pos.y + pBullet->size.y, 0.0f);
			if (pBullet->pos.x < 0 || pBullet->pos.x > 1500 || pBullet->pos.y < 0 || pBullet->pos.y > 800) pBullet->bUse = false;

			pEnemy = GetEnemy();
			//player��bullet��enemy�̏d�˂锻��
			for (int nCntEnemy = 0; nCntEnemy < (MAX_ENEMY); nCntEnemy++, pEnemy++)
			{
 				if (pEnemy->bUse == true)
				{
					//abs��Βl�֐��@from <cmath>
					//bullet �� enemy���S���W�̊K��
					if (abs(pBullet->pos.x - pEnemy->pos.x) < (pBullet->size.x + pEnemy->size.x) && abs(pBullet->pos.y - pEnemy->pos.y) < (pBullet->size.y + pEnemy->size.y + 10))
					{
						//Enemy�@hurt�̏�ԂŁ@���G����
						if (pEnemy->bHit == true)
						{
							pBullet->bUse = false;
							break;
						}
						//Enemy dead
						else
						{
							if (pEnemy->nLife == 0)
							{
								SetExplosion(pEnemy->pos, (int)pEnemy->size.x);//explosion effect
								SetItem(pEnemy->pos, pEnemy->Item);//item���Ă���enemy�Ł@item�o��
								pBullet->bUse = false;
								pEnemy->bUse = false;
								PlaySound(SOUND_LABEL_SE_EXPLOSIONENEMY);
								switch (pEnemy->nType)//enemy�̎�ނɂ����Score�����
								{
								case 0:
									AddScore(100);
									break;
								case 1:
									AddScore(200);
									break;
								case 2:
									AddScore(300);
									break;
								case 3:
									AddScore(400);
									break;
								}
							}
							else//Enemy��HP-1�Ahurt��ԂɈڂ�
							{
								pEnemy->nLife--;
								PlaySound(SOUND_LABEL_SE_HIT001);
								pEnemy->bHit = true;
							}
							break;
						}
					}
				}
			}

			//player��bullet��boss�̏d�˂锻��
			if (pBoss->bUse == true)
			{
				//�����蔻��
				if (abs(pBullet->pos.x - pBoss->pos.x) < (pBullet->size.x + pBoss->size.x - 150) && abs(pBullet->pos.y - pBoss->pos.y) < (pBullet->size.y + pBoss->size.y - 100))
				{
					if (pBoss->bHit == false)
					{
						//boss dead
						if (pBoss->nLife <= 0)
						{
							PlaySound(SOUND_LABEL_SE_EXPLOSIONBOSS);
							pOAC[1].bUse = true;//gameclear�̏�����
							SetFade(FADE_OUT, MODE_OAC);//gameclear�ֈڂ�
							pBoss->bUse = false;
							pBullet->bUse = false;
							AddScore(800);//boss��|��score
							AddScore(pPlayer->nLife * 500);//�c����HP�́@score�ɉ��Z
							AddScore(pPlayer->nBomb * 300);//�c����bomb�́@score�ɉ��Z
							SetExplosion(pBoss->pos, (int)pBoss->size.x);//boss�{�̂�explosion effect
							for (int nCnt = 0; nCnt < 3; nCnt++, pBossEyes++)//bosseyes��explosion effect
							{
								SetExplosion(pBossEyes->pos, (int)pBossEyes->size.x);
								pBossEyes->bUse = false;
							}
						}
						else//boss get hurt
						{
							pBoss->nLife--;
							PlaySound(SOUND_LABEL_SE_HIT001);
							pBoss->bHit = true;
							AddScore(10);
						}
					}
					pBullet->bUse = false;
				}
			}
		}
	}
	//enemy bullet��update
	for (int nCntEnBullet = 0; nCntEnBullet < ENEMY_BULLET_NUMBER; nCntEnBullet++, pEnBullet++, pVtx += 4)
	{
		if (pEnBullet->bUse == true)
		{
			D3DXVECTOR3 different = pBomb->pos - pEnBullet->pos;//player�̍��W�Ɍ���
			float length = D3DXVec3Length(&different);//player�Ƃ̋������v�Z
			if (length < pBomb->size.x && pBomb->bUse == true)//bomb��enemybullet������
			{
				pEnBullet->bUse = false;
				SetExplosion(pEnBullet->pos, (int)pEnBullet->size.x);
			}
			switch (pEnBullet->nType)//enemybullet�ړ�
			{
			//�����ړ���bullet
			case 1:
				pEnBullet->pos += pEnBullet->move;
				break;
			//�΂߈ړ���bullet
			case 2:
				pEnBullet->pos.y += cosf(pEnBullet->fAngle) * 5;
				pEnBullet->pos.x += sinf(pEnBullet->fAngle) * 5;
				break;
			}
			pVtx[0].pos = D3DXVECTOR3(pEnBullet->pos.x - pEnBullet->size.x, pEnBullet->pos.y - pEnBullet->size.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(pEnBullet->pos.x + pEnBullet->size.x, pEnBullet->pos.y - pEnBullet->size.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(pEnBullet->pos.x - pEnBullet->size.x, pEnBullet->pos.y + pEnBullet->size.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(pEnBullet->pos.x + pEnBullet->size.x, pEnBullet->pos.y + pEnBullet->size.y, 0.0f);
			
			//��ʊO��bullet����
			if (pEnBullet->pos.x <= 0 || pEnBullet->pos.x >= 1500 || pEnBullet->pos.y <= 0 || pEnBullet->pos.y >= 800) pEnBullet->bUse = false;
			//player�Ƃ̓����蔻��
			if (abs(pPlayer->pos.x - pEnBullet->pos.x) < (pPlayer->size.x - 20 + pEnBullet->size.x) && abs(pPlayer->pos.y - 25 - pEnBullet->pos.y) < (pPlayer->size.y - 25 + pEnBullet->size.y))
			{
				//hit��Ԃ�bullet����
				if (pPlayer->bHit == true) pEnBullet->bUse = false;
				else
				{
					//player dead
					if (pPlayer->nLife == 1 && pPlayer->bUse != false)
					{
						pPlayer->bUse = false;			
						SetExplosion(pPlayer->pos, (int)pPlayer->size.x);//explosion effect
						PlaySound(SOUND_LABEL_SE_EXPLOSIONBOSS);
						pOAC[0].bUse = true;//gameover�̏�����
						SetFade(FADE_OUT, MODE_OAC);//gameover�ֈڂ�
						break;
					}
					//player hit
					else if (pPlayer->bUse != false)
					{
						pPlayer->nLife--;
						pEnBullet->bUse = false;
						pPlayer->bHit = true;
						SetExplosion(pEnBullet->pos, (int)pEnBullet->size.x);
						PlaySound(SOUND_LABEL_SE_HIT000);
					}
				}
			}
		}
	}
	g_pVtxBuffBullet->Unlock();
}

void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDeviceBt;
	pDeviceBt = GetDevice();
	//bullet pointer�̐ݒ�@create and init
	BULLET *pBullet, *pEnBullet;
	pBullet = &g_aBullet[0];
	pEnBullet = &g_aEnemyBullet[0];

	pDeviceBt->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));//���_Data flow�̐ݒ�
	pDeviceBt->SetFVF(FVF_VERTEX_2D);//���_mod�̐ݒ�
	
	//draw player bullet
	for (int nCntBullet = 0; nCntBullet < PLAYER_BULLET_NUMBER; nCntBullet++, pBullet++)
	{
		if (pBullet->bUse == true)
		{
			pDeviceBt->SetTexture(0, g_pTextureBullet[0]);
			//���_Data flow�̎g�p(1,ploygon�̎�ށ@2,�n�߂钸�_�@3,polygon�̐�(2��D3DPT_TRIANGLESTRIP�O�p�`))
			pDeviceBt->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * 4, 2);
		}
	}
	//draw enemy bullet
	for (int nCntEnBullet = 0; nCntEnBullet < ENEMY_BULLET_NUMBER; nCntEnBullet++, pEnBullet++)
	{
		if (pEnBullet->bUse == true)
		{
			pDeviceBt->SetTexture(0, g_pTextureBullet[1]);
			pDeviceBt->DrawPrimitive(D3DPT_TRIANGLESTRIP, PLAYER_BULLET_NUMBER * 4 + nCntEnBullet * 4, 2);
		}
	}
}

//player��bullet�ݒ�
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife)
{
	PlaySound(SOUND_LABEL_SE_SHOOT);
	VERTEX_2D *pVtx;
	//bullet pointer�̐ݒ�@create and init
	BULLET *pBullet = &g_aBullet[0];
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntBullet = 0; nCntBullet < PLAYER_BULLET_NUMBER; nCntBullet++, pBullet++, pVtx += 4)
	{
		if (pBullet->bUse == false)
		{
			pBullet->pos.x = pos.x;
			pBullet->pos.y = pos.y;
			pBullet->pos.z = pos.z;
			pBullet->move = move;
			pBullet->bUse = true;
			pBullet->nType = 0;
			pVtx[0].pos = D3DXVECTOR3(pBullet->pos.x - pBullet->size.x, pBullet->pos.y - pBullet->size.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(pBullet->pos.x + pBullet->size.x, pBullet->pos.y - pBullet->size.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(pBullet->pos.x - pBullet->size.x, pBullet->pos.y + pBullet->size.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(pBullet->pos.x + pBullet->size.x, pBullet->pos.y + pBullet->size.y, 0.0f);
			break;
		}
	}
	g_pVtxBuffBullet->Unlock();
}
//enemybullet�̐ݒ�
void SetEnemyBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fAngle, int nType)
{
	PlaySound(SOUND_LABEL_SE_SHOOTENEMY);
	VERTEX_2D *pVtx;
	BULLET *pEnBullet;
	pEnBullet = &g_aEnemyBullet[0];
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntBullet = 0; nCntBullet < PLAYER_BULLET_NUMBER; nCntBullet++, pEnBullet++, pVtx += 4)
	{
		if (pEnBullet->bUse == false)
		{
			pEnBullet->pos.x = pos.x;
			pEnBullet->pos.y = pos.y;
			pEnBullet->pos.z = pos.z;
			pEnBullet->move = move;
			pEnBullet->bUse = true;
			pEnBullet->fAngle = fAngle;
			pEnBullet->nType = nType;
			pVtx[0].pos = D3DXVECTOR3(pEnBullet->pos.x - pEnBullet->size.x, pEnBullet->pos.y - pEnBullet->size.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(pEnBullet->pos.x + pEnBullet->size.x, pEnBullet->pos.y - pEnBullet->size.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(pEnBullet->pos.x - pEnBullet->size.x, pEnBullet->pos.y + pEnBullet->size.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(pEnBullet->pos.x + pEnBullet->size.x, pEnBullet->pos.y + pEnBullet->size.y, 0.0f);
			break;
		}
	}
	g_pVtxBuffBullet->Unlock();
}