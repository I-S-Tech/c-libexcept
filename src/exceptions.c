#include "exceptions.h"

inline static size_t len_str(const char* str)
{
    size_t i = 0;

    for (; str[i]; ++i);
    return i;
}

static void dispuerr(unsigned line)
{
    unsigned bfore = line / 10;
    unsigned after = line % 10;
    UNUSED int _;

    if (bfore)
        dispuerr(bfore);
    _ = write(2, &(char){after + '0'}, 1);
}

void disperror(const char* file, unsigned line, const char* func)
{
    UNUSED int _;
    _ = write(2, "Unhandled exception at ", 23);
    _ = write(2, file, len_str(file));
    _ = write(2, ":", 1);
    dispuerr(line);
    _ = write(2, " (in ", 5);
    _ = write(2, func, len_str(func));
    _ = write(2, ").\n", 3);
}