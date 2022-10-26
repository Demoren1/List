#include <stdio.h>
#include <stdlib.h>
#include <debug.h>
#include <assert.h>
#include <list_func.h>

int list_ctor(List_t *list, size_t capacity, const char* name_function, const char* name_file, const char* name_variable, int num_line)
{
    list->head = 1;
    list->tail = 0;
    list->size = 1;
    list->capacity = capacity;
    list->elements = (Elements_t*) calloc(capacity, sizeof(Elements_t));

    list->elements[0].value = 0;
    list->elements[0].prev  = 0;
    list->elements[0].next  = 0;

    int i = 1;
    for (i = 1; i < capacity / 2; i++)
    {
        list->elements[i].value = 10 * i;
        list->elements[i].next  = i + 1;
        list->elements[i].prev  = i - 1;
        list->tail++;
        list->size++;
    }
    list->elements[i-1].next = 0;

    list_fill_poison(list, list->capacity / 2, list->capacity);

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
    ASSERT_OK(list->elements[index].next == -1, LIST_ERROR_ADD_AFTER_POISONED_INDEX);

    if (list->size + 1 == list->capacity)
    {
        list_resize(list, list->capacity * 2);
    }
        
    int tmp_next = find_index_for_next(list);
    int tmp_prev = find_index_for_prev(list, index);
    
    find_new_tail(list, index, tmp_next);
    
    list->elements[tmp_next].value = value;

    list_swap_next(list, index, tmp_next);
    list_swap_prev(list, tmp_next, tmp_prev);

    list->size++;

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
    if (index1 == list->tail)
    {
        list->elements[index1].prev = index2;
    }

    else
    {
        list->elements[index1].prev = list->elements[index2].prev;
        list->elements[index2].prev = index1;
    }
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
    if (index == list->tail)
    {
        return index;
    }
    
    while(list->elements[tmp_prev].prev != index)
    {
        tmp_prev++;
        // DBG;
    }

    return tmp_prev;
}

int find_new_tail(List_t *list, int index, int new_index)
{
    if (index == list->tail)
    {
        list->tail = new_index;
    }
    
    return 0;
}

int list_detor(List_t *list)
{
    free(list->elements);
    
    return 0;
}

int list_resize(List_t *list, size_t new_capacity)
{   
    //todo write validator

    assert(list->capacity < MAX_CAPACITY);

    list->elements = (Elements_t *) realloc(list->elements, new_capacity * sizeof(Elements_t));
    list_fill_poison(list, list->capacity, new_capacity);
    list->capacity = new_capacity;

    return 0;
}

int list_fill_poison(List_t *list, int start, int finish)
{
    for (int i = start; i < finish; i++)
    {
        list->elements[i].value = POISON;
        list->elements[i].next  = POISON;
        list->elements[i].prev  = POISON;
    }

    return 0;
}

int list_del(List_t *list, int index)
{   
    ASSERT_OK(list->elements[index].next == POISON, LIST_ERROR_DEL_FROM_POISON_INDEX);


    if (index == list->tail)
    {
        list->tail = list->elements[index].prev;
        list->elements[list->elements[index].prev].next = 0;

        list_fill_poison(list, index, index + 1);
        return 0;
    }

    if (index == list->head)
    {
        list->head = list->elements[index].next;
        list->elements[list->elements[index].next].prev = 0;
        
        list_fill_poison(list, index, index + 1);
        return 0;
    }

    int tmp_prev = list->elements[index].prev;
    int tmp_next = list->elements[index].next;

    list->elements[list->elements[index].prev].next = tmp_next;
    list->elements[list->elements[index].next].prev = tmp_prev;

    list_fill_poison(list, index, index + 1);

    return 0;
}




