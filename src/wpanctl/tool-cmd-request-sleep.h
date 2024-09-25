#ifndef TOOL_CMD_REQUEST_SLEEP_H
#define TOOL_CMD_REQUEST_SLEEP_H

#include "wpanctl-utils.h"

#define REQUEST_SLEEP_TIMEOUT 10 * 1000

int tool_cmd_request_sleep(int argc, char *argv[]);

#endif