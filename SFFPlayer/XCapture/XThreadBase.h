#pragma once

//线程基类对象

#include "aqueue.h"
#include "i_aqueue_callback.h"

#include <string>

using namespace std;
class XThreadMgr;

class XThreadBase : public i_asynobj_events
{
public:
	XThreadBase(const string& obj_id_, XThreadMgr* mgr_);
	~XThreadBase(void);

	/************************************************************************
	* 名称：OnTimer
	* 说明：//定时器实现者实现该函数。
	* 参数：id定时器事件ID
	* 返回值：无
	/************************************************************************/
	virtual void OnTimer(int id) = 0;

	/************************************************************************
	* 名称：OnAttach
	* 说明：附加对象到线程成功事件
	* 参数：无
	* 返回值：无
	/************************************************************************/
	virtual void OnAttach() = 0;

	/************************************************************************
	* 名称：OnDetach
	* 说明：从线程分离事件
	* 参数：无
	* 返回值：无
	/************************************************************************/
	virtual void OnDetach() = 0;

	/************************************************************************
	* 名称：OnMsg
	* 说明：响应其他线程的消息
	* 参数：cmd 命令ID,lparm,wparam
	* 返回值：无
	/************************************************************************/
	virtual void OnMsg(int cmd_, long long  lparm_, long long wparam_) = 0;

	/************************************************************************
	* 名称：get_id
	* 说明：获取本异步对象的ID
	* 参数：无
	* 返回值：对象ID
	/************************************************************************/
	string get_id();

	/************************************************************************
	* 名称：get_mgr
	* 说明：获取当前异步对象管理类
	* 参数：无
	* 返回值：对象ID
	/************************************************************************/
	XThreadMgr* get_mgr();

	/************************************************************************
	* 名称：add_timer
	* 说明：返回对象是否被初始化
	* 参数：无
	* 返回值：对象ID
	/************************************************************************/
	void add_timer(int tmid_, int tmout_);


private:
	/************************************************************************/
	/* 异步对象继承实现																								 */
	/************************************************************************/
	virtual void attach_event();
	virtual void dettach_event();
	virtual void timer_event(int id_);
	virtual void msg_event(aqueue::aqueue_msg_t* msg_);
protected:
	bool _isStaring;//标识该线程是否正在工作
private:
	string  _obj_id;//对象ID
	XThreadMgr* _aobj_mgr;//异步对象管理类

private:
	XThreadBase(const XThreadBase&);
	const XThreadBase &operator = (const XThreadBase&);
};
