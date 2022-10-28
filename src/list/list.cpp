#include <stdio.h>
#include <list_debug.h>
#include <list_func.h>

int main()
{
    LIST_CHECK_FUNC(open_list_logs());

    puts("hello world"); 
    List_t list = {};
    LIST_CTOR(list, 20);
    
    DUMP_LIST(&list);

    // list_add(&list, 4, 1488);

    // list_add(&list, 2, 228);

    // int tmp = list_find(&list, 4);
    // printf("tmp = %d\n", tmp);

    // DUMP_LIST(&list); 

    // list_sort(&list);

    // tmp = list_find(&list, 4);
    // printf("tmp = %d\n", tmp);

    DUMP_LIST(&list);
    list_del(&list, 3);
    list_del(&list, 7);
    DUMP_LIST(&list);    
    list_detor(&list);
    LIST_CHECK_FUNC(close_list_logs());
    return 0;
}