#pragma once

#include <string.h>

//异步消息定义
enum ENUM_ASYNC_MSG 
{
	RESET_CAPTURE
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