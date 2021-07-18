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
    if (!condition)
    {
        PANIC("assert failed\n");
    }
}


#endif
