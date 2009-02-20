#ifndef CHAN_ABC
#define CHAN_ABC

#include "ABC/chan_dispatch.h"

// 
//	Device declaration
//
#ifdef __cplusplus
    class ChannelDevice_ABC : public ChannelDevice
    {
    public:
        ChannelDevice_ABC(const struct ast_channel_tech *tech)
            : ChannelDevice(tech) {/* */}

        struct ast_channel * request_channel(const char *type, int format, void *data, int *cause);
        void release_channel(Channel*);
        int get_state(void *data);
    private:

    };
#else
    typedef struct ChannelDevice_ABC ChannelDevice_ABC;
#endif

//
//	Channel declaration
//
#ifdef __cplusplus
    class Channel_ABC : public Channel
    {
    public:
        ~Channel_ABC();
        int init(const struct ast_channel_tech *, const char *type, int format, void *data);

        struct ast_frame * read ();
        int write (struct ast_frame *frame);
        int call (char *addr, int timeout);
        int hangup ();
        int indicate (int condition, const void *data, size_t datalen);
    private:
        int _pipefds[2];
    };
#else
    typedef struct Channel_ABC Channel_ABC;
#endif

#ifdef __cplusplus
extern "C" {
#endif

    int 
        create_device
            (ChannelDevice** device, const struct ast_channel_tech *tech , const char *cfg);

	void 
	    abc_device_free
	    	(struct ChannelDevice *dev);

#ifdef __cplusplus
}
#endif

#endif /*CHAN_ABC*/


