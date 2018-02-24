#pragma once
#include <string>
#include "aqueue.h"
using namespace std;

class XThreadBase;

//线程管理类
class XThreadMgr
{
public:
	XThreadMgr(int _msg_count, int _timer_count);
	virtual ~XThreadMgr();
	int send_cmd(const string & id, int _msg_id, int _lparam, long _wparam);
	int send_short_buff(const string & id, int _msg_id, const void * _buff, long _length);
	int send_long_buff(const string & id, int _msg_id, const void * _buff, long _length);
	int regist_timer(const string & id, int _timer_id, int _time_out);
	int unregist_timer(const string & id, int _timer_id);
	int attach_obj(XThreadBase * _obj, thread_type _type);
	int detch_obj(const string & id);
private:
	void*       _ctx;//上下文对象
	int		    _msgs;//消息线程
	int         _timers;//定时器线程
private:
	XThreadMgr(const XThreadMgr&);
	const XThreadMgr &operator = (const XThreadMgr&);
};

