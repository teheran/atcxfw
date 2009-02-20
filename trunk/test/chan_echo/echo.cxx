#include "chan_abc.h"
#include <memory>

#include "asterisk/module.h"

//
//  DeviceChannel impl
//
struct ast_channel * ChannelDevice_ABC::request_channel(const char *type, int format, void *data, int *cause)
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
        return NULL;
    }

    tmp->tech = _tech;
 

    std::auto_ptr<Channel_ABC> spChan(new Channel_ABC());
    int cause = spChan->init(_tech, type, format, static_cast<char *>(data));
    if(0 == cause) {
        tmp->tech_pvt = (reinterpret_cast<void*>(spChan.release()));
    }
    return tmp;    
}

void ChannelDevice_ABC::release_channel(Channel*)
{
    ast_log(LOG_NOTICE, "\n");
}

int ChannelDevice_ABC::get_state(void *data)
{
    ast_log(LOG_NOTICE, "\n");

    return -1; //AST_DEVICE_INUSE;
}

//
//  Channel impl
//
int Channel_ABC::init(const struct ast_channel_tech* tech, const char *type, int format, void *data)
{
    _channel->nativeformats = _channel->tech->capabilities;
    _channel->writeformat = ast_best_codec(_channel->nativeformats);
    _channel->rawwriteformat = ast_best_codec(_channel->nativeformats);
    _channel->readformat = ast_best_codec(_channel->nativeformats);
    _channel->rawreadformat = ast_best_codec(_channel->nativeformats);
    
    ::pipe(_pipefds);
    
    _channel->fds[0] = _pipefds[0];
    _channel->fds[1] = _pipefds[1];

    return 0;
}

Channel_ABC::~Channel_ABC()
{
    ::close(_pipefds[0]);
    ::close(_pipefds[1]);
}

struct ast_frame * Channel_ABC::read ()
{
    struct ast_frame * tmp = NULL;
    return sizeof(tmp) == ::read(_pipefds[0], &tmp, sizeof(tmp)) ? tmp : NULL;
}

int Channel_ABC::write (struct ast_frame *frame)
{
   struct ast_frame * tmp = ast_frdup(frame);
   return sizeof(frame) == ::write(_pipefds[1], &tmp, sizeof(frame)) ? 0 : -1;
}

int Channel_ABC::call (char *addr, int timeout)
{
    return ast_setstate(_channel, AST_STATE_UP);
}

int Channel_ABC::hangup ()
{
    return 0;
}

int Channel_ABC::indicate (int condition, const void *data, size_t datalen)
{
    return 0;
}

//
//  ChannelDevice adapters impl
//
int create_device (ChannelDevice** device, const struct ast_channel_tech *tech , const char *cfg)
{
    if(device == NULL || *device != NULL) {
        return AST_MODULE_LOAD_FAILURE; // invalid arg || device is already in use
    }

    std::auto_ptr<ChannelDevice> spDev(new ChannelDevice_ABC(tech));
    if(NULL != spDev.get()) 
    {
        int retVal = (spDev->load_config(cfg))
                    ? AST_MODULE_LOAD_DECLINE 
                    : AST_MODULE_LOAD_SUCCESS;

        if(::ast_channel_register(tech)) {
            return AST_MODULE_LOAD_FAILURE;
        }
        else {
            *device = spDev.release();
            return retVal;
        }
    }

    return AST_MODULE_LOAD_FAILURE;
}

void abc_device_free( struct ChannelDevice *dev)
{
    delete dev;
}

