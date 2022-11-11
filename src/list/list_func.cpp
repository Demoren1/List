#include <stdio.h>
#include <stdlib.h>
#include <list_func.h>
#include <list_debug.h>
#include <assert.h>

static int list_swap_next(List_t *list, size_t index1, size_t index2); 

static int list_swap_prev(List_t *list, size_t index1, size_t index2);

static int find_head_and_tail(List_t *list);

static int free_push(List_t *list, int start, int finish);  

static int free_pop(List_t *list);

static int free_update(List_t *list);

static int bind_nodes(List_t *list, int index);

static int list_resize(List_t *list, size_t new_capacity);

int _list_ctor(List_t *list, size_t capacity, const char* name_function, const char* name_file, const char* name_variable, int num_line)
{   
    SOFT_ASS(list == NULL);
    CHECK_ON_ERROR(capacity <= 0, LIST_ERROR_CAPACITY_TOO_FEW);

    list->head = 0;
    list->tail = 0;
    list->size = 1;
    list->is_sorted = 1;
    list->free_head = POISON;
    list->free_tail = POISON;
    list->capacity = capacity;
    list->elements = (Element_t*) calloc(capacity, sizeof(Element_t));
    
    CHECK_ON_ERROR(list->elements == NULL, LIST_ERROR_CANT_CALLOC);

    list->elements[0].value = 0;
    list->elements[0].prev  = 0;
    list->elements[0].next  = 0;

    free_push(list, 1, list->capacity);
    list_dump_info_ctor(list, name_function, name_file, name_variable, num_line);
    return 0;
}

int list_dump_info_ctor(List *list, const char* name_function, const char* name_file, const char* name_variable, int num_line)
{   
    SOFT_ASS(list == NULL);

    list->dump_info.name_of_func     = name_function;
    list->dump_info.name_of_file     = name_file;   
    list->dump_info.name_of_variable = name_variable + 1;
    list->dump_info.num_of_line      = num_line;

    return 0;
}

int list_insert(List_t *list, size_t index, var value, Positions pos)
{   
    SOFT_ASS(list == NULL);
    SOFT_ASS(index < 0);
    CHECK_ON_ERROR(list->elements[index].prev == POISON, LIST_ERROR_ADD_AFTER_POISONED_INDEX);
    CHECK_ON_ERROR(index != list->elements[list->elements[index].prev].next, LIST_ERROR_PREV_NOT_EQ_NEXT);
    list_check(list);
    
    if (list->size + 1 == list->capacity)
    {
        list_resize(list, list->capacity * 2);
    }
    
    if (index != list->tail)
        list->is_sorted = 0;

    if ((index > 0) && (pos == BEFORE))
    {
        index--;
    }
    else if ((index <= 0) && (pos == BEFORE))
    {
        CHECK_ON_ERROR(1, LIST_ERROR_ADD_BEFORE_ZERO_INDEX);
    }

    int tmp_next = free_pop(list);
    int tmp_prev = list->elements[index].next;
    
    list->elements[tmp_next].value = value;

    list_swap_next(list, index, tmp_next);              
    list_swap_prev(list, tmp_next, tmp_prev);

    list->size++;
    find_head_and_tail(list);
    return tmp_next;
}

int list_push(List_t *list, var value)
{
    return list_insert(list, list->tail, value, AFTER);
}

static int list_swap_next(List_t *list, size_t index1, size_t index2)
{
    SOFT_ASS(list == NULL);

    list->elements[index2].next = list->elements[index1].next;
    list->elements[index1].next = index2;

    return 0;
}

static int list_swap_prev(List_t *list, size_t index1, size_t index2)
{   
    SOFT_ASS(list == NULL);

    list->elements[index1].prev = list->elements[index2].prev;
    list->elements[index2].prev = index1;
    
    return 0;
}

static int find_head_and_tail(List_t *list)
{
    SOFT_ASS(list == NULL);

    list->head = list->elements[0].next;
    list->tail = list->elements[0].prev;
    
    return 0;
}

int list_dtor(List_t *list)
{
    SOFT_ASS(list == NULL);

    free_push(list, 0, list->capacity);
    if (list->elements != NULL)
    {
        free(list->elements);
        list->elements = NULL;
    }
    return 0;
}

