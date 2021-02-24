//=============================================================================
//
// [Player.h]
// Author : JITAKU YO
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "DirectX.h"

//motionの種類
typedef enum
{
	P_NEUTRAL = 0,
	P_RUN,
	P_BACK,
	P_THROW,
	P_DEAD,
	P_MAX,
}PLAYER_STATE;

//キーの構造体
typedef struct
{
	//位置
	float fPosX;
	float fPosY;
	float fPosZ;
	//向き
	float fRotX;
	float fRotY;
	float fRotZ;
}KEY;

//keyframe
typedef struct
{
	int nFrame;//motion速度
	KEY akey[10];//パーツ数
}KEY_INFO;

//motion
typedef struct
{
	bool bLoop;//循環するかどうか
	bool bLock;
	int nNumkey;//今のkeyframe番号
	int nMAXkey;
	KEY_INFO akeyInfo[10];//keyframeのMAX数
}MOTION_INFO;

typedef struct
{
	MOTION_INFO aMotionInfo[P_MAX];//全motionの定義
	int nNumMotion;//motionの数
	PLAYER_STATE state;//今の状態
	bool bLoopMotion, bPlayMotion;//motion
	int nNumkey;//全部のkeyframe数
	int nKey;//再生中のkeyID
	int nCntMotion;//

	D3DXVECTOR3 pos;//全model中心座標
	D3DXVECTOR3 move;//移動量更新
	D3DXVECTOR3 rot;//全model向き
	D3DXMATRIX mtxworld;//全model世界行列
	MODEL aModel[10];//playerは全部10パーツで組み合わせる
	int nNumModel, ID, nScore;//パーツ数=10、IDは親子関係についての計算用
	bool bUse;
	float fMoveSpeed;//移動速度
}PLAYER;

HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER *GetPlayer(void);
void PlayMotion(int PlayerMotion);
void ReadMotion(void);
void GetKeyDifference(int FrameNext, int FrameNow);
#endif // !_PLAYER_H_
