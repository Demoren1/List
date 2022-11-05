#include <stdio.h>

#define FUNC_GENERAL_INFO(object)  __FILE__, __FUNCTION__, #object, __LINE__

#define LIST_CTOR(list, capacity) list_ctor(&list, capacity, FUNC_GENERAL_INFO(list))

#define DUMP_LIST(list) list_dump(list, FUNC_GENERAL_INFO(list));                   \
                        list_graph_dump(list);

#define POISON -1

#define PUSH_IN_LIST(list, value)   list_add(list, (list)->tail, value); 

#define POP_FROM_LIST(list)         list_del(list, (list)->tail);

typedef int var;

typedef struct Elements
{
    var value;
    int next = POISON;
    int prev = POISON;
}Elements_t;

struct Dump_list_info
{
    const char* name_of_func;
    const char* name_of_file;
    const char* name_of_variable;
    int num_of_str;
};

typedef struct List
{
    int head;
    int tail;
    size_t size;
    size_t capacity;
    Elements_t *elements;
    Dump_list_info dump_info = {};
    int free_head;
    int free_tail;
    size_t code_of_error = 0;
    int is_sorted = 0;
}List_t;


int list_ctor(List_t *list, size_t capacity, const char* name_function, const char* name_file, const char* name_variable, int num_line);

[[nodiscard]]int list_add(List_t *list, size_t index, var value);

int list_dump_info_ctor(List *list, const char* name_function, const char* name_file, const char* name_variable, int num_line);

int list_dump(List_t *list, const char* name_function, const char* name_file, const char* name_variable, int num_line);

int list_detor(List_t *list);

int list_resize(List_t *list, size_t new_size);      

int list_del(List_t *list, int index);

int list_sort(List_t *list);

[[nodiscard]]int list_find(List *list, int logical_index);

int list_graph_dump(List_t *list);              

//todo add 