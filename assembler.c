
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "globals.h"
#include "preassembler.h"
#include "first_pass.h"
#include "seconde_pass.h"
#include "output.h"
#include "assembler.h"
#include "labels.h"


int main(int argc,char *argv[])
{
    int i,success=1;
    for (i=1;i<argc;++i){
        success=process_file(argv[i]);
    }
    return success;
}

int process_file(char *filename){
    char *input_filename;
    FILE *fptr;
    FILE *fptr1;
    int success=0;
    int IC = IC_INITIAL_VALUE;          /*  1.1 */
    int DC = 0;
    machine_word code_img[MAX_MEMORY_PLACE];
    machine_word data_img[MAX_MEMORY_PLACE];
    label* label_matrix[MAX_TABLE_LABLE_SIZE];
    int i;

    input_filename = (char *) malloc(sizeof(filename)+4);
    if(input_filename == NULL) {
        printf("Error! memory not allocated.\n");
        exit(0);
    }
    strcpy(input_filename, filename);
    strcat(input_filename, ".as");
    fptr = fopen(input_filename,"r");
    if (fptr == NULL){
        printf("Error: file %s is no have access to reading \n",input_filename);
        free(input_filename);
        return 0;
    }
    fptr1=preassembler(fptr, filename);
    if (fptr1==NULL)
        printf("Error: file %s is failed to make pre-assembler process \n",input_filename);
    else
    {
        rewind(fptr1);
        success = first_pass(fptr1,filename, &DC, &IC, label_matrix, code_img,data_img);
        if (success)
        {
            rewind(fptr1);
            IC = IC_INITIAL_VALUE;              /* 2.1 */
            success = seconde_pass(filename,fptr1, &IC, label_matrix, code_img);
            if (success)
            {
                process_output_files(filename,label_matrix,code_img,data_img,IC,DC);        /* 2.11 */
                printf("The assembler work fine , your output files is in the library\n");
            }

        }
    }
    for (i=0;i<get_counter_label();i++)                          /* free label matrix memory */
    {
        free(label_matrix[i]->labal_name);
        free(label_matrix[i]);
        set_counter_label(0);
    }
    printf("-----------------------------------------------------------------------\n");
    return success;
}





































