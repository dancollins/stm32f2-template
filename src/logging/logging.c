/*
 * Copyright 2021 Dan Collins
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
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
