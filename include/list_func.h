#ifndef FUNC_HEADER_GUARD
#define FUNC_HEADER_GUARD

#include <stdio.h>
#include <stdbool.h>
#include <list_debug.h>

#define FUNC_GENERAL_INFO(object)  __FILE__, __FUNCTION__, #object, __LINE__

#define list_ctor(list, capacity)  _list_ctor(&list, capacity, FUNC_GENERAL_INFO(list)) 

#define DUMP_LIST(list) list_dump(list, FUNC_GENERAL_INFO(list)); \
                        list_graph_dump(list);

#define POISON -1

typedef int var;

typedef struct Element
{
    var value;
    int next = POISON;
    int prev = POISON;
}Element_t;

struct Dump_list_info
{
    const char* name_of_func;
    const char* name_of_file;
    const char* name_of_variable;
    int num_of_line;             
};

typedef struct List
{
    int head;
    int tail;

    size_t size;
    size_t capacity;

    Element_t *elements;

    Dump_list_info dump_info = {};

    int free_head;
    int free_tail;

    List_errors code_of_error = NO_ERROR;         

    bool is_sorted = 0;
}List_t;

typedef enum Postions_t
{
    BEFORE = 0,
    AFTER  = 1
} Positions;

int _list_ctor(List_t *list, size_t capacity, const char* name_function, const char* name_file, const char* name_variable, int num_line);

int list_insert(List_t *list, size_t index, var value, Positions pos);  

int list_push(List_t *list, var value);

int list_dump_info_ctor(List *list, const char* name_function, const char* name_file, const char* name_variable, int num_line);

int list_dump(const List_t *list, const char* name_function, const char* name_file, const char* name_variable, int num_line);     

int list_dtor(List_t *list);

var list_erase(List_t *list, int index);    

var list_pop(List_t *list);

int list_sort(List_t *list);

[[nodiscard]]int list_find(List *list, int logical_index);      

int list_graph_dump(List_t *list);              

int list_check(List_t *list);

#endif