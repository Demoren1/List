#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <list_debug.h>
#include <list_func.h>

static FILE *list_logs = 0;
static FILE *graph_log_for_browser = 0;

static int num_of_pic = 0;


int open_list_logs()
{
    list_logs = fopen("log_list_file.txt", "w");

    if (list_logs == NULL)
    {
        printf("Cant open logs");
        return -1;
    }

    graph_log_for_browser = fopen("graph_log.htm", "w");

    if (graph_log_for_browser == NULL)
    {
        printf("Cant open graph logs for browser");
        return -1;
    }

    fprintf(graph_log_for_browser, "<pre>\n\n");

    return 0;
}

int close_list_logs()
{
    fclose(list_logs);
    fclose(graph_log_for_browser);
    return 0;
}

int list_dump(List_t *list, const char* name_file, const char* name_function, const char* name_variable, int num_line)
{   
    
    fprintf(list_logs, "Dump called from %s file, in %s func, in %d line, name of variable = %s\n\n", name_file, name_function, num_line, name_variable);    
    fprintf(graph_log_for_browser, "Dump called from %s file, in %s func, in %d line, name of variable = %s\n\n", name_file, name_function, num_line, name_variable);    

    
    fprintf(list_logs,  "size     = %zd\n"\
                        "capacity = %zd\n", list->size, list->capacity);            //todo use defines
                    
    fprintf(graph_log_for_browser,  "size     = %zd\n"\
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

    LIST_PRINT_ERROR(code, LIST_ERROR_WRONG_REALLOC_IN_RESIZE);

    LIST_PRINT_ERROR(code, LIST_ERROR_CANT_REALLOC);

    LIST_PRINT_ERROR(code, LIST_ERROR_CANT_CALLOC_FOR_SORT);

    LIST_PRINT_ERROR(code, LIST_ERROR_PREV_NOT_EQ_NEXT);

    LIST_PRINT_ERROR(code, LIST_ERROR_CAPACITY_TOO_FEW);

    fflush(LIST_LOG_FILE);

    return code;
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
    FILE *graph_log = fopen("graph_log.html", "w");
    fputs("digraph lala{\n", graph_log);
    fputs("rankdir = LR;\n", graph_log);
    fputs("bgcolor = grey;\n", graph_log);

    fputs("graph [splines=polyline];\n", graph_log);
    fputs("node [shape = \"plaintext\", style = \"solid\"];\n", graph_log);
    for (int i = 0; i < list->capacity; i++)
    {
        fprintf(graph_log, "node%d [\n"
                        "label=<\n"
                        
                        "<table border=\"0\" cellborder=\"1\" cellspacing=\"0\">\n"
                        
                        "    <tr><td bgcolor=\"yellow\" port = \"I%d\">I = %d</td></tr>\n"
                        
                        "    <tr><td bgcolor=\"lightblue\"><font color=\"#0000ff\">V = %d</font></td></tr>\n"
                        
                        "    <tr>\n"
                        "    <td>\n"
                        
                        "        <table border=\"0\" cellborder=\"1\">\n"
                        
                        "        <tr>\n"
                        
                        "            <td bgcolor=\"#70de9f\">P = %d</td> \n"
                        
                        "            <td bgcolor = \"#c8A2c8\" port = \"N%d\"> N =  %d </td>\n"
                        
                        "        </tr> \n"
                        
                        "        </table> \n"
                        
                        "    </td>\n"
                        
                        "    </tr>\n" 
                        
                        "</table>>\n"
                        "]\n\n", i, i, i, list->elements[i].value, list->elements[i].prev, i, list->elements[i].next);
    }

    fputs("edge [weight = \"100\", color = grey];\n", graph_log);
    for (int i = 0; i < list->capacity - 1; i++)
    {
        fprintf(graph_log, "node%d -> node%d ", i, i+1);

    }
    fputs(";\n", graph_log);



    fputs("edge [weight = \"1\", color = \"#3f0063\", splines = ortho];\n", graph_log);
    for (int jumper = list->head; ; jumper = list->elements[jumper].next)
    {
        fprintf(graph_log, "node%d:N%d -> node%d:I%d  ", jumper, jumper, list->elements[jumper].next, list->elements[jumper].next);

        if (jumper == 0)
        {
            break;
        }
    }
    fprintf(graph_log, ";\n");

    fputs("edge [weight = \"1\", color = blue];\n", graph_log);

    for (int  i = list->free_head; ; i = list->elements[i].next)
    {
        if (i == list->free_head)
        {
            fprintf(graph_log, "free [shape = \"circle\", style = \" filled\", filcolor = \"blue\"]; \n");
            fprintf(graph_log, "free -> node%d  ", i);
        }

        if (i == list->free_tail)
            break;
        
        fprintf(graph_log, "node%d -> node%d  ", i, list->elements[i].next);

        // printf("i = %d, free tail = %d\n", i, list->free_tail);
    }

    fprintf(graph_log, ";\n");

    fputs("\n}", graph_log);

    fprintf(graph_log_for_browser, "DUMP #%d \n", num_of_pic);
    fprintf(graph_log_for_browser, "<img src = graph_dumps/dump_%d.jpeg>\n", num_of_pic);

    fclose(graph_log);
    char command[128] = {};   
    sprintf(command, "dot -Tjpeg graph_log.html > graph_dumps/dump_%d.jpeg", num_of_pic++);
    
    system(command);
    return 0;
}














