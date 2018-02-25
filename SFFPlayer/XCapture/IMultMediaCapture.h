#pragma once
#ifndef __II_MULTMEDIA_CAPTURE_HH
#define __II_MULTMEDIA_CAPTURE_HH

class IMultMediaCapture 
{
public:
	virtual ~IMultMediaCapture() {};

	//��ʼ��ffmpeg��Ϣ
	static void Init();

	//����һ�������ػ���(������Ҫ�����Ĵ���ID)
	static IMultMediaCapture* CreateCapture(void* WID);

	//�����豸(�����豸����, ���ݽػ��С)
	virtual int Start(const char* device, int width, int height, int sampRate = 60) = 0;

	//ֹͣ�豸
	virtual int Stop() = 0;

	//�����洢
	virtual int StartSave(const char* name = "default") = 0;

	//ֹͣ�洢
	virtual int StopSave() = 0;

protected:
	IMultMediaCapture() {};
};
#endif