int list_resize(List_t *list, size_t new_capacity)
{   
    SOFT_ASS(list == NULL);

    list_check(list);
    CHECK_ON_ERROR(list->capacity > MAX_CAPACITY, LIST_ERROR_CAPACITY_TOO_BIG);
    
    Element_t *test_realloc = (Element_t *) realloc(list->elements, new_capacity * sizeof(Element_t));
    CHECK_ON_ERROR(test_realloc == NULL, LIST_ERROR_CANT_REALLOC);

    list->elements = test_realloc;
    CHECK_ON_ERROR(list->elements == NULL, LIST_ERROR_WRONG_REALLOC_IN_RESIZE);

    free_push(list, list->capacity - 1, new_capacity);
    
    list->capacity = new_capacity;

    return 0;
}

int free_push(List_t *list, int start, int finish)
{   
    SOFT_ASS(list == NULL);

    list_check(list);

    if (POISON == list->free_head)
    {
        list->free_head = start;
    }

    list->elements[list->free_tail].next = start;

    for (int i = start; i < finish - 1; i++)
    {
        list->elements[i].value = POISON;
        list->elements[i].prev = POISON;
        list->elements[i].next  = i + 1;
    }

    list->elements[finish - 1].next = POISON;
    list->elements[finish - 1].prev = POISON;
    list->elements[finish - 1].value = POISON;

    list->free_tail = finish - 1;

    return 0;
}

var list_erase(List_t *list, int index)
{   
    SOFT_ASS(list == NULL);
    CHECK_ON_ERROR(list->elements[index].next == POISON, LIST_ERROR_DEL_FROM_POISON_INDEX);
    CHECK_ON_ERROR(index != list->elements[list->elements[index].prev].next, LIST_ERROR_PREV_NOT_EQ_NEXT);  
    list_check(list);

    if (index != list->head)
        list->is_sorted = 0;

    var value = list->elements[index].value;

    bind_nodes(list, index);

    free_push(list, index, index + 1);   

    list->size--;
    find_head_and_tail(list);
    return value;
}

int bind_nodes(List_t *list, int index)
{
    SOFT_ASS(list == NULL);

    int tmp_prev = list->elements[index].prev;
    int tmp_next = list->elements[index].next;

    list->elements[list->elements[index].prev].next = tmp_next;
    list->elements[list->elements[index].next].prev = tmp_prev;

    return 0;
}

var list_pop(List_t *list)
{
    SOFT_ASS(list == NULL);
    return list_erase(list, (list)->tail);
}

[[nodiscard]]int list_find(List *list, int logical_index)
{
    SOFT_ASS(list == NULL);
    SOFT_ASS(logical_index < 0);

    list_check(list);
    CHECK_ON_ERROR(logical_index >= list->capacity, LIST_ERROR_LOGIC_INDEX_GREATER_CAPACITY);

    int counter = 0;
    while (counter++ < list->capacity)
    {
        if (list->elements[counter].prev == 0)
        {
            break;
        }
    }

    int jumper = counter;
    int jump_counter = 1;
    while(jumper != 0)
    {
        if (jump_counter == logical_index)
        {   
            return jumper;
        }

        jumper = list->elements[jumper].next;
        jump_counter++;
        CHECK_ON_ERROR(jumper == -1, LIST_ERROR_JUMP_ON_POISON);
    }

    return -1;
}

int list_sort(List_t *list)
{
    SOFT_ASS(list == NULL);
    list_check(list);
    Element_t *sorted_elements = (Element_t*)calloc(list->capacity, sizeof(Element_t));  
    CHECK_ON_ERROR(sorted_elements == NULL, LIST_ERROR_CANT_CALLOC_FOR_SORT);
    
    list->is_sorted = 1;
    int jumper = list->head;                                                                
    
    int counter = 1;
    while(jumper != 0)
    {   
        sorted_elements[counter].value = list->elements[jumper].value;
        sorted_elements[counter].next  = counter + 1;
        sorted_elements[counter].prev  = counter - 1;

        jumper = list->elements[jumper].next;
        counter++;
    }

    sorted_elements[0].next  = 1;
    sorted_elements[0].prev  = counter - 1;
    sorted_elements[0].value = 0; 

    free(list->elements);
    list->elements = sorted_elements;

    free_update(list);
    find_head_and_tail(list);
    list->is_sorted = 1;

    list->elements[list->tail].next = 0;

    return 0;
}

int free_pop(List_t *list)
{
    SOFT_ASS(list == NULL);

    int tmp = list->free_head;
    list->free_head = list->elements[tmp].next;

    return tmp;
}

int free_update(List_t *list)
{
    SOFT_ASS(list == NULL);

    list->free_head = POISON;
    list->free_tail = POISON;

    free_push(list, list->size, list->capacity);

    return 1;
}