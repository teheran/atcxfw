#ifndef CHAN_ABC
#define CHAN_ABC

#include "chan_dispatch.h"

// 
//	Device declaration
//
#ifdef __cplusplus
    class ChannelDevice_Echo : public ChannelDevice
    {
    public:
        ChannelDevice_Echo(const struct ast_channel_tech *tech)
            : ChannelDevice(tech) {/* */}

        struct ast_channel * request_channel(const char *type, int format, void *data, int *cause);
//        void release_channel(Channel*);
        int get_state(void *data);
    private:

    };
#else
    typedef struct ChannelDevice_Echo ChannelDevice_Echo;
#endif

//
//	Channel declaration
//
#ifdef __cplusplus
    class Channel_Echo : public Channel
    {
    public:
        Channel_Echo(const struct ast_channel_tech *tech);
        ~Channel_Echo();

        struct ast_frame * read ();
        int write (struct ast_frame *frame);
        int call (char *addr, int timeout);
        int hangup ();
        int indicate (int condition, const void *data, size_t datalen);
    private:
        int _pipefds[2];
    };
#else
    typedef struct Channel_Echo Channel_Echo;
#endif

#ifdef __cplusplus
extern "C" {
#endif

    int 
        initialize
            (const struct ast_channel_tech *tech , const char *cfg);

    int 
        uninitialize
	    	(void);

#ifdef __cplusplus
}
#endif

#endif /*CHAN_ABC*/


