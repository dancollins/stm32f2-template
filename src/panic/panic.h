#ifndef PANIC_H__
#define PANIC_H__


#define PANIC(...)                              \
    do {                                        \
        LOG_ERROR("\n\n*** PANIC ***\n\n");     \
        LOG_ERROR("    " __VA_ARGS__);          \
        panic(__FILE__, __LINE__);              \
    } while (0)


/**
 * Invoked when a panic occurs. Must be supplied by the application at
 * compile-time.
 *
 * @param file the file where the panic occured.
 * @param line the line in the file where the panic occured.
 */
extern void
panic(const char *file, int line) __attribute__((noreturn));


static inline void
assert(bool condition)
{
    if (condition)
    {
        PANIC("assert failed\n");
    }
}


#endif
