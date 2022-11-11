#ifndef HEADER_GUARD
#define HEADER_GUARD
#include <unistd.h>
#include <math.h>
#include <list_func.h>

#define MAX_CAPACITY 65536

#define LIST_END_DUMP() fputs("-----------------------------------------------------------------------------------------------------------------------\n\n", LIST_LOG_FILE);

#define LIST_CHECK_FUNC(func)    if(func == -1)                                                                      \
                            {                                                                                   \
                                size_t code_of_error = LIST_ERROR_LIST_FUNC_END_WITH_ERROR;                     \
                                error_decoder(code_of_error);                                                   \
                                DBG;                                                                            \
                                return -1;                                                                      \
                            }      

#define DBG printf("%s:%d -- %s\n", __FILE__, __LINE__, __FUNCTION__);

#define SOFT_ASS(condition) if (condition)                                                                                   \
                            {                                                                                               \
                                printf("something go wrong at %s file, %s func, %s obj, %d line\n", FUNC_GENERAL_INFO());   \
                                return -1;                                                                                  \
                            }   

#define CHECK(condition, code_of_error)  (condition) ? code_of_error : 0;

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

int turtle_hare_check(List_t *list);


#endif