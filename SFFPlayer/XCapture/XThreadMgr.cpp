#include "XThreadMgr.h"
#include "aqueue.h"
#include "XThreadBase.h"

XThreadMgr::XThreadMgr(int _msg_count, int _timer_count) :
	_ctx(NULL),
	_msgs(_msg_count),
	_timers(_timer_count)
{
	_ctx = aqueue_init(_msgs, _timers);
	aqueue_start(_ctx);
}

XThreadMgr::~XThreadMgr(void)
{
	if (_ctx)
	{
		aqueue_ctx_destroy(_ctx);
	}
}

int XThreadMgr::send_cmd(const string& id, int _msg_id, int _lparam, long _wparam)
{
	if (NULL == _ctx)
	{
		return -1;
	}

	aqueue::aqueue_msg_t msg;
	msg.type = aqueue::aqueue_msg_t::common_msg;
	msg.body.msg_common.lparam = _lparam;
	msg.body.msg_common.wparam = _wparam;
	msg.msg_id = _msg_id;

	return aqueue_send_msg(id.c_str(), &msg, _ctx);
}

int XThreadMgr::send_short_buff(const string& id, int _msg_id, const void* _buff, long _length)
{
	//短数据不能超过512字节
	if (NULL == _ctx || (_length > 512))
	{
		return -1;
	}

	aqueue::aqueue_msg_t msg;
	msg.type = aqueue::aqueue_msg_t::short_msg;
	memcpy(msg.body.msg_short.msg_buf, _buff, _length);
	msg.body.msg_short.msg_len = _length;
	msg.msg_id = _msg_id;

	return aqueue_send_msg(id.c_str(), &msg, _ctx);
}

int XThreadMgr::send_long_buff(const string& id, int _msg_id, const void* _buff, long _length)
{
	if (NULL == _ctx)
	{
		return -1;
	}

	aqueue::aqueue_msg_t msg;
	msg.type = aqueue::aqueue_msg_t::long_msg;
	msg.body.msg_long.msg_buf = (char*)_buff;
	msg.body.msg_long.msg_len = _length;
	msg.msg_id = _msg_id;

	return aqueue_send_msg(id.c_str(), &msg, _ctx);
}

int XThreadMgr::regist_timer(const string& id, int _timer_id, int _time_out)
{
	//return -1;
	if (NULL == _ctx)
	{
		return -1;
	}

	return aqueue_register_timer(id.c_str(), _time_out, _timer_id, _ctx);
}

int XThreadMgr::unregist_timer(const string& id, int _timer_id)
{
	if (NULL == _ctx)
	{
		return -1;
	}

	return aqueue_unregister_timer(id.c_str(), _timer_id, _ctx);
}

int XThreadMgr::attach_obj(XThreadBase* _obj, thread_type _type /*= e_msg*/)
{
	if (NULL == _ctx)
	{
		return -1;
	}

	return aqueue_attach_asynobject(_obj->get_id().c_str(), _obj, _ctx, _type);
}

int XThreadMgr::detch_obj(const string& id)
{
	if (NULL == _ctx)
	{
		return -1;
	}

	return aqueue_dettach_asynobject(id.c_str(), _ctx);
}
