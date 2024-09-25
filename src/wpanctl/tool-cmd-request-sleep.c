// #if HAVE_CONFIG_H
#include <config.h>
// #endif
#include <getopt.h>
#include <stdio.h>
#include <stdarg.h>
#include "tool-cmd-request-sleep.h"

#define BLUE "\033[0;34m"
#define DEFAULT "\033[0;33m"

const char request_sleep_cmd_syntax[] = "[args]";

void logging(const char *func_name, int line_num, const char *format, ...)
{
    printf(BLUE);

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

    LOG("%d", optind);
}