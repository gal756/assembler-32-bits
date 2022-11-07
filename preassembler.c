#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "preassembler.h"
#include "tools.h"
#include "globals.h"
#include "labels.h"



FILE* preassembler(FILE *fptr ,char *filename){
    char buff_line[MAX_LINE_LENGTH];
    int macroplace,flag,i,j;
    FILE *fptr1;
    char *output_file_name;
    int have_macro=0;
    int macro_counter=0;
    macro **macroarr;
    int flag_error = -1;
    int counter_lines=0;
    char *word;



    macroarr=(macro **)malloc(MAX_TABLE_MACROS_SIZE*sizeof(macro *));
    if(macroarr == NULL) {
        printf("Error! memory not allocated.\n");
        return NULL;
    }
    output_file_name = (char *) malloc(sizeof(filename)+4);
    if(output_file_name == NULL) {
        printf("Error! memory not allocated.\n");
        return NULL;
    }
    strcpy(output_file_name,filename);
    strcat(output_file_name, ".am");
    fptr1 = fopen(output_file_name,"w+");
    if (fptr == NULL){
        printf("Error: file %s is no have access to writing \n",output_file_name);
        free(output_file_name);
        return NULL;
    }

    while (fgets(buff_line,MAX_LINE_LENGTH,fptr)) {             /*  0.1 */

        counter_lines++;
        i = 0;
        macroplace = -1;
        if (is_blank_line(buff_line))
        {
            fprintf(fptr1,"%s",buff_line);
            continue;
        }
        i=pass_spaces(buff_line,i);
        j=i;
        macroplace=isMacro(macroarr,buff_line,i,macro_counter);
        word= getWord(buff_line,&j);
        if(macroplace==-1 && checkOpcode(word) == -1 &&
           check_prompt_type(word, 0) == -1 && checkForLabel(word)==0 && check_equals_strings(word, 0, "macro")==0 && is_blank_line(buff_line)==0)  /* macro name not defined before */
        {
            printf("ERROR: in file %s at line %d , macro name %s was not defined \n",filename,counter_lines,word);
            flag_error = counter_lines;
        }

        else if (macroplace !=-1)                               /*  0.2 */
            /* it's find macro in the table so we need to print the buff of the macro */
            fprintf(fptr1,"%s",macroarr[macroplace]->macrobuff);


        else
        {
            j = 0;
            if (check_equals_strings(buff_line, i, "macro"))        /*  0.3 */
            {
                have_macro = 1;                                     /*  0.4 */
                macroarr[macro_counter] = (macro *) malloc(sizeof(macro));
                i = pass_not_spaces(buff_line, i);
                i = pass_spaces(buff_line, i);
                word= getWord(buff_line,&i);
                strcpy(macroarr[macro_counter]->macroname, word);                   /*  0.5 */
                i = pass_spaces(buff_line, i);
                word= getWord(buff_line,&i);
                if(word[0]!='\0')       /* to check if there is a macro set with two names (incorrect- m1 m2) */
                {
                    printf("ERROR: in file %s at line %d , there is a duplicate names for the macro name,%s and %s .  \n",filename,counter_lines,macroarr[macro_counter]->macroname,word);
                    flag_error = counter_lines;
                }
                else if (checkOpcode(macroarr[macro_counter]->macroname) != -1 ||
                         check_prompt_type(macroarr[macro_counter]->macroname, 0) != -1)         /* to check if the name of macro is prompt or command (illegal)   */
                {
                    printf("ERROR: in file %s at line %d , there is a illegal name of macro %s .  \n",filename,counter_lines,macroarr[macro_counter]->macroname);
                    flag_error = counter_lines;
                }
                else {      /*it's the first line from the macro lines definitions */           /*  0.6 */
                    macroarr[macro_counter]->macrobuff = (char *) malloc(MAX_MACRO_LENGTH * sizeof(char));
                    flag = 0;
                    while (have_macro == 1 && fgets(buff_line, MAX_LINE_LENGTH, fptr)) /* loop through the rest of the macros lines  */ {
                        counter_lines++;
                        j = 0;
                        j = pass_spaces(buff_line, j);
                        if (check_equals_strings(buff_line, j, "endmacro") == 1)        /*0.7 end of macro-set   */
                            have_macro = 0;                                             /*0.8 */
                        else if (check_equals_strings(buff_line, j, "macro") == 1)      /* to check if there is macro-set inside a macro (illegal)   */
                        {
                            printf("ERROR: in file %s at line %d , there is a macro defined inside macro  .  \n",filename,counter_lines);
                            flag_error = counter_lines;
                        }
                        else {

                            if (flag == 0) {         /*  first line of setting macro */
                                strcpy(macroarr[macro_counter]->macrobuff, buff_line);
                                flag = 1;
                            } else
                                strcat(macroarr[macro_counter]->macrobuff, buff_line);
                        }

                    }
                    macro_counter++;    /*  finish to set the macro in macro array*/
                }
            }
            else
            {
                fprintf(fptr1,"%s",buff_line);
            }


        }
    }
    if(flag_error!=-1)      /*  check for errors (return the line of the first error was found */
    {
        return NULL;
    }
    return fptr1;        /*  return the address for the new file (.am) that was finish writing*/
}



int isMacro(macro **macroarr,char buff_line[],int i,int macro_counter)
{
    int a=0,foundmacro;

    foundmacro=0;
    while(a<macro_counter && foundmacro==0)
    {
        foundmacro=check_equals_strings(buff_line,i,macroarr[a]->macroname);
        a++;
    }
    if (foundmacro == 1)
        return a-1;
    else
        return -1;
}