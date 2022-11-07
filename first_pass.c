#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "globals.h"
#include "tools.h"
#include "labels.h"
#include "first_pass.h"

int first_pass(FILE* fptr,char *filename, int* DC, int* IC, label** label_matrix, machine_word* code_img,machine_word* data_img)
{
    int len, flag_label, index ;
    char* temp;
    char* temp_label=NULL;
    char buff_line[MAX_LINE_LENGTH];
    int ans;
    int error_flag=-1,num_line=0;


    while (fgets(buff_line, MAX_LINE_LENGTH, fptr) != NULL)              /*  1.2 */
    {
        index=0;
        flag_label=0;
        num_line++;

        if (is_blank_line(buff_line))
            continue;

        temp = getWord(buff_line, &index);
        if (checkForLabel(temp) == 1)                               /*  1.3 */
        {
            flag_label = 1;                                         /*  1.4 */
            len = strlen(temp);
            temp_label = (char*)malloc((len + 1) * sizeof(char));
            strcpy(temp_label, temp);
            temp_label[index - 1] = '\0';
            temp = getWord(buff_line, &index);
        }
        ans = check_prompt_type(temp, 0);

        if (ans >= 0 && ans < 3) {                      /*  1.5 */
            if (flag_label == 1)
            {
                if (insertLabel(label_matrix, temp_label, *DC, data) != 0)          /*  1.6 */
                {
                    printf("ERROR: in file %s.am at line %d in first pass process, the label '%s' is already exist  .  \n", filename, num_line,temp_label);
                    error_flag = num_line;
                }
            }
            if (insert_data(buff_line, &index, data_img, DC) == -1)          /*  1.7 */
            {
                printf("ERROR: in file %s.am at line %d in first pass process, there is an incorrect definition of data arguments. \n '%s'  \n", filename, num_line,buff_line);
                error_flag=num_line;
            }
        }
        else if (ans >= 3)                              /*  1.8 */
        {
            if (ans == 4)                                       /*  1.9 */
            {
                temp = getWord(buff_line, &index);
                while(temp[0]!='\0')
                {
                    insertLabel(label_matrix, temp, 0, external);
                    temp = getWord(buff_line, &index);
                }

            }

        }
        else
        {
            if (flag_label == 1)                            /*  1.11 */
            {
                if (insertLabel(label_matrix, temp_label, *IC, code) == -1)
                {
                    printf("ERROR: in file %s.am at line %d in first pass process, the label '%s' is already exist  .  \n", filename, num_line,temp_label);
                    error_flag=num_line;
                }
            }
            ans = checkOpcode(temp);                    /*  1.12 */
            if (ans == -1)
            {
                printf("ERROR: in file %s.am at line %d in first pass process, the opcode command '%s' isn't valid  .  \n", filename, num_line,temp);
                error_flag=num_line;
            }
            else
            {
                if(insert_code(filename,num_line,ans, buff_line, &index, IC, code_img)==-1)   /*  1.13 1.14 */
                {

                    error_flag=num_line;
                }

            }
        }
    }
    if(error_flag!=-1)                  /*  1.16 */
    {
        printf("error in process of the first pass in %s.am at line %d\n",filename,error_flag);
        return 0;
    }
    update_label_matrix(label_matrix,*IC);      /*  1.17 */
    return 1;
}




int insert_code(char *filename,int num_line,int opcode, char* buffline, int *index, int* IC, machine_word* code_img)
{
    int flag_error=-1;
    if (opcode != -1)
    {
        if (opcode < 5)
        {
            flag_error=twooperand(filename,num_line,buffline, index, code_img, IC ,opcode);
        }
        else if (opcode > 4 && opcode < 14)
        {
            flag_error=oneoperand(filename,num_line,buffline, index, code_img, IC,opcode);
        }
        else
        {
            flag_error=zerooperand(buffline, index, code_img, IC,opcode);
        }
    }
    return flag_error;
}

/*
 * this function take string and check if it's number argument,if it's it send the number as int if not return -1
 *
 */
int insert_data(char *buffline, int *index, machine_word *data_img, int *dc)
{

    int counter;
    char *string;
    int isnum,i,number;
    int flag_insert=0;
    int place;

    while (buffline[*index]!='\n' && flag_insert!=-1)
    {
        counter=0;
        string= getWord(buffline,index);
        isnum= check_string_is_num(string);

        if(isnum==1)
        {
            place=(*dc)+counter;
            number= atoi(string);
            flag_insert=1;
            data_img[place].type=3;
            data_img[place].word.dataWord.data=number;
            counter++;

        }
        else if(string[0]=='"'&& string[strlen(string)-1]=='"')
        {
            i=1;
            while(string[i]!='"')
            {
                place=(*dc)+counter;
                flag_insert=1;
                number=(int)string[i];
                data_img[place].type=3;
                data_img[place].word.dataWord.data=number;
                i++;
                counter++;
            }
            place=(*dc)+counter;
            data_img[place].type=3;
            data_img[place].word.dataWord.data=0;
            counter++;
        }
        else
            flag_insert=-1;
        *dc=(*dc)+counter;
        pass_comma(buffline,index);

    }
    return flag_insert;
}

