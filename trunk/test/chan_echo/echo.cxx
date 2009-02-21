#include "echo.h"
#include <memory>

#include "asterisk/module.h"

extern "C"
{
extern struct ChannelDevice* device;
}

//
//  ChannelDevice adapters impl
//
int initialize (const struct ast_channel_tech *tech , const char */*cfg*/)
{
    ast_log(LOG_NOTICE, "\n");

    try
    {
        std::auto_ptr<ChannelDevice> spDevice = std::auto_ptr<ChannelDevice>(new ChannelDevice_Echo(tech));

        if(0 == ::ast_channel_register(tech)) {
            device = spDevice.release();
        }
    }
    catch(...)
    {
//        assert(false);
//        throw;
    }

    return NULL != device ? 1 : 0;
}

int uninitialize(const struct ast_channel_tech *tech)
{
    ast_log(LOG_NOTICE, "\n");

    ::ast_channel_unregister(tech);
    
    if(device) {
        delete device;
        device = NULL;
    }
    return 1;
}

//
//  DeviceChannel impl
//
struct ast_channel * ChannelDevice_Echo::request_channel(const char */*type*/, int /*format*/, void */*data*/, int */*cause*/)
{
    ast_log(LOG_NOTICE, "\n");

    std::auto_ptr<Channel> spChannel = std::auto_ptr<Channel>(new Channel_Echo(_tech));
    struct ast_channel* tmp = spChannel->get_channel();
    ast_log(LOG_DEBUG, "tmp = %p", tmp);
    spChannel.release();
    return tmp;
}

int ChannelDevice_Echo::get_state(void *data)
{
    ast_log(LOG_NOTICE, "\n");

    return -1; //AST_DEVICE_INUSE;
}

//
//  Channel impl
//
Channel_Echo::Channel_Echo(const struct ast_channel_tech* tech)
{
    ast_log(LOG_NOTICE, "\n");

    struct ast_channel *tmp = NULL;
    tmp = ast_channel_alloc(0, /* do we need a queue; for why? */
                            AST_STATE_DOWN, /* requested channel is down */
                            "abc_cid_num", /* caller ID number */
                            "abc_cid_name", /* caller ID name */
                            "abc_accountcode", /* what is it? */
                            "777", /* extension; default is 's' */
                            "phones", /* context; default is 'default' */
                            0, /* somethig related to CDR & billing? */
                            "ABC/8:12"); /* provider(channel name)/???:??? * state mgmt relay on this  */

    if(NULL == tmp) {
        ast_log(LOG_WARNING, "Unable to allocate channel structure\n");
        throw -1;    
    }

    tmp->tech = tech;
 
    tmp->tech_pvt = (reinterpret_cast<void*>(this));

    tmp->nativeformats = tech->capabilities;
    tmp->writeformat = ast_best_codec(tech->capabilities);
    tmp->rawwriteformat = ast_best_codec(tech->capabilities);
    tmp->readformat = ast_best_codec(tech->capabilities);
    tmp->rawreadformat = ast_best_codec(tech->capabilities);
    
    ::pipe(_pipefds);
    tmp->fds[0] = _pipefds[0];
    tmp->fds[1] = _pipefds[1];

    _channel = tmp;    
    ast_log(LOG_DEBUG, "Well done\n");
    
}

Channel_Echo::~Channel_Echo()
{
    ast_log(LOG_NOTICE, "\n");

    ::close(_pipefds[0]);
    ::close(_pipefds[1]);
}

struct ast_frame * Channel_Echo::read ()
{
    struct ast_frame * tmp = NULL;
    return sizeof(tmp) == ::read(_pipefds[0], &tmp, sizeof(tmp)) ? tmp : NULL;
}

int Channel_Echo::write (struct ast_frame *frame)
{
   struct ast_frame * tmp = ast_frdup(frame);
   return sizeof(frame) == ::write(_pipefds[1], &tmp, sizeof(frame)) ? 0 : -1;
}

int Channel_Echo::call (char *addr, int timeout)
{
    return ast_setstate(_channel, AST_STATE_UP);
}

int Channel_Echo::hangup ()
{
    return 0;
}

int Channel_Echo::indicate (int condition, const void *data, size_t datalen)
{
    return 0;
}



