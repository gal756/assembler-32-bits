#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tools.h"
#include "globals.h"
#include "output.h"
#include "labels.h"

void process_output_files(char *filename,label** label_matrix, machine_word* code_img,machine_word* data_img,int IC,int DC)
{
    process_ob_file(filename,code_img,data_img,IC,DC);
    process_ent_file(filename, label_matrix);
}
void process_ob_file(char *filename ,machine_word* code_img,machine_word* data_img,int IC,int DC)
{
    char *output_filename;
    FILE *fp;
    unsigned int *num;
    unsigned int index;
    int first_num,second_num,first_index,seconde_index;
    int i=0,d=0;


    output_filename = (char*)malloc(sizeof(filename) + 4);
    if (output_filename == NULL) {
        printf("Error! memory not allocated.");
        exit(0);
    }
    strcpy(output_filename, filename);
    strcat(output_filename, ".ob");
    fp = fopen(output_filename, "w");
    if(IC-IC_INITIAL_VALUE>31 || DC>31)
    {
        num=(unsigned int*)(&DC);
        index=IC-IC_INITIAL_VALUE;
        first_num=take_5_bits(0, *num);
        second_num=take_5_bits(1, *num);
        first_index=take_5_bits(0,index);
        seconde_index=take_5_bits(1,index);
        fprintf(fp, "\t    %c%c %c%c\n", base32_convert(first_index), base32_convert(seconde_index), base32_convert(first_num), base32_convert(second_num));
    }
    else
        fprintf(fp,"\t    %c %c\n",base32_convert(IC-IC_INITIAL_VALUE),base32_convert(DC));
    while(i<(IC-IC_INITIAL_VALUE))
    {
        num=(unsigned int*)(&code_img[i].word);
        index=IC_INITIAL_VALUE+i;
        first_num=take_5_bits(0, *num);
        second_num=take_5_bits(1, *num);
        first_index=take_5_bits(0,index);
        seconde_index=take_5_bits(1,index);
        fprintf(fp, "\t%c%c\t%c%c\n", base32_convert(first_index), base32_convert(seconde_index), base32_convert(first_num), base32_convert(second_num));
        i++;
    }
    while(d<DC)
    {
        num=(unsigned int*)(&data_img[d].word);
        index=IC_INITIAL_VALUE+i+d;
        first_num=take_5_bits(0, *num);
        second_num=take_5_bits(1, *num);
        first_index=take_5_bits(0,index);
        seconde_index=take_5_bits(1,index);
        fprintf(fp, "\t%c%c\t%c%c\n",base32_convert(first_index), base32_convert(seconde_index), base32_convert(first_num), base32_convert(second_num));
        d++;
    }
    fclose(fp);
}

void process_ent_file(char *filename,label** label_matrix)
{
    char *output_filename;
    FILE *fp;
    int i=0;
    unsigned int *num;
    int first_num,second_num;


    output_filename = (char*)malloc(sizeof(filename) + 4);
    if (output_filename == NULL) {
        printf("Error! memory not allocated.");
        exit(0);
    }
    strcpy(output_filename, filename);
    strcat(output_filename, ".ent");
    fp = fopen(output_filename, "w");
    while(i<get_counter_label())
    {
        if(label_matrix[i]->type==entry)
        {
            num=(unsigned int*)(&label_matrix[i]->index);
            first_num=take_5_bits(0, *num);
            second_num=take_5_bits(1, *num);
            fprintf(fp, "%s\t%c%c\n",label_matrix[i]->labal_name,base32_convert(first_num), base32_convert(second_num));

        }
        i++;
    }
    fclose(fp);
}