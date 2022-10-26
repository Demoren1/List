#include <unistd.h>
#include <math.h>

#define MAX_CAPACITY 4096

#define END_DUMP() fputs("-----------------------------------------------------------------------------------------------------------------------\n\n", log_file);

#define CHECK_FUNC(func)    if(func == -1)                                                                      \
                            {                                                                                   \
                                printf("Function return error code on ");                                       \
                                write_error_in_dump(LIST_ERROR_LIST_FUNC_END_WITH_ERROR, FUNC_GENERAL_INFO());  \
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

#define LOG_FILE list_logs

#define PRINT_IN_LOG(code)  fprintf(LOG_FILE, "ERROR %x: happend in %s file, %s func, on %d line \n", code, name_file, name_function, num_line); \
                            fflush(LOG_FILE);

#define ASSERT_OK(condition, error_code) if(condition)                                              \
                                        {                                                           \
                                            write_error_in_dump(error_code, FUNC_GENERAL_INFO());   \
                                            return -1;                                              \
                                        }                                                           


const long long QUANTITY_OF_ERRORS = pow(2, 16);

int open_list_logs();

int close_list_logs();

int write_error_in_dump(int code, const char* name_file, const char* name_function, const char* name_variable, int num_line);

enum List_errors
{
    LIST_ERROR_LIST_FUNC_END_WITH_ERROR = 1 << 0,
    LIST_ERROR_ADD_AFTER_POISONED_INDEX = 1 << 1,
    LIST_ERROR_CAPACITY_TOO_BIG         = 1 << 2,
    LIST_ERROR_DEL_FROM_POISON_INDEX    = 1 << 3
};