
extern "C" {

	#include "asterisk/devicestate.h"
}

#include "chan_dispatch.h"


struct ast_channel *request_channel(struct ChannelDevice *dev, const char *type, int format, void *data, int *cause)
{
   return dev
       ? dev->request_channel(type, format, data, cause)
       : NULL;
}

int get_device_state(struct ChannelDevice *dev, void *data)
{
    return dev 
        ? dev->get_state(data)
        : AST_DEVICE_INVALID;
}


Channel* get_channel_pvt(struct ast_channel *chan)
{
    return 
        (chan && chan->tech_pvt) 
            ? static_cast<Channel*>(chan->tech_pvt)
            : NULL;
}

int 
    channel_dispatch_send_digit_begin
        (struct ast_channel *chan, char digit)
{
    Channel* tmp = get_channel_pvt(chan);
    return  tmp ? tmp->send_digit_begin(digit) : -1;
}

int 
    channel_dispatch_send_digit_end
        (struct ast_channel *chan, char digit, unsigned int duration)
{
    Channel* tmp = get_channel_pvt(chan);
    return  tmp ? tmp->send_digit_end(digit, duration) : -1;
}

int 
	channel_dispatch_call
		(struct ast_channel *chan, char *addr, int timeout)
{
    Channel* tmp = get_channel_pvt(chan);
    return  tmp ? tmp->call(addr, timeout) : -1;
}

int 
    channel_dispatch_hangup
        (struct ast_channel *chan)
{
    Channel* tmp = get_channel_pvt(chan);
    int ret = tmp ? tmp->hangup() : -1;

    if (0 == ret) {
        // get_device(chan)->release_channel(tmp); ?? how to do it safe
        chan->tech_pvt = NULL;
        delete tmp;        
    }
    return ret;
}

int 
    channel_dispatch_answer
        (struct ast_channel *chan)
{
    Channel* tmp = get_channel_pvt(chan);
    return  tmp ? tmp->answer() : -1;
}

struct ast_frame * 
    channel_dispatch_read
        (struct ast_channel *chan)
{
    Channel* tmp = get_channel_pvt(chan);
    return  tmp ? tmp->read() : NULL;
}

int 
    channel_dispatch_write
        (struct ast_channel *chan, struct ast_frame *frame)
{
    Channel* tmp = get_channel_pvt(chan);
    return  tmp ? tmp->write(frame) : -1;
}

int 
    channel_dispatch_send_text
        (struct ast_channel *chan, const char *text)
{
    Channel* tmp = get_channel_pvt(chan);
    return  tmp ? tmp->send_text(text) : -1;
}

int 
    channel_dispatch_send_image
        (struct ast_channel *chan, struct ast_frame *frame)
{
    Channel* tmp = get_channel_pvt(chan);
    return  tmp ? tmp->send_image(frame) : -1;
}

int 
    channel_dispatch_send_html
        (struct ast_channel *chan, int subclass, const char *data, int len)
{
    Channel* tmp = get_channel_pvt(chan);
    return  tmp ? tmp->send_html(subclass, data, len) : -1;
}


struct ast_frame * 
    channel_dispatch_exception
        (struct ast_channel *chan)
{
    Channel* tmp = get_channel_pvt(chan);
    return  tmp ? tmp->exception() : NULL;
}


enum ast_bridge_result 
    channel_dispatch_bridge
        (struct ast_channel *c0, struct ast_channel *c1, int flags, struct ast_frame **fo, struct ast_channel **rc, int timeoutms)
{
/*  TODO
    Channel* tmp = get_channel_pvt(chan);
    return  tmp ? tmp->brige() : -1;
*/
    return (ast_bridge_result)-1;
}

int 
    channel_dispatch_indicate
        (struct ast_channel *chan, int condition, const void *data, size_t datalen)
{
    Channel* tmp = get_channel_pvt(chan);
    return  tmp ? tmp->indicate(condition, data, datalen) : -1;
}


int 
    channel_dispatch_fixup
        (struct ast_channel *oldchan, struct ast_channel *newchan)
{
/*  TODO
    Channel* tmp = get_channel_pvt(chan);
    return  tmp ? tmp->fixup(digit) : -1;
*/
    return -1;
}


