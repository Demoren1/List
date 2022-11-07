#include <stdio.h>
#include <stdlib.h>
#include <list_debug.h>
#include <assert.h>
#include <list_func.h>

static int list_swap_next(List_t *list, size_t index1, size_t index2); 

static int list_swap_prev(List_t *list, size_t index1, size_t index2);

static int find_head_and_tail(List_t *list);

// TODO: free_push?
static int list_add_to_free(List_t *list, int start, int finish);  

static size_t list_check(List_t *list);          

static int free_pop(List_t *list);

static int free_update(List_t *list);

int list_ctor(List_t *list, size_t capacity, const char* name_function, const char* name_file, const char* name_variable, int num_line)
{   
    CHECK_ON_ERROR(capacity <= 0, LIST_ERROR_CAPACITY_TOO_FEW);

    list->head = 0;
    list->tail = 0;
    list->size = 1;
    list->free_head = POISON;
    list->free_tail = POISON;
    list->capacity = capacity;
    list->elements = (Elements_t*) calloc(capacity, sizeof(Elements_t)); // TODO: Return value check

    list->elements[0].value = 0;
    list->elements[0].prev  = 0;
    list->elements[0].next  = 0;

    list_add_to_free(list, 1, list->capacity);
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

[[nodiscard]]int list_add(List_t *list, size_t index, var value)
{   
    // TODO: Verifier that at least checks correct connections
    CHECK_ON_ERROR(index != list->elements[list->elements[index].prev].next, LIST_ERROR_PREV_NOT_EQ_NEXT);
    CHECK_ON_ERROR(list->elements[index].next == POISON, LIST_ERROR_ADD_AFTER_POISONED_INDEX);
    
    if (list->size + 1 == list->capacity)
    {
        list_resize(list, list->capacity * 2);
    }

    int tmp_next = free_pop(list);
    int tmp_prev = list->elements[index].next;
    
    list->elements[tmp_next].value = value;

    list_swap_next(list, index, tmp_next);
    // TODO: Confusing names: tmp_next becomes prev for tmp_prev
    list_swap_prev(list, tmp_next, tmp_prev);

    list->size++;
    find_head_and_tail(list); // TODO: Do you need to update them every time?
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

// TODO: Usually function names are paired like ctor-dtor
// TODO: Fill with poison list and list structure
int list_detor(List_t *list)
{
    list_add_to_free(list, 0, list->capacity);
    free(list->elements); // TODO: Double list_detor?
    return 0;
}

int list_resize(List_t *list, size_t new_capacity)
{   
    CHECK_ON_ERROR(list->capacity > MAX_CAPACITY, LIST_ERROR_CAPACITY_TOO_BIG);
    
    Elements_t *test_realloc = (Elements_t *) realloc(list->elements, new_capacity * sizeof(Elements_t));
    CHECK_ON_ERROR(test_realloc == NULL, LIST_ERROR_CANT_REALLOC);

    list->elements = test_realloc;
    CHECK_ON_ERROR(list->elements == NULL, LIST_ERROR_WRONG_REALLOC_IN_RESIZE);

    list_add_to_free(list, list->capacity - 1, new_capacity);
    
    list->capacity = new_capacity;

    return 0; // TODO: Do you need it? Function always returns 0
}

int list_add_to_free(List_t *list, int start, int finish)
{   
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

int list_del(List_t *list, int index)
{   
    CHECK_ON_ERROR(list->elements[index].next == POISON, LIST_ERROR_DEL_FROM_POISON_INDEX);

    int tmp_prev = list->elements[index].prev;
    int tmp_next = list->elements[index].next;

    /* TODO: Wrap in function for clarity

    May be instead of list_swap_next() and ..._prev() create
    create function that connects to elements? Like:

    ---
    bind_elements(tmp_prev, tmp_next);
    ---

    And in case of list_add it also would become more clear

    */
    list->elements[list->elements[index].prev].next = tmp_next;
    list->elements[list->elements[index].next].prev = tmp_prev;
   
    list_add_to_free(list, index, index + 1);   

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

    list->elements[list->tail].next = 0;

    return 0;
}

int free_pop(List_t *list)
{
    int tmp = list->free_head;

    list->free_head = list->elements[tmp].next;

    return tmp;
}

int free_update(List_t *list)
{
    list->free_head = POISON;
    list->free_tail = POISON;

    list_add_to_free(list, list->size, list->capacity);

    return 1;
}