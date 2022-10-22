#include <stdio.h>
#include <debug.h>
#include <list_func.h>

int main()
{
    open_list_logs();

    puts("hello world"); 
    List_t list = {};
    LIST_CTOR(list, NUM_OF_ELEMENTS);

    DUMP_LIST(&list);
    
    printf("%d\n", list_add(&list, 3, 228));

    DUMP_LIST(&list);

    close_list_logs();
    return 0;
}