#include <stdio.h>
#include <stdlib.h>
#include <list_debug.h>
#include <assert.h>
#include <list_func.h>
#include <stack_objects.h>
#include <stack_debug.h>

int list_ctor(List_t *list, size_t capacity, const char* name_function, const char* name_file, const char* name_variable, int num_line)
{   
    stack_open_logs();

    STACK_CTOR(&list->free, 10);

    list->head = 1;
    list->tail = 0;
    list->size = 1;
    list->capacity = capacity;
    list->elements = (Elements_t*) calloc(capacity, sizeof(Elements_t));

    list->elements[0].value = 0;
    list->elements[0].prev  = list->tail;
    list->elements[0].next  = list->head;

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

    list->elements[0].prev  = list->tail;
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

[[nodiscard]]int list_add(List_t *list, size_t index, var value)
{   
    if(list->elements[index].next == -1)
    {
        list->code_of_error |= LIST_ERROR_ADD_AFTER_POISONED_INDEX;
        error_decoder(list->code_of_error);
        return -1;
    }
    
    if (list->size == list->capacity)
    {
        list_resize(list, list->capacity * 2);
    }
    
    elem tmp = 0;
    stack_pop(&list->free, &tmp);
    int tmp_next = (elem) tmp;
    
    int tmp_prev = list->elements[index].next;
    
    find_head_and_tail(list);
    
    list->elements[tmp_next].value = value;

    list_swap_next(list, index, tmp_next);
    list_swap_prev(list, tmp_next, tmp_prev);

    list->size++;
    
    find_head_and_tail(list);
    return tmp_next;
}

static int list_swap_next(List_t *list, size_t index1, size_t index2)
{
    list->elements[index2].next = list->elements[index1].next;

    list->elements[index1].next = index2;

    return 0;
}

static int list_swap_prev(List_t *list, size_t index1, size_t index2)
{   
    list->elements[index1].prev = list->elements[index2].prev;
    
    list->elements[index2].prev = index1;
    
    return 0;
}

static int find_head_and_tail(List_t *list)
{
    list->head = list->elements[0].next;

    list->tail = list->elements[0].prev;
    
    return 0;
}

int list_detor(List_t *list)
{
    list_fill_poison(list, 0, list->capacity);
    free(list->elements);
    stack_dtor(&list->free);
    return 0;
}

int list_resize(List_t *list, size_t new_capacity)
{   
    CHECK_ON_ERROR(list->capacity > MAX_CAPACITY, LIST_ERROR_CAPACITY_TOO_BIG);

    list->elements = (Elements_t *) realloc(list->elements, new_capacity * sizeof(Elements_t));

    CHECK_ON_ERROR(list->elements == NULL, LIST_ERROR_WRONG_REALLOC_IN_RESIZE);

    list_fill_poison(list, list->capacity, new_capacity);
    list->capacity = new_capacity;

    return 0;
}

int list_fill_poison(List_t *list, int start, int finish)
{
    for (int i = finish - 1; i >= start; i--)
    {
        list->elements[i].value = POISON;
        list->elements[i].next  = POISON;
        list->elements[i].prev  = POISON;
        stack_push(&list->free, i);
    }
    SHOW_ELEMENTS(list->free);

    return 0;
}

int list_del(List_t *list, int index)
{   
    CHECK_ON_ERROR(list->elements[index].next == POISON, LIST_ERROR_DEL_FROM_POISON_INDEX);

    int tmp_prev = list->elements[index].prev;
    int tmp_next = list->elements[index].next;

    list->elements[list->elements[index].prev].next = tmp_next;
    list->elements[list->elements[index].next].prev = tmp_prev;

    list_fill_poison(list, index, index + 1);
    list->size--;
    find_head_and_tail(list);
    return 0;
}

[[nodiscard]]int list_find(List *list, int logical_index)
{

    CHECK_ON_ERROR(logical_index >= list->capacity, LIST_ERROR_LOGIC_INDEX_GREATER_CAPACITY);

    int counter = 0;

    while (counter++ < list->capacity)
    {
        if (list->elements[counter].prev == 0)
        {
            break;
        }
    }

    printf("counter = %d\n", counter);

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
    Elements_t *sorted_elements = (Elements_t*)calloc(list->capacity, sizeof(Elements_t));

    int jumper = list->head;

    int counter = 1;
    while(jumper !=0)
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
    clean_free_stack(&list->free);
    
    list->elements = sorted_elements;
    
    list_fill_poison(list, counter, list->capacity);

    find_head_and_tail(list);

    list->elements[list->tail].next = 0;

    return 0;
}

int clean_free_stack(Stack *stk)
{
    elem tmp = 0;
    while (stk->size > 0)
    {
        stack_pop(stk, &tmp);
    }
    
    return 0;
}
