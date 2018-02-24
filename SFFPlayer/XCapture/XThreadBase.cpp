#include "XThreadBase.h"
#include "XThreadMgr.h"

XThreadBase::XThreadBase( const string& obj_id_, XThreadMgr* mgr_ ):
    _obj_id(obj_id_),
    _aobj_mgr(mgr_) ,
	_isStaring(false)
{

}

XThreadBase::~XThreadBase( void )
{

}

std::string XThreadBase::get_id()
{
    return _obj_id;
}

XThreadMgr* XThreadBase::get_mgr()
{
    return _aobj_mgr;
}

void XThreadBase::add_timer( int tmid, int tmout )
{
    if (_aobj_mgr)
    {
        _aobj_mgr->regist_timer(get_id(), tmid, tmout);
    }
}

void XThreadBase::attach_event()
{
    OnAttach();
}

void XThreadBase::dettach_event()
{
    OnDetach();
}

void XThreadBase::timer_event( int id_ )
{
    OnTimer(id_);
}

void XThreadBase::msg_event( aqueue::aqueue_msg_t* msg )
{
    if (msg)
    {
        switch (msg->type)
        {
        case aqueue::aqueue_msg_t::common_msg:
            {
                //如果是命令消息
                OnMsg(msg->msg_id,
                    msg->body.msg_common.lparam,
                    msg->body.msg_common.wparam);
            }
            break;
        case aqueue::aqueue_msg_t::short_msg:
            {
                //如果是短包消息
                OnMsg(msg->msg_id,
                    msg->body.msg_short.msg_len,
					(long long)msg->body.msg_short.msg_buf);
            }
            break;
        case aqueue::aqueue_msg_t::long_msg:
            {
                //如果是长包消息
                OnMsg(msg->msg_id,
                    msg->body.msg_long.msg_len,
					(long long)msg->body.msg_long.msg_buf);
            }
            break;
        }
    }
}
