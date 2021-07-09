#ifndef LOGGING_H__
#define LOGGING_H__


#define LOG_LEVEL_NONE    (0)
#define LOG_LEVEL_ERROR   (1)
#define LOG_LEVEL_WARNING (2)
#define LOG_LEVEL_INFO    (3)
#define LOG_LEVEL_DEBUG   (4)
#define LOG_LEVEL_VERBOSE (5)


/* Our default log level is optionally set in the logging config file. If not
 * defined, we're relying on the implicit value being 0. */
#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_LEVEL_DEFAULT
#endif


#if LOG_LEVEL >= LOG_LEVEL_ERROR
#define LOG_ERROR(...) do {                     \
        logging_log(LOG_LEVEL_ERROR,            \
                    LOGGING_FILE, __LINE__,     \
                    __VA_ARGS__);               \
    } while(0)
#else
#define LOG_ERROR(...)
#endif

#if LOG_LEVEL >= LOG_LEVEL_WARNING
#define LOG_WARNING(...) do {                   \
        logging_log(LOG_LEVEL_WARNING,          \
                    LOGGING_FILE, __LINE__,     \
                    __VA_ARGS__);               \
    } while(0)
#else
#define LOG_WARNING(...)
#endif

#if LOG_LEVEL >= LOG_LEVEL_INFO
#define LOG_INFO(...) do {                      \
        logging_log(LOG_LEVEL_INFO,             \
                    LOGGING_FILE, __LINE__,     \
                    __VA_ARGS__);               \
    } while(0)
#else
#define LOG_INFO(...)
#endif

#if LOG_LEVEL >= LOG_LEVEL_DEBUG
#define LOG_DEBUG(...) do {                     \
        logging_log(LOG_LEVEL_DEBUG,            \
                    LOGGING_FILE, __LINE__,     \
                    __VA_ARGS__);               \
    } while(0)
#else
#define LOG_DEBUG(...)
#endif

#if LOG_LEVEL >= LOG_LEVEL_VERBOSE
#define LOG_VERBOSE(...) do {                   \
        logging_log(LOG_LEVEL_VERBOSE,          \
                    LOGGING_FILE, __LINE__,     \
                    __VA_ARGS__);               \
    } while(0)
#else
#define LOG_VERBOSE(...)
#endif


typedef struct logging_init_args_t
{
    void (*handler)(const char *message);
    unsigned long (*get_time)(void);
} logging_init_args_t;


extern void
logging_init(logging_init_args_t *init_args);


extern void
logging_log(int level,
            const char *file, int line,
            const char *format, ...);


#endif
