#ifndef HEADER_GUARD
#define HEADER_GUARD
#include <unistd.h>
#include <math.h>
// #include <list_func.h>

#define MAX_CAPACITY 65536

#define LIST_END_DUMP() fputs("-----------------------------------------------------------------------------------------------------------------------\n\n", LIST_LOG_FILE);

#define LIST_CHECK_FUNC(func)    if(func == -1)                                                                      \
                            {                                                                                   \
                                size_t code_of_error = LIST_ERROR_LIST_FUNC_END_WITH_ERROR;                     \
                                error_decoder(code_of_error);                                                   \
                                DBG;                                                                            \
                                return -1;                                                                      \
                            }

#define CHECK_CONDITION(condition)  if(condition)       \
                                    {                   \
                                        DBG;            \
                                        return -1;      \
                                    }       

#define DBG printf("%s:%d -- %s\n", __FILE__, __LINE__, __FUNCTION__);

#define SOFT_ASS(condition) if (condition)                                                                                   \
                            {                                                                                               \
                                printf("something go wrong at %s file, %s func, %s obj, %d line\n", FUNC_GENERAL_INFO());   \
                                return -1;                                                                                  \
                            }   

#define CHECK(condition, code_of_error)  (condition) ? code_of_error : 0;

#define DOT .

#define LIST_LOG_FILE list_logs

#define GRAPH_LOG_FILE graph_log_for_browser

#define GRAPH_FOR_BROWSER "graph_log.html"

#define WRITE_LIST_LOG_HEADER() fprintf(LIST_LOG_FILE, "Dump called from %s file, in %s func, in %d line, name of variable = %s\n\n",   \
                                name_file, name_function, num_line, name_variable);                                                     \
                                fprintf(GRAPH_LOG_FILE, "Dump called from %s file, in %s func, in %d line, name of variable = %s\n\n",  \
                                name_file, name_function, num_line, name_variable);                                                     \
                                fprintf(LIST_LOG_FILE,  "size     = %zd\n"                                                              \
                                                    "capacity = %zd\n", list->size, list->capacity);                                    \
                                fprintf(GRAPH_LOG_FILE,  "size     = %zd\n"                                                             \
                                                    "capacity = %zd\n", list->size, list->capacity);                                    

#define CHECK_ON_ERROR(condition, code) if(condition)                                                           \
                                        {                                                                       \
                                            error_decoder(code);                                                \
                                            list_dump(list, FUNC_GENERAL_INFO());                               \
                                            return code;                                                         \
                                        }

#define LIST_PRINT_ERROR(testing_var, code_of_error) if (testing_var & code_of_error)                           \
                                                    {                                                           \
                                                        fprintf(LIST_LOG_FILE, "%s\n", #code_of_error);         \
                                                        fprintf(GRAPH_LOG_FILE, "%s\n", #code_of_error); \
                                                    }                                                           
                                                

const long long QUANTITY_OF_ERRORS = 1 << 20;

int open_list_logs();

int close_list_logs();

int error_decoder(int code);

typedef enum List_errors_t
{
    NO_ERROR                                    = 0,
    LIST_ERROR_LIST_FUNC_END_WITH_ERROR         = 1 << 0,
    LIST_ERROR_ADD_AFTER_POISONED_INDEX         = 1 << 1,
    LIST_ERROR_CAPACITY_TOO_BIG                 = 1 << 2,
    LIST_ERROR_DEL_FROM_POISON_INDEX            = 1 << 3,
    LIST_ERROR_LOGIC_INDEX_GREATER_CAPACITY     = 1 << 4,
    LIST_ERROR_PTR_ON_LIST_NULL                 = 1 << 5,
    LIST_ERROR_JUMP_ON_POISON                   = 1 << 6,
    LIST_ERROR_WRONG_REALLOC_IN_RESIZE          = 1 << 7,
    LIST_ERROR_CANT_REALLOC                     = 1 << 8,
    LIST_ERROR_CANT_CALLOC_FOR_SORT             = 1 << 9,
    LIST_ERROR_PREV_NOT_EQ_NEXT                 = 1 << 10,
    LIST_ERROR_CAPACITY_TOO_FEW                 = 1 << 11,
    LIST_ERROR_CANT_CALLOC                      = 1 << 12,
    LIST_ERROR_LIST_BROKEN                      = 1 << 13,
    LIST_ERROR_ADD_BEFORE_ZERO_INDEX            = 1 << 14
} List_errors;

#endif