#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <list_debug.h>
#include <list_func.h>

static FILE *LIST_LOG_FILE = 0;
static FILE *GRAPH_LOG_FILE = 0;
static const int LEN_OF_COMMAND = 128;
static int num_of_pic = 0;

int open_list_logs()
{
    LIST_LOG_FILE = fopen("log_list_file.txt", "w");

    if (LIST_LOG_FILE == NULL)
    {
        printf("Cant open logs");
        return -1;
    }

    GRAPH_LOG_FILE = fopen("graph_log.htm", "w");

    if (GRAPH_LOG_FILE == NULL)
    {
        printf("Cant open graph logs for browser");
        return -1;
    }

    fprintf(GRAPH_LOG_FILE, "<pre>\n\n");

    return 0;
}

int close_list_logs()
{   
    if (LIST_LOG_FILE != NULL)  
    {
        fclose(LIST_LOG_FILE);
        LIST_LOG_FILE = NULL;
    }

    if (GRAPH_LOG_FILE != NULL)
    {
        fclose(GRAPH_LOG_FILE);
        GRAPH_LOG_FILE = NULL;
    }
    return 0;
}

int list_dump(const List_t *list, const char* name_file, const char* name_function, const char* name_variable, int num_line)
{   
    WRITE_LIST_LOG_HEADER();

    fprintf(LIST_LOG_FILE, "            ");
    for(int i = 0; i < list->capacity; i++)
    {   
        if (list->head == i)
        {
            fprintf(LIST_LOG_FILE, "H_______");
        }

        else if (list->tail == i)
        {
            fprintf(LIST_LOG_FILE, "T_______");
        }

        else
        {
            fprintf(LIST_LOG_FILE, "________");
        }
    }

                    
    
    fprintf(LIST_LOG_FILE, "\nINDEXES: ");
    for(int i = 0; i < list->capacity; i++)
    {
        fprintf(LIST_LOG_FILE, "|%3d|   ", i);
    }
                    

    fprintf(LIST_LOG_FILE, "\n\nVALUE:   ");
    for(int i = 0; i < list->capacity; i++)
    {
        fprintf(LIST_LOG_FILE, "|%3d|   ", list->elements[i].value);
    }
                    

    fprintf(LIST_LOG_FILE, "\n\nNEXT:    ");
    for(int i = 0; i < list->capacity; i++)
    {
        fprintf(LIST_LOG_FILE, "|%3d|   ", list->elements[i].next);
    }

                    
    

    fprintf(LIST_LOG_FILE, "\n\nPREV:    ");
    for(int i = 0; i < list->capacity; i++)
    {
        fprintf(LIST_LOG_FILE, "|%3d|   ", list->elements[i].prev);
    }
                    
    
    fprintf(LIST_LOG_FILE, "\n");
    for(int i = 0; i < list->capacity; i++)
    {
        fprintf(LIST_LOG_FILE, "_________");
    }

                    
    

    fprintf(LIST_LOG_FILE, "\nHow we see:\t");
    
    int i = list->head;
    while (list->elements[i].next > 0)
    {
        fprintf(LIST_LOG_FILE, "%d\t", list->elements[i].value);
        i = list->elements[i].next;
        
    }
    fprintf(LIST_LOG_FILE, "%d", list->elements[i].value);

    fprintf(LIST_LOG_FILE, "\n\n\n");

    fflush(LIST_LOG_FILE);
    
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

    LIST_PRINT_ERROR(code, LIST_ERROR_CANT_CALLOC);

    LIST_PRINT_ERROR(code, LIST_ERROR_LIST_BROKEN);

    LIST_PRINT_ERROR(code, LIST_ERROR_ADD_BEFORE_ZERO_INDEX);

    fflush(LIST_LOG_FILE);

    return code;
}
//Черепаха заяц алгоритм
int list_check(List_t *list)
{   
    CHECK_ON_ERROR(list == NULL, LIST_ERROR_LIST_BROKEN);

    int jumper = list->head;
    int test_size = 0;

    while((test_size++ < list->capacity) && (jumper != 0))
    {
        jumper = list->elements[jumper].next;
    }

    CHECK_ON_ERROR(jumper != 0, LIST_ERROR_LIST_BROKEN);

    return 0;
}

int turtle_hare_check(List_t *list)
{
    int start = list->free_head;

    int hare = start;
    int turtle = start;

    while (turtle != hare)
    {
        // turt;
    }
    
    return 0;
}

int list_graph_dump(List_t *list)
{
    FILE *graph_log = fopen(GRAPH_FOR_BROWSER, "w");
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
                        
                        "    <tr><td bgcolor=\"yellow\" port = \"I%d\">Index = %d</td></tr>\n"
                        
                        "    <tr><td bgcolor=\"lightblue\"><font color=\"#0000ff\">Value = %d</font></td></tr>\n"
                        
                        "    <tr>\n"
                        "    <td>\n"
                        
                        "        <table border=\"0\" cellborder=\"1\">\n"
                        
                        "        <tr>\n"
                        
                        "            <td bgcolor=\"#70de9f\">Prev = %d</td> \n"
                        
                        "            <td bgcolor = \"#c8A2c8\" port = \"N%d\"> Next =  %d </td>\n"
                        
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
    }

    fprintf(graph_log, ";\n");

    fputs("\n}", graph_log);

    fprintf(GRAPH_LOG_FILE, "DUMP #%d \n", num_of_pic);
    fprintf(GRAPH_LOG_FILE, "<img src = graph_dumps/dump_%d.jpeg>\n", num_of_pic);

    fclose(graph_log);
    char command[LEN_OF_COMMAND] = {};   
    sprintf(command, "dot -Tjpeg %s > graph_dumps/dump_%d.jpeg", GRAPH_FOR_BROWSER, num_of_pic++);
    
    system(command);
    return 0;
}














