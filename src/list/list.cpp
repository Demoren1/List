#include <stdio.h>
#include <list_debug.h>
#include <list_func.h>

int main()
{
    LIST_CHECK_FUNC(open_list_logs());

    List_t list = {};
    LIST_CTOR(list, 10);
    
    // printf("in main free head = %d, free tail = %d\n", list.free_head, list.free_tail);
    // printf("is sorted = %d\n", list.is_sorted);
    DUMP_LIST(&list);

    for (int i = 1; i < 6; i ++)
    {
        PUSH_IN_LIST(&list, i*10);
    }
    // printf("is sorted = %d\n", list.is_sorted);
    
    // list_add(&list, 8, 25);
    list_add(&list, 3, 25);
    // printf("is sorted = %d\n", list.is_sorted);

    // list_add(&list, 3, 25);

    DUMP_LIST(&list); 


//    list_add(&list, 3, 25);
    // list_add(&list, 3, 25);
    // list_add(&list, 3, 25);
    // list_add(&list, 3, 25);



    // DUMP_LIST(&list); 

    // POP_FROM_LIST(&list);

    // list_del(&list, 7);

    // DUMP_LIST(&list); 

    list_sort(&list);

    DUMP_LIST(&list); 

    // int tmp = list_find(&list, 4);
    // printf("tmp = %d\n", tmp);
    // DUMP_LIST(&list);

    // list_add(&list, 1, 1488);
    // DUMP_LIST(&list);
    // list_del(&list, 3);
    // list_del(&list, 7);
    // DUMP_LIST(&list);  

    list_detor(&list);
    LIST_CHECK_FUNC(close_list_logs());
    return 0;
}