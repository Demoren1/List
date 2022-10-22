#include <stdio.h>
#include <stdlib.h>
#include <debug.h>
#include <list_func.h>

int list_ctor(List_t *list, size_t capacity, const char* name_function, const char* name_file, const char* name_variable, int num_line)
{
    list->head = 1;
    list->tail = 1;

    list->elements[0].value = 0;
    list->elements[0].prev  = 0;
    list->elements[0].next  = 0;
    int i = 1;
    for (i = 1; i < capacity / 2; i++)
    {
        list->elements[i].value = 2 * i + 1;
        // printf("value  = %d \n", list->elements[i].value);
        list->elements[i].next  = i + 1;
        list->elements[i].prev  = i - 1;
        list->tail++;

    }

    list->elements[i-1].next = 0;

    for (int i = capacity / 2; i < capacity; i++)
    {
        list->elements[i].value = -1;
        list->elements[i].next  = -1;
        list->elements[i].prev  = -1;
    }

    list_dump_info_ctor(list, name_function, name_file, name_variable, num_line);

    return 0;
}

int list_dump_info_ctor(List *list, const char* name_function, const char* name_file, const char* name_variable, int num_line)
{   

    list->dump_info.name_of_func     = name_function;
    list->dump_info.name_of_file     = name_file;   
    list->dump_info.name_of_variable = name_variable + 1;
    list->dump_info.num_of_str       = num_line;

    return 0;
}

int list_add(List_t *list, size_t index, var value)
{
    int tmp_next = find_index_for_next(list);
    int tmp_prev = find_index_for_prev(list, index);

    list->elements[tmp_next].value = value;

    list_swap_next(list, index, tmp_next);
    list_swap_prev(list, tmp_next, tmp_prev);

    list->tail++;

    return tmp_next;
}

int list_swap_next(List_t *list, size_t index1, size_t index2)
{
    list->elements[index2].next = list->elements[index1].next;

    list->elements[index1].next = index2;

    return 0;
}

int list_swap_prev(List_t *list, size_t index1, size_t index2)
{
    list->elements[index1].prev = list->elements[index2].prev;
    list->elements[index2].prev = index1;
    
    return 0;
}

int find_index_for_next(List_t *list)
{
    int tmp_next = 1;

    while(list->elements[tmp_next].next != -1)
    {
        tmp_next++;
    }

    return tmp_next;
}

int find_index_for_prev(List_t *list, size_t index)
{   
    int tmp_prev = 1;

    while(list->elements[tmp_prev].prev != index)
    {
        tmp_prev++;
    }

    return tmp_prev;
}
