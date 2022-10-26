#include <stdio.h>
#include <debug.h>
#include <list_func.h>

int main()
{
    CHECK_FUNC(open_list_logs());

    puts("hello world"); 
    List_t list = {};
    LIST_CTOR(list, 10);
    
    DUMP_LIST(&list);
    
    list_del(&list, 1);
    DUMP_LIST(&list);
    
    list_detor(&list);
    CHECK_FUNC(close_list_logs());
    return 0;
}