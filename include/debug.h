#include <unistd.h>

#define END_DUMP() fputs("-----------------------------------------------------------------------------------------------------------------------\n\n", log_file);


#define DBG printf("%s:%d -- %s\n", __FILE__, __LINE__, __FUNCTION__);

int open_list_logs();

int close_list_logs();

