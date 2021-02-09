//=============================================================================
//
// サウンド処理 [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "DirectX.h"

//*****************************************************************************
// サウンドファイル
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BOSSBGM = 0,
	SOUND_LABEL_RANKBGM,
	SOUND_LABEL_STAGE1BGM,
	SOUND_LABEL_TITLE1BGM,
	SOUND_LABEL_TITLE2BGM,
	//SOUND_LABEL_TUTORIALBGM,
	SOUND_LABEL_SE_BOMB,
	SOUND_LABEL_SE_CANCEL000,
	SOUND_LABEL_SE_CHARGE000,
	SOUND_LABEL_SE_DECIDE,
	SOUND_LABEL_SE_EXPLOSIONBOSS,
	SOUND_LABEL_SE_EXPLOSIONENEMY,	// 爆発音
	SOUND_LABEL_SE_HIT000,
	SOUND_LABEL_SE_HIT001,			// ヒット音
	SOUND_LABEL_SE_LOCKON000,
	SOUND_LABEL_SE_PAUSE,
	SOUND_LABEL_SE_SELECT,
	SOUND_LABEL_SE_SHOOT,
	SOUND_LABEL_SE_SHOOTENEMY,
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
