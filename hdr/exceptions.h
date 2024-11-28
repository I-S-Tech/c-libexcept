/************
 *
 *    #
 *      #
 *  # # #
 *
 ************/

#ifndef INCLUDED_LIB_EXCEPTIONS_H
    #define INCLUDED_LIB_EXCEPTIONS_H

    #include <setjmp.h>
    #include <stdlib.h>
    #include <unistd.h>

#if defined(__GNUC__)
    #define __FUNC__ __PRETTY_FUNCTION__
#elif defined(_MSC_VER)
    #define __FUNC__ __FUNCSIG__
#else
    #define __FUNC__ __func__
#endif

    #define UNUSED __attribute__((unused))

typedef struct exception {
    jmp_buf env;
    struct exception* next;
} exception_t;

static UNUSED exception_t *ctx = NULL;

    #define PERR disperror(__FILE__, __LINE__, __FUNC__); abort();

    #define TRY do {exception_t e; e.next = ctx; ctx = &e; if (setjmp(e.env) == 0) {
    #define CATCH } else {
    #define END_TRY } ctx = ctx->next; } while (0)

    #define THROW() do {if (ctx == NULL) {PERR} longjmp(ctx->env, 1);} while (0)

void disperror(const char* file, unsigned line, const char* func);

#endif