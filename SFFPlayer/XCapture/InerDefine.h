#pragma once

#include <string.h>

//�첽��Ϣ����
enum ENUM_ASYNC_MSG 
{
	RESET_CAPTURE
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