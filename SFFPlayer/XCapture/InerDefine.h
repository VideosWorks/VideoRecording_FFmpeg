#pragma once

#include <string.h>

#define MAX_DEVICE_LENGTH 256

#define VIDEO_DATA_CAPTURE_ID 1000

#define SAVE_FILE_MAX_LEN 500

//�첽��Ϣ����
enum ENUM_ASYNC_MSG
{
	RESET_CAPTURE = 10001,
	SATRT_SAVE,//��ʼ�洢
	STOP_SAVE,//ֹͣ�洢
	RESET_SAVE,//���ô洢
};

//��Ⱦ������
typedef struct stRenderData
{
	char*	data;
	//int     dataType;
	int		inersize;
	stRenderData() 
	{
		memset(this, 0, sizeof(stRenderData));
	}
}stRenderData;

//�����豸����Ϣ
typedef struct stResetDevice 
{
	char	deviceName[256];//�豸����
	int		width;//���
	int		height;//�߶�
	int		freqcy;//������
	stResetDevice()
	{
		memset(this, 0, sizeof(stResetDevice));
	}
};

//���ô洢��Ϣ
typedef struct stSetSaveInfo 
{
	int		freqcy;//������
	int     width;//��
	int     height;//��
	char	saveName[SAVE_FILE_MAX_LEN];//�洢����
	stSetSaveInfo()
	{
		memset(this, 0, sizeof(stSetSaveInfo));
	}
};