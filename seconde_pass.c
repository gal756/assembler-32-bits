#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tools.h"
#include "seconde_pass.h"
#include "labels.h"


int seconde_pass(char *filename,FILE* fptr, int* IC, label** label_matrix, machine_word* code_img)
{
    char buff_line[MAX_LINE_LENGTH];
    char *temp;
    int index;
    int index_label=-1;
    int ans;
    int error_flag=-1,num_line=0;
    int counter = 0;
    char *output_filename;
    FILE *fp;



    output_filename = (char*)malloc(sizeof(filename) + 4);
    if (output_filename == NULL) {
        printf("Error! memory not allocated.\n");
        exit(0);
    }
    strcpy(output_filename, filename);
    strcat(output_filename, ".ext");
    fp= fopen(output_filename,"w");
    if (fp == NULL){
        printf("Error: file %s is no have access to writing \n",output_filename);
        free(output_filename);
        return 0;
    }
    while (fgets(buff_line, MAX_LINE_LENGTH, fptr) != NULL)          /* 2.2 */
    {
        num_line++;
        index=0;
        if (is_blank_line(buff_line))
            continue;
        temp = getWord(buff_line, &index);

        if (checkForLabel(temp) == 1)               /* 2.3 */
        {
            temp = getWord(buff_line, &index);
        }
        ans=check_prompt_type(temp, 0);             /* 2.4 */
        if(ans==3)                                      /* 2.5 */
        {
            temp = getWord(buff_line, &index);
            while(temp[0]!='\0')
            {
                index_label=searchLabel(label_matrix,temp);
                if(index_label!=-1)
                {
                    label_matrix[index_label]->type=entry;          /* 2.6 */
                }
                else
                {
                    printf("ERROR: in file %s.am at line %d in second pass process, the label '%s' doesn't exist .  \n", filename, num_line,temp);
                    error_flag=num_line;
                }
                temp = getWord(buff_line, &index);
            }
        }
        else if(ans==-1)                        /* 2.7 2.8*/
        {
            counter++;
            if(address_completion(filename,output_filename,num_line,temp,buff_line,&index,&counter,label_matrix,code_img)==-1)
            {
                error_flag=num_line;
            }
        }
    }
    fclose(fp);
    if (error_flag != -1)   /* 2.10 */
    {
        printf("error in process of the second pass in %s.am at line %d \n",filename,error_flag);
        return 0;
    }
    (*IC)+=(counter-1);
    return 1;
}

int address_completion(char *filename,char *filename_ext,int num_line,char *temp,char *buff_line,int *index,int *counter,label** label_matrix, machine_word* code_img)
{
    char* op1, *op2;
    int op_num;
    int flag_error=0;


    op_num = checkOpcode(temp);

    if (op_num < 5)
    {
        op1 = getWord(buff_line, index);
        pass_comma(buff_line, index);
        op2 = getWord(buff_line, index);
        if (find_address(op1)==find_address(op2)&& find_address(op1)==3)
        {
            (*counter)++;
        }
        else
        {
            if (code_img[*counter].type == -1)
            {
                if (find_address(op1) == 2)
                {
                    process_addressing_method(op1);
                    flag_error=update_miss_op(filename_ext,label_matrix,op1,code_img,counter);
                    if (flag_error==-1)
                        printf("ERROR: in file %s.am at line %d in second pass process, the label '%s' doesn't exist .  \n", filename,num_line,op1);
                }
                else
                {
                    flag_error=update_miss_op(filename_ext,label_matrix,op1,code_img,counter);
                    if (flag_error==-1)
                        printf("ERROR: in file %s.am at line %d in second pass process, the label '%s' doesn't exist .  \n", filename,num_line,op1);
                }
            }
            (*counter)++;
            if (code_img[*counter].type == -1) {

                if (find_address(op2) == 2) {
                    process_addressing_method(op2);
                    flag_error=update_miss_op(filename_ext,label_matrix, op2, code_img, counter);
                    if (flag_error==-1)
                        printf("ERROR: in file %s.am at line %d in second pass process, the label '%s' doesn't exist .  \n", filename,num_line,op2);
                } else
                {
                    flag_error=update_miss_op(filename_ext,label_matrix, op2, code_img, counter);
                    if (flag_error==-1)
                        printf("ERROR: in file %s.am at line %d in second pass process, the label '%s' doesn't exist .  \n", filename,num_line,op2);
                }
            }
            else
                (*counter)++;
        }
    }
    else if (op_num > 4 && op_num < 14)
    {
        if (code_img[*counter].type == -1)
        {
            op1 = getWord(buff_line, index);
            if (find_address(op1) == 2)
            {
                process_addressing_method(op1);
                flag_error=update_miss_op(filename_ext,label_matrix,op1,code_img,counter);
                if (flag_error==-1)
                    printf("ERROR: in file %s.am at line %d in second pass process, the label '%s' doesn't exist .  \n", filename,num_line,op1);
            }
            else
            {
                flag_error=update_miss_op(filename_ext,label_matrix,op1,code_img,counter);
                if (flag_error==-1)
                    printf("ERROR: in file %s.am at line %d in second pass process, the label '%s' doesn't exist .  \n", filename,num_line,op1);
            }
        }
        else
            (*counter)++;
    }
    else
        (*counter)++;
    return flag_error;
}
int update_miss_op(char *output_filename,label** label_matrix,char *op,machine_word* code_img,int *counter)
{
    FILE *fp;
    unsigned int num;
    int first_num,second_num;

    int label_place;
    label_place = searchLabel(label_matrix, op);
    if (label_place==-1) {
        (*counter)++;
        return -1;
    }
    code_img[*counter].type = 1;
    code_img[*counter].word.add.data = label_matrix[label_place]->index;
    if(label_matrix[label_place]->type==external)
    {
        code_img[*counter].word.add.ARE = 1;
        fp = fopen(output_filename, "a");
        num=(unsigned int)(IC_INITIAL_VALUE+(*counter));
        first_num=take_5_bits(0, num);
        second_num=take_5_bits(1, num);
        fprintf(fp, "%s\t%c%c\n",label_matrix[label_place]->labal_name, base32_convert(first_num), base32_convert(second_num));
        fclose(fp);
    }
    else
        code_img[*counter].word.add.ARE = 2;
    (*counter)++;
    return 0;
}

void process_addressing_method(char* word)
{
    int i = 0;
    while (word[i]!='.')
    {
        i++;
    }
    word[i] = '\0';
}