int 
    channel_dispatch_setoption
        (struct ast_channel *chan, int option, void *data, int datalen)
{
    Channel* tmp = get_channel_pvt(chan);
    return  tmp ? tmp->setoption(option, data, datalen) : -1;
}


int 
    channel_dispatch_queryoption
        (struct ast_channel *chan, int option, void *data, int *datalen)
{
    Channel* tmp = get_channel_pvt(chan);
    return  tmp ? tmp->queryoption(option, data, datalen) : -1;
}


int 
    channel_dispatch_transfer
        (struct ast_channel *chan, const char *newdest)
{
    Channel* tmp = get_channel_pvt(chan);
    return  tmp ? tmp->transfer(newdest) : -1;
}


int 
    channel_dispatch_write_video
        (struct ast_channel *chan, struct ast_frame *frame)
{
    Channel* tmp = get_channel_pvt(chan);
    return  tmp ? tmp->write_video(frame) : -1;
}

/*  TODO
struct ast_channel *
    channel_dispatch_bridged_channel
       (struct ast_channel *chan, struct ast_channel *bridge)
{
    Channel* tmp = get_channel_pvt(chan);
    return  tmp ? tmp->bridge_channel(bridge) : NULL;
}
*/

int 
    channel_dispatch_func_channel_read
        (struct ast_channel *chan, char *function, char *data, char *buf, size_t len)
{
    Channel* tmp = get_channel_pvt(chan);
    return  tmp ? tmp->func_channel_read(function, data, buf, len) : -1;
}

int 
    channel_dispatch_func_channel_write
        (struct ast_channel *chan, char *function, char *data, const char *value)
{
    Channel* tmp = get_channel_pvt(chan);
    return  tmp ? tmp->func_channel_write(function, data, value) : -1;
}


struct ast_channel* 
    channel_dispatch_get_base_channel
        (struct ast_channel *chan)
{
    Channel* tmp = get_channel_pvt(chan);
    return  tmp ? tmp->get_base_channel() : NULL;
}


int 
    channel_dispatch_set_base_channel
        (struct ast_channel *chan, struct ast_channel *base)
{
    Channel* tmp = get_channel_pvt(chan);
    return  tmp ? tmp->set_base_channel(base) : -1;
}


int Channel::send_digit_begin (char digit)
{
    return -1;
}

int Channel::send_digit_end (char digit, unsigned int duration)
{
    return -1;
}


int Channel::call (char *addr, int timeout)
{
    return -1;
}


int Channel::hangup ()
{
    return -1;
}


int Channel::answer ()
{
    return -1;
}


struct ast_frame * Channel::read ()
{
    return NULL;
}


int Channel::write (struct ast_frame *frame)
{
    return -1;
}


int Channel::send_text (const char *text)
{
    return -1;
}


int Channel::send_image (struct ast_frame *frame)
{
    return -1;
}


int Channel::send_html (int subclass, const char *data, int len)
{
    return -1;
}


struct ast_frame * Channel::exception ()
{
    return NULL;
}


//	enum ast_bridge_result Channel::bridge (struct ast_channel *c0, struct ast_channel *c1, int flags, struct ast_frame **fo, struct ast_channel **rc, int timeoutms)
int Channel::indicate (int condition, const void *data, size_t datalen)
{
    return -1;
}


//	int fixup (struct ast_channel *oldchan, struct ast_channel *newchan)
int Channel::setoption (int option, void *data, int datalen)
{
    return -1;
}


int Channel::queryoption (int option, void *data, int *datalen)
{
    return -1;
}


int Channel::transfer (const char *newdest)
{
    return -1;
}


int Channel::write_video (struct ast_frame *frame)
{
    return -1;
}


struct ast_channel * Channel::bridged_channel (struct ast_channel *bridge)
{
    return NULL;
}


int Channel::func_channel_read (char *function, char *data, char *buf, size_t len)
{
    return -1;
}


int Channel::func_channel_write (char *function, char *data, const char *value)
{
    return -1;
}


struct ast_channel* Channel::get_base_channel ()
{
    return NULL;
}


int Channel::set_base_channel (struct ast_channel *base)
{
    return -1;
}


ChannelDevice::ChannelDevice(const struct ast_channel_tech *tech) 
    : _tech(tech) { /* */ }




