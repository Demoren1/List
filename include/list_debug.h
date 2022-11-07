#include <unistd.h>
#include <math.h>

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

#define CHECK(condition, code_of_error)  (condition) ? code_of_error : 0;

#define LIST_LOG_FILE list_logs

#define CHECK_ON_ERROR(condition, code) if(condition)                                                           \
                                        {                                                                       \
                                            error_decoder(code);                                                \
                                            list_dump(list, FUNC_GENERAL_INFO());                               \
                                            return -1;                                                          \
                                        }


#define LIST_ASSERT_OK(stk)      if (list_check(list) != 0)                                                      \
                            {                                                                               \
                                list_err_decoder(stk->code_of_error);                                      \
                                list_dump(list, FUNC_GENERAL_INFO(), list_check(list));                      \
                                return -1;                                                                   \
                            }                                                           

#define CHECK(condition, code_of_error)  (condition) ? code_of_error : 0;

#define LIST_PRINT_ERROR(testing_var, code_of_error) if (testing_var & code_of_error)                           \
                                                    {                                                           \
                                                        fprintf(LIST_LOG_FILE, "%s\n", #code_of_error);         \
                                                        fprintf(graph_log_for_browser, "%s\n", #code_of_error); \
                                                    }                                                           \
                                                    else  0;

const long long QUANTITY_OF_ERRORS = pow(2, 16);

int open_list_logs();

int close_list_logs();

int error_decoder(int code);

enum List_errors
{
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
};