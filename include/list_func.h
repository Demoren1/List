#include <stdio.h>

#define FUNC_GENERAL_INFO(object)  __FILE__, __FUNCTION__, #object, __LINE__

#define LIST_CTOR(list, capacity) list_ctor(&list, capacity, FUNC_GENERAL_INFO(list))

#define DUMP_LIST(list) dump_list(list, FUNC_GENERAL_INFO(list))

#define POISON -1


typedef int var;

typedef struct Elements
{
    var value;
    int next;
    int prev;
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
    size_t free;
    size_t size;
    size_t capacity;
    Elements_t *elements;
    Dump_list_info dump_info = {};
}List_t;


int list_ctor(List_t *list, size_t capacity, const char* name_function, const char* name_file, const char* name_variable, int num_line);

int list_add(List_t *list, size_t index, var value);

int list_dump_info_ctor(List *list, const char* name_function, const char* name_file, const char* name_variable, int num_line);

int dump_list(List_t *list, const char* name_function, const char* name_file, const char* name_variable, int num_line);

int list_swap_next(List_t *list, size_t index1, size_t index2);

int list_swap_prev(List_t *list, size_t index1, size_t index2);

int find_index_for_next(List_t *list);

int find_index_for_prev(List_t *list, size_t index);

int find_new_tail(List_t *list, int index, int new_index);

int list_detor(List_t *list);

int list_resize(List_t *list, size_t new_size);

int list_fill_poison(List_t *list, int start, int finish);

int list_del(List_t *list, int index);