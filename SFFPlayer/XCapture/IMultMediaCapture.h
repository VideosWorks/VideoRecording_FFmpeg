#pragma once
#ifndef __II_MULTMEDIA_CAPTURE_HH
#define __II_MULTMEDIA_CAPTURE_HH

class IMultMediaCapture 
{
public:
	virtual ~IMultMediaCapture() {};

	//初始化ffmpeg信息
	static void Init();

	//创建一个视屏截获类(输入需要依附的窗口ID)
	static IMultMediaCapture* CreateCapture(void* WID);

	//启动设备(输入设备名称, 数据截获大小)
	virtual int Start(const char* device, int width, int height, int sampRate = 60) = 0;

	//停止设备
	virtual int Stop() = 0;

	//启动存储
	virtual int StartSave(const char* name = "default") = 0;

	//停止存储
	virtual int StopSave() = 0;

protected:
	IMultMediaCapture() {};
};
#endif