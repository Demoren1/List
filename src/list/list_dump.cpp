#include <stdio.h>
#include <assert.h>
#include <list_debug.h>
#include <list_func.h>

static FILE *list_logs = 0;


int open_list_logs()
{
    list_logs = fopen("log_list_file.txt", "w");

    if (list_logs == NULL)
    {
        printf("Cant open logs");
        return -1;
    }

    return 0;
}

int close_list_logs()
{
    fclose(list_logs);
    return 0;
}

int list_dump(List_t *list, const char* name_file, const char* name_function, const char* name_variable, int num_line)
{   
    fprintf(list_logs, "Dump called from %s file, in %s func, in %d line, name of variable = %s\n\n", name_file, name_function, num_line, name_variable);    

    fprintf(list_logs,  "size     = %zd\n"\
                        "capacity = %zd\n", list->size, list->capacity);
    
    fprintf(list_logs, "            ");
    for(int i = 0; i < list->capacity; i++)
    {   
        if (list->head == i)
        {
            fprintf(list_logs, "H_______");
        }

        else if (list->tail == i)
        {
            fprintf(list_logs, "T_______");
        }

        else
        {
            fprintf(list_logs, "________");
        }
    }

    
    fprintf(list_logs, "\nINDEXES: ");
    for(int i = 0; i < list->capacity; i++)
    {
        fprintf(list_logs, "|%3d|   ", i);
    }

    fprintf(list_logs, "\n\nVALUE:   ");
    for(int i = 0; i < list->capacity; i++)
    {
        fprintf(list_logs, "|%3d|   ", list->elements[i].value);
    }

    fprintf(list_logs, "\n\nNEXT:    ");
    for(int i = 0; i < list->capacity; i++)
    {
        fprintf(list_logs, "|%3d|   ", list->elements[i].next);
    }

    

    fprintf(list_logs, "\n\nPREV:    ");
    for(int i = 0; i < list->capacity; i++)
    {
        fprintf(list_logs, "|%3d|   ", list->elements[i].prev);
    }
    
    fprintf(list_logs, "\n");
    for(int i = 0; i < list->capacity; i++)
    {
        fprintf(list_logs, "_________");
    }

    

    fprintf(list_logs, "\nHow we see:\t");
    
    int i = list->head;
    while (list->elements[i].next > 0)
    {
        fprintf(list_logs, "%d\t", list->elements[i].value);
        i = list->elements[i].next;
    }
    fprintf(list_logs, "%d", list->elements[i].value);

    fprintf(list_logs, "\n\n\n");

    fflush(list_logs);
    
    return 0;
}

int error_decoder(int code)
{
    LIST_PRINT_ERROR(code, LIST_ERROR_LIST_FUNC_END_WITH_ERROR);

    LIST_PRINT_ERROR(code, LIST_ERROR_ADD_AFTER_POISONED_INDEX);

    LIST_PRINT_ERROR(code, LIST_ERROR_CAPACITY_TOO_BIG);

    LIST_PRINT_ERROR(code, LIST_ERROR_DEL_FROM_POISON_INDEX);

    LIST_PRINT_ERROR(code, LIST_ERROR_LOGIC_INDEX_GREATER_CAPACITY);

    LIST_PRINT_ERROR(code, LIST_ERROR_JUMP_ON_POISON);

    fflush(LIST_LOG_FILE);

    return 0;
}

size_t list_check(List_t *list)
{   
    if (LIST_LOG_FILE == 0)
    {
        return -1;
    }
    
    if (list == 0)
    {   
        fprintf(LIST_LOG_FILE, "ERROR: list destroyed");
        return -1;
    }

    list->code_of_error |= CHECK(list->capacity > MAX_CAPACITY, LIST_ERROR_CAPACITY_TOO_BIG);

    return list->code_of_error;

}   

int list_graph_dump(List_t *list)
{
    
}
















