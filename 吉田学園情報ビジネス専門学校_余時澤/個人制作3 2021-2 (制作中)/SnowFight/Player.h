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
	MOTIONTYPE_NEUTRAL = 0,
	MOTIONTYPE_WALK,
	MOTIONTYPE_RUN,
	MOTIONTYPE_JUMP,
	MOTIONTYPE_SQUAT,//しゃがむ　(上半身更新だけ)
	MOTIONTYPE_SHOOT1,//gun1 shoot (上半身更新だけ)
	MOTIONTYPE_SHOOT2,//gun2 shoot (上半身更新だけ)
	MOTIONTYPE_RELOAD,//reload gun　(上半身更新だけ)
	MOTIONTYPE_THROW,//throw the grenade　(上半身更新だけ)
	MOTIONTYPE_MAX,
}MOTIONTYPE;

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
	int nNumkey;//今のkeyframe番号
	int nMAXkey;
	KEY_INFO akeyInfo[2];//keyframeの総数
}MOTION_INFO;

typedef struct
{
	MOTION_INFO aMotionInfo[MOTIONTYPE_MAX];//全motionの定義
	int nNumMotion;//motionの数
	MOTIONTYPE motionType;//今の状態
	bool bLoopMotion, bPlayMotion;//motion
	int nNumkey;//全部のkeyframe数
	int nKey;//再生中のkeyID
	int nCntMotion;//

	D3DXVECTOR3 pos;//全model中心座標
	D3DXVECTOR3 rot;//全model向き
	D3DXMATRIX mtxworld;//全model世界行列
	MODEL aModel[10];//playerは全部10パーツで組み合わせる
	int nNumModel, ID;//パーツ数=10、IDは親子関係についての計算用
	bool bUse;
	float fMoveSpeed;//移動速度
}PLAYER;

HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER *GetPlayer(void);
MOTIONTYPE PlayMotion(int PlayerMotion);
void PlayKeyFrame(int KeyPre, int KeyNext);
void ReadMotion(void);
void PlayFrame(int nMaxkey);
void GetKeyDifference(int FrameNext, int FrameNow);
#endif // !_PLAYER_H_
