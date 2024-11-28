#include "exceptions.h"
#include <stdio.h>

void very_dangerous_functions()
{
    printf("I might or might not break the system !!!\n");
    if (!(rand() % 10))
        THROW();
    printf("U lucky\n");
}

void even_more_dangerous_function()
{
    printf("I'me pure evil\n");
    THROW();
}

void slightly_more_evil_function()
{
    printf("The function even_more_dangerous_function doesn't seem that bad :)\n");
    even_more_dangerous_function();
}

int main()
{
    TRY {
        very_dangerous_functions();
    } CATCH {
        printf("Oh no, our system is broken !!!\n");
    } END_TRY;

    slightly_more_evil_function();
}