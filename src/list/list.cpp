#include <stdio.h>
#include <list_debug.h>
#include <list_func.h>

int main()
{
    LIST_CHECK_FUNC(open_list_logs());

    List_t list = {};
    list_ctor(list, 10);
    
    // printf("in main free head = %d, free tail = %d\n", list.free_head, list.free_tail);
    // printf("is sorted = %d\n", list.is_sorted);
    DUMP_LIST(&list);

    for (int i = 1; i < 6; i ++)
    {
        list_push(&list, i*10);
    }
    // printf("is sorted = %d\n", list.is_sorted);
    
    // list_insert(&list, 8, 25);
    list_insert(&list, 3, 25, AFTER);
    // printf("is sorted = %d\n", list.is_sorted);

    // list_insert(&list, 3, 25);

    DUMP_LIST(&list); 


//    list_insert(&list, 3, 25);
    // list_insert(&list, 3, 25);
    // list_insert(&list, 3, 25);
    // list_insert(&list, 3, 25);



    // DUMP_LIST(&list); 

    // list_pop(&list);

    // list_erase(&list, 7);

    // DUMP_LIST(&list); 

    list_sort(&list);

    DUMP_LIST(&list); 

    // int tmp = list_find(&list, 4);
    // printf("tmp = %d\n", tmp);
    // DUMP_LIST(&list);

    // list_insert(&list, 1, 1488);
    // DUMP_LIST(&list);
    // list_erase(&list, 3);
    // list_erase(&list, 7);
    // DUMP_LIST(&list);  

    list_dtor(&list);
    LIST_CHECK_FUNC(close_list_logs());
    return 0;
}