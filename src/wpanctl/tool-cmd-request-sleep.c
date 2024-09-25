// #if HAVE_CONFIG_H
#include <config.h>
// #endif
#include <getopt.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "wpan-dbus-v1.h"
#include "tool-cmd-request-sleep.h"

#define BLUE "\033[0;34m"
#define YELLOW "\033[0;33m"
#define DEFAULT "\033[0;33m"

const char request_sleep_cmd_syntax[] = "[args]";

void logging(const char *func_name, int line_num, const char *format, ...)
{
    printf(YELLOW);
    printf("[LOG] %s.%d: ", func_name, line_num);
    va_list args;
    va_start(args, format);
    vprintf(format, args);  // Print the formatted message
    va_end(args);

    printf(DEFAULT "\n");
}

#define LOG(...) logging(__func__, __LINE__, __VA_ARGS__)

int tool_cmd_request_sleep(int argc, char *argv[])
{
    int c;
    int timeout = REQUEST_SLEEP_TIMEOUT;
    DBusConnection *connection = NULL;
    DBusMessage *message = NULL;
    DBusMessage *reply = NULL;
    DBusError error;
    DBusMessageIter iter;
    DBusMessageIter list_iter;
    char object_path[DBUS_MAXIMUM_NAME_LENGTH + 1] = {0};
    char interface_dbus_name[DBUS_MAXIMUM_NAME_LENGTH + 1] = {0};
    int ret;

    static const struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"timeout", required_argument, 0, 't'},
        {0, 0, 0, 0}
    };
    
    while (1)
    {
        int option_index = 0;
        c = getopt_long(argc, argv, "ht:", long_options, &option_index);
        
        // Detect the end of the options
        if (c == -1)
        {
            break;
        }

        switch (c) 
        {
            case 'h':
                break;
            case 't':
                timeout = strtol(optarg, NULL, 0);
                break;
            default:
                break;
        } 
    }

    if (optind < argc)
    {
        LOG("%s: error: Unexpected extra argument: \"%s\"",
			argv[0], argv[optind]);
        goto bail;
    }

    if (strlen(gInterfaceName) == 0)
    {
        LOG("%s: error: No WPAN interface set (use the `cd` command, or the `-I` argument for `wpanctl`).\n",
            argv[0]);
        goto bail;
    }    

    dbus_error_init(&error);
    connection = dbus_bus_get(DBUS_BUS_SYSTEM, &error);

    if (connection < 0)
    {
        LOG("%s", error.message);
        goto bail;
    }

    ret = lookup_dbus_name_from_interface(interface_dbus_name, gInterfaceName);
    if (ret != 0) 
    {
        LOG("Failed to look up dbus name from interface");
        goto bail;
    }

    snprintf(object_path, \
            sizeof(object_path), \
            "%s/%s", \
            WPANTUND_DBUS_PATH, \
            gInterfaceName);

    message = dbus_message_new_method_call(interface_dbus_name, \
                                            object_path, \
                                            WPANTUND_DBUS_APIv1_INTERFACE,
                                            WPANTUND_IF_CMD_REQUEST_SLEEP);

    LOG("Sending request-sleep command . . .");

    // Sends a message and blocks a certain time period while waiting for a reply
    // If a normal reply is received, it is returned
    // If it is not received, #NULL is returned and the error is DBUS_ERROR_NO_REPLY
    reply = dbus_connection_send_with_reply_and_block(connection, \
                                                        message, \
                                                        timeout, \
                                                        &error);
    if (!reply)
    {
        LOG("%s: error: %s", argv[0], error.message);
        goto bail;
    }

    dbus_message_get_args(reply, \
                        &error, \
                        DBUS_TYPE_INT32, 
                        &ret,
                        DBUS_TYPE_INVALID);
    if (ret)
    {
        LOG("%s failed with error %d. %s\n", argv[0], ret, wpantund_status_to_cstr(ret));
        print_error_diagnosis(ret);
    }

bail:
    if (connection)
        dbus_connection_unref(connection);
    
    if (message)
        dbus_message_unref(message);   

    if (reply)
		dbus_message_unref(reply); 
    
    dbus_error_free(&error);

    return ret;
}