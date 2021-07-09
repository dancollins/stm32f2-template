#include "logging.h"

#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>


static logging_init_args_t log;


static const char *
get_level_str(int level)
{
    switch (level)
    {
    case LOG_LEVEL_ERROR:
        return "ERR";

    case LOG_LEVEL_WARNING:
        return "WRN";

    case LOG_LEVEL_INFO:
        return "INF";

    case LOG_LEVEL_DEBUG:
        return "DBG";

    case LOG_LEVEL_VERBOSE:
        return "VRB";

    default:
        return "XXX";
    }
}


void
logging_init(logging_init_args_t *init_args)
{
    memcpy(&log, init_args, sizeof(log));
}


void
logging_log(int level,
            const char *file, int line,
            const char *format, ...)
{
    static char buffer[256];
    va_list args;
    int len;

    /* Check that logging is enabled. */
    if (level <= LOG_LEVEL_NONE)
        return;

    /* Prepend our log format. */
    len = snprintf(buffer, sizeof(buffer), "%s %lu %s:%d ",
                   get_level_str(level), log.get_time(), file, line);

    va_start(args, format);
    vsnprintf(buffer + len, sizeof(buffer) - len, format, args);
    va_end(args);

    log.handler(buffer);
}
