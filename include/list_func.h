#include <stdio.h>
#include <stdbool.h>

#define FUNC_GENERAL_INFO(object)  __FILE__, __FUNCTION__, #object, __LINE__

#define LIST_CTOR(list, capacity) list_ctor(&list, capacity, FUNC_GENERAL_INFO(list))

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
    int num_of_str;
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
    size_t code_of_error = 0;
    bool is_sorted = 0;
}List_t;


int list_ctor(List_t *list, size_t capacity, const char* name_function, const char* name_file, const char* name_variable, int num_line);

[[nodiscard]]int list_add(List_t *list, size_t index, var value);

[[nodiscard]]int list_push(List_t *list, var index);

int list_dump_info_ctor(List *list, const char* name_function, const char* name_file, const char* name_variable, int num_line);

int list_dump(List_t *list, const char* name_function, const char* name_file, const char* name_variable, int num_line);

int list_dtor(List_t *list);

int list_resize(List_t *list, size_t new_size);      

var list_del(List_t *list, int index);

var list_pop(List_t *list);

int list_sort(List_t *list);

[[nodiscard]]int list_find(List *list, int logical_index);

int list_graph_dump(List_t *list);              

int list_check(List_t *list);

//todo add 