int twooperand(char *filename,int num_line,char* buffline, int *index, machine_word* code_img, int* IC,int opcode)
{
    char* op1 ;
    char* op2 ;
    int miun1, miun2;
    int word_index=*IC-IC_INITIAL_VALUE;
    int a,b;
    int flag_error=0;

    op1= getWord(buffline,index);
    pass_comma(buffline,index);
    op2= getWord(buffline,index);
    if(op1[0]=='\0'|| op2[0]=='\0')
    {
        printf("ERROR: in file %s.am at line %d in first pass process, the opcode command needs two arguments. the arguments is '%s' and  '%s'  .  \n", filename, num_line,op1,op2);
        return -1;
    }
    miun1 = find_address(op1);
    miun2 = find_address(op2);
    code_img[word_index].type=0;
    code_img[word_index].word.code.opcode = opcode ;
    code_img[word_index].word.code.src_op = miun1;
    code_img[word_index].word.code.dest_op = miun2;
    code_img[word_index].word.code.ARE = 0;
    (*IC)++;
    if(miun1==3 && miun1==miun2)
    {
        a=(int)op1[1];
        b=(int)op2[1];
        code_img[(*IC)-IC_INITIAL_VALUE].type=2;
        code_img[(*IC)-IC_INITIAL_VALUE].word.reg.ARE = 0 ;
        code_img[(*IC)-IC_INITIAL_VALUE].word.reg.source_reg = (a-48) ;
        code_img[(*IC)-IC_INITIAL_VALUE].word.reg.des_reg = (b-48);
        (*IC)++;
    }
    else{
        flag_error=process_argument(0,op1,miun1,code_img,IC);
        if (flag_error!=-1)
        {
            flag_error=process_argument(1,op2,miun2,code_img,IC);
            if(flag_error==-1)
                printf("ERROR: in file %s.am at line %d in first pass process, failed to process the argument '%s'.  \n", filename, num_line,op2);
        }
        else
            printf("ERROR: in file %s.am at line %d in first pass process, failed to process the argument '%s'.  \n", filename, num_line,op1);
    }
    return flag_error;

}
int oneoperand(char *filename,int num_line,char* buffline, int *index, machine_word* code_img, int* IC, int opcode)
{
    int word_index=*IC-IC_INITIAL_VALUE;
    char* op1;
    int miun1;
    int flag_error=0;


    op1= getWord(buffline,index);
    if(op1[0]=='\0')
    {
        printf("ERROR: in file %s.am at line %d in first pass process, the opcode command needs one argument. the arguments is blank '%s' .  \n", filename, num_line,op1);
        return -1;
    }
    (*index)=pass_spaces(buffline,*index);
    if (buffline[*index]!='\n')
    {
        printf("ERROR: in file %s.am at line %d in first pass process, the opcode command needs one argument. there is more than one argument... \n'%s'  \n", filename, num_line,buffline);
        return -1;
    }
    miun1 = find_address(op1);
    code_img[word_index].type=0;
    code_img[word_index].word.code.opcode = opcode ;
    code_img[word_index].word.code.src_op = 0;
    code_img[word_index].word.code.dest_op = miun1;
    code_img[word_index].word.code.ARE = 0;
    (*IC)++;
    flag_error=process_argument(1,op1,miun1,code_img,IC);
    if(flag_error==-1)
        printf("ERROR: in file %s.am at line %d in first pass process, failed to process the argument '%s'.  \n", filename, num_line,op1);
    return flag_error;
}
int zerooperand(char* word, int *index, machine_word* code_img, int* IC ,int opcode)
{
    int word_index=*IC-IC_INITIAL_VALUE;
    code_img[word_index].type=0;
    code_img[word_index].word.code.opcode=opcode;
    code_img[word_index].word.code.src_op = 0;
    code_img[word_index].word.code.dest_op = 0;
    code_img[word_index].word.code.ARE = 0;
    return 0;
}

int process_argument(int sd,char* op,int miun,machine_word *code_img,int *IC)
{
    int i=0,num;
    char *str;
    int a;

    switch (miun) {
        case 0:{
            i=1;
            str=getWord(op,&i);
            num= atoi(str);
            code_img[(*IC)-IC_INITIAL_VALUE].type=1;
            code_img[(*IC)-IC_INITIAL_VALUE].word.add.ARE = 0 ;
            code_img[(*IC)-IC_INITIAL_VALUE].word.add.data = num ;
            (*IC)++;
        }
            break;
        case 1:{
            code_img[(*IC)-IC_INITIAL_VALUE].type=-1;
            (*IC)++;
        }
            break;
        case 2:{
            a=(int)op[strlen(op)-1];
            if (a!=49 && a!=50)         /* invalid cell in struct (only 1 or 2) */
                return -1;
            else
            {
                code_img[(*IC)-IC_INITIAL_VALUE].type=-1;
                (*IC)++;
                code_img[(*IC)-IC_INITIAL_VALUE].type=1;
                code_img[(*IC)-IC_INITIAL_VALUE].word.add.ARE = 0 ;
                code_img[(*IC)-IC_INITIAL_VALUE].word.add.data = (a-48) ;
                (*IC)++;
            }
        }
            break;
        default:{
            if(compare_reg(op)==-1)
                return -1;
            a=(int)op[1];
            code_img[(*IC)-IC_INITIAL_VALUE].type=2;
            code_img[(*IC)-IC_INITIAL_VALUE].word.reg.ARE = 0 ;
            if(sd==0)
            {
                code_img[(*IC)-IC_INITIAL_VALUE].word.reg.source_reg = (a-48) ;
                code_img[(*IC)-IC_INITIAL_VALUE].word.reg.des_reg = 0;
            }
            else{
                code_img[(*IC)-IC_INITIAL_VALUE].word.reg.source_reg = 0 ;
                code_img[(*IC)-IC_INITIAL_VALUE].word.reg.des_reg = (a-48);
            }
            (*IC)++;
        }
    }
    return 0;
}

