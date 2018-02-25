#pragma once

#include <string.h>

#define MAX_DEVICE_LENGTH 256

#define VIDEO_DATA_CAPTURE_ID 1000

#define SAVE_FILE_MAX_LEN 500

//异步消息定义
enum ENUM_ASYNC_MSG
{
	RESET_CAPTURE = 10001,
	SATRT_SAVE,//开始存储
	STOP_SAVE,//停止存储
	RESET_SAVE,//重置存储
};

//渲染的数据
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

//重置设备的信息
typedef struct stResetDevice 
{
	char	deviceName[256];//设备名称
	int		width;//宽度
	int		height;//高度
	int		freqcy;//采样率
	stResetDevice()
	{
		memset(this, 0, sizeof(stResetDevice));
	}
};

//重置存储信息
typedef struct stSetSaveInfo 
{
	int		freqcy;//采样率
	int     width;//宽
	int     height;//高
	char	saveName[SAVE_FILE_MAX_LEN];//存储名称
	stSetSaveInfo()
	{
		memset(this, 0, sizeof(stSetSaveInfo));
	}
};