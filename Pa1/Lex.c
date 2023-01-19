/*
Name: Evan Metcalf
CruzID: evmetcal 1963052
Assignment Name: pa1
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

#define MAX_WORD_LENGTH 100

void print_list(List L1)
{
    printf("=================================\n");
    int saved = index(L1);
    
    int size = 0;
    moveFront(L1);
    while(size != length(L1))
    {
        printf("[%d] - %d", index(L1), get(L1));
        if(index(L1) == saved)
        {
            printf("  <----");
        }
        printf("\n");
        moveNext(L1);
        size++;
    }
    
    moveFront(L1);
    int i = 0;
    while(i != saved)
    {
        if(saved == -1) {
            append(L1,0);
            moveBack(L1);
            delete(L1);
            break;
        }
        moveNext(L1);
        i++;
    }
    printf("================================\n");
}

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        fprintf( stderr, "ERROR: MUST PASS TWO ARGUMENTS\nUse command like Lex in.txt out.txt");
        return -1;
    }

    FILE* file = fopen(argv[1], "r");
    if(file == NULL) 
    {
        printf("unable to open: %s", file); 
        return -1;
    }

    //-----------------------------------------------------------------------------------//

    int count = 0;
    int i = 0;

    char ch;
    while((ch=fgetc(file))!=EOF) {
      if(ch=='\n')
         count++;
    }

    rewind(file);
    char** strings = calloc(count, sizeof(char*));
    size_t control = count;

    while(control--)
    {
        char* word = calloc(MAX_WORD_LENGTH, sizeof(char));  
        fscanf(file, "%s", word);
        strings[i++] = (char*)word;
    }

    control = count; i = 0;

    List L = newList();

    while(control--)
    {
        if(length(L) == 0)
        {
            append(L, i);
            moveFront(L);
        }
        else
        {
            if(strcmp(strings[i], strings[get(L)]) == 1 ||  strcmp(strings[i], strings[get(L)]) == 0)
            {
                insertAfter(L, i);
                moveBack(L);
            }
            else
            {
                if(strcmp(strings[i], strings[front(L)]) == -1 || strcmp(strings[i], strings[front(L)]) == 0)
                {
                    prepend(L, i);
                    moveBack(L);
                }
                else{
                    while(strcmp(strings[i], strings[get(L)]) == -1)
                    {
                        movePrev(L);
                    }
                    insertAfter(L, i);
                    moveBack(L);
                }
            }
        }
        i++;
    } 

    print_list(L);

    fclose(file);

    return 0;
}