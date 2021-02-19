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
	MOTIONTYPE_NEUTRAL = 0,
	MOTIONTYPE_WALK,
	MOTIONTYPE_RUN,
	MOTIONTYPE_JUMP,
	MOTIONTYPE_SQUAT,//���Ⴊ�ށ@(�㔼�g�X�V����)
	MOTIONTYPE_SHOOT1,//gun1 shoot (�㔼�g�X�V����)
	MOTIONTYPE_SHOOT2,//gun2 shoot (�㔼�g�X�V����)
	MOTIONTYPE_RELOAD,//reload gun�@(�㔼�g�X�V����)
	MOTIONTYPE_THROW,//throw the grenade�@(�㔼�g�X�V����)
	MOTIONTYPE_MAX,
}MOTIONTYPE;

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
	int nNumkey;//����keyframe�ԍ�
	int nMAXkey;
	KEY_INFO akeyInfo[2];//keyframe�̑���
}MOTION_INFO;

typedef struct
{
	MOTION_INFO aMotionInfo[MOTIONTYPE_MAX];//�Smotion�̒�`
	int nNumMotion;//motion�̐�
	MOTIONTYPE motionType;//���̏��
	bool bLoopMotion, bPlayMotion;//motion
	int nNumkey;//�S����keyframe��
	int nKey;//�Đ�����keyID
	int nCntMotion;//

	D3DXVECTOR3 pos;//�Smodel���S���W
	D3DXVECTOR3 rot;//�Smodel����
	D3DXMATRIX mtxworld;//�Smodel���E�s��
	MODEL aModel[10];//player�͑S��10�p�[�c�őg�ݍ��킹��
	int nNumModel, ID;//�p�[�c��=10�AID�͐e�q�֌W�ɂ��Ă̌v�Z�p
	bool bUse;
	float fMoveSpeed;//�ړ����x
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
