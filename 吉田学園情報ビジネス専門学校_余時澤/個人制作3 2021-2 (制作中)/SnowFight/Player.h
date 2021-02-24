//=============================================================================
//
// [Player.h]
// Author : JITAKU YO
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "DirectX.h"

//motion�̎��
typedef enum
{
	P_NEUTRAL = 0,
	P_RUN,
	P_BACK,
	P_THROW,
	P_DEAD,
	P_MAX,
}PLAYER_STATE;

//�L�[�̍\����
typedef struct
{
	//�ʒu
	float fPosX;
	float fPosY;
	float fPosZ;
	//����
	float fRotX;
	float fRotY;
	float fRotZ;
}KEY;

//keyframe
typedef struct
{
	int nFrame;//motion���x
	KEY akey[10];//�p�[�c��
}KEY_INFO;

//motion
typedef struct
{
	bool bLoop;//�z���邩�ǂ���
	bool bLock;
	int nNumkey;//����keyframe�ԍ�
	int nMAXkey;
	KEY_INFO akeyInfo[10];//keyframe��MAX��
}MOTION_INFO;

typedef struct
{
	MOTION_INFO aMotionInfo[P_MAX];//�Smotion�̒�`
	int nNumMotion;//motion�̐�
	PLAYER_STATE state;//���̏��
	bool bLoopMotion, bPlayMotion;//motion
	int nNumkey;//�S����keyframe��
	int nKey;//�Đ�����keyID
	int nCntMotion;//

	D3DXVECTOR3 pos;//�Smodel���S���W
	D3DXVECTOR3 move;//�ړ��ʍX�V
	D3DXVECTOR3 rot;//�Smodel����
	D3DXMATRIX mtxworld;//�Smodel���E�s��
	MODEL aModel[10];//player�͑S��10�p�[�c�őg�ݍ��킹��
	int nNumModel, ID, nScore;//�p�[�c��=10�AID�͐e�q�֌W�ɂ��Ă̌v�Z�p
	bool bUse;
	float fMoveSpeed;//�ړ����x
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
