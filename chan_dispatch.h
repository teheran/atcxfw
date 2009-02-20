#ifndef CHAN_DISPATCH
#define CHAN_DISPATCH

#ifdef __cplusplus
extern "C" {
#endif

//
//	Channel dispatchers 
//

#include "asterisk/channel.h"

int 
	channel_dispatch_send_digit_begin
		(struct ast_channel *chan, char digit);

int 
	channel_dispatch_send_digit_end
		(struct ast_channel *chan, char digit, unsigned int duration);

int 
	channel_dispatch_call
		(struct ast_channel *chan, char *addr, int timeout);

int 
	channel_dispatch_hangup
		(struct ast_channel *chan);

int 
	channel_dispatch_answer
		(struct ast_channel *chan);

struct ast_frame * 
	channel_dispatch_read
		(struct ast_channel *chan);

int 
	channel_dispatch_write
		(struct ast_channel *chan, struct ast_frame *frame);

int 
	channel_dispatch_send_text
		(struct ast_channel *chan, const char *text);

int 
	channel_dispatch_send_image
		(struct ast_channel *chan, struct ast_frame *frame);

int 
	channel_dispatch_send_html
		(struct ast_channel *chan, int subclass, const char *data, int len);

struct ast_frame * 
	channel_dispatch_exception
		(struct ast_channel *chan);

enum ast_bridge_result 
	channel_dispatch_bridge
		(struct ast_channel *c0, struct ast_channel *c1, int flags, struct ast_frame **fo, struct ast_channel **rc, int timeoutms);

int 
	channel_dispatch_indicate
		(struct ast_channel *c, int condition, const void *data, size_t datalen);

int 
	channel_dispatch_fixup
		(struct ast_channel *oldchan, struct ast_channel *newchan);

int 
	channel_dispatch_setoption
		(struct ast_channel *chan, int option, void *data, int datalen);

int 
	channel_dispatch_queryoption
		(struct ast_channel *chan, int option, void *data, int *datalen);

int 
	channel_dispatch_transfer
		(struct ast_channel *chan, const char *newdest);

int 
	channel_dispatch_write_video
		(struct ast_channel *chan, struct ast_frame *frame);

struct ast_channel *
	channel_dispatch_bridged_channel
		(struct ast_channel *chan, struct ast_channel *bridge);

int 
	channel_dispatch_func_channel_read
		(struct ast_channel *chan, char *function, char *data, char *buf, size_t len);

int 
	channel_dispatch_func_channel_write
		(struct ast_channel *chan, char *function, char *data, const char *value);

struct ast_channel* 
	channel_dispatch_get_base_channel
		(struct ast_channel *chan);

int 
	channel_dispatch_set_base_channel
		(struct ast_channel *chan, struct ast_channel *base);

#ifdef __cplusplus
}
#endif


//
//	Channel base class
//
#ifdef __cplusplus
    class Channel
    {
    public:
        virtual ~Channel() {}
        virtual int send_digit_begin (char digit);
        virtual int send_digit_end (char digit, unsigned int duration);
        virtual int call (char *addr, int timeout);
        virtual int hangup ();
        virtual int answer ();
        virtual struct ast_frame * read ();
        virtual int write (struct ast_frame *frame);
        virtual int send_text (const char *text);
        virtual int send_image (struct ast_frame *frame);
        virtual int send_html (int subclass, const char *data, int len);
        virtual struct ast_frame * exception ();
        //	TODO virtual enum ast_bridge_result bridge (struct ast_channel *c0, struct ast_channel *c1, int flags, struct ast_frame **fo, struct ast_channel **rc, int timeoutms)
        virtual int indicate (int condition, const void *data, size_t datalen);
        //	TODO virtual int fixup (struct ast_channel *oldchan, struct ast_channel *newchan)
        virtual int setoption (int option, void *data, int datalen);
        virtual int queryoption (int option, void *data, int *datalen);
        virtual int transfer (const char *newdest);
        virtual int write_video (struct ast_frame *frame);
        virtual struct ast_channel * bridged_channel (struct ast_channel *bridge);
        virtual int func_channel_read (char *function, char *data, char *buf, size_t len);
        virtual int func_channel_write (char *function, char *data, const char *value);
        virtual struct ast_channel* get_base_channel ();
        virtual int set_base_channel (struct ast_channel *base);
    protected:
        struct ast_channel * _channel;
    };
#else
    typedef struct Channel Channel;
#endif

//
//	Channel device class
//
#ifdef __cplusplus
   class ChannelDevice 
    {
    public:
        ChannelDevice(const struct ast_channel_tech *tech);
        virtual ~ChannelDevice() {}
        virtual int load_config(const char *cfg) {return 1;}
        virtual struct ast_channel * request_channel(const char *type, int format, void *data, int *cause) = 0;

        virtual void release_channel(Channel*) = 0;

	    virtual int get_state(void *data) = 0;
    protected:
        const struct ast_channel_tech *_tech;
    };
#else
    typedef struct ChannelDevice ChannelDevice;
#endif

//
//	Channel device dispatchers
//
#ifdef __cplusplus
extern "C" {
#endif

	struct ast_channel *
        request_channel
            (struct ChannelDevice *dev, const char *type, int format, void *data, int *cause);

    int 
        get_device_state
            (struct ChannelDevice *dev, void *data);

#ifdef __cplusplus
}
#endif

    
#endif /*CHAN_DISPATCH*/

