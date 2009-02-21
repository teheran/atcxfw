#include "asterisk.h"

ASTERISK_FILE_VERSION(__FILE__, "$Revision: $")

#include "asterisk/module.h"
#include "echo.h"

static const struct ast_channel_tech tech = {
	.type         = "ABC",
	.description  = "ABC Channel driver",
	.capabilities = AST_FORMAT_ULAW | AST_FORMAT_ALAW,
	.requester    = device_dispatch_request,
	.devicestate  = device_dispatch_devicestate,
	.call         = channel_dispatch_call,
	.hangup       = channel_dispatch_hangup,
	.read         = channel_dispatch_read,
	.write        = channel_dispatch_write,
	.indicate     = channel_dispatch_indicate,
};

static int load_module(void)
{
//    assert(NULL == device);

    return initialize(&tech, NULL) 
            ? AST_MODULE_LOAD_SUCCESS 
            : AST_MODULE_LOAD_FAILURE;
}

static int unload_module(void)
{
    return uninitialize() 
            ? AST_MODULE_LOAD_FAILURE
            : AST_MODULE_LOAD_SUCCESS;
}

AST_MODULE_INFO(ASTERISK_GPL_KEY, AST_MODFLAG_DEFAULT, "Channel implements echo as simple as possible",
                .load = load_module,
                .unload = unload_module,
               ); 

