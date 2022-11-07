#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tools.h"
#include "globals.h"

/* the base 32 array of chars that represent the number .example 6 in base 32 is base32[6]= '&' */
char base32[32] = {'!','@','#','$','%','^','&','*','<','>','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v'};
/* strings array that represent all the legal registers */
char* registers[8] = { "r0","r1","r2","r3","r4","r5","r6","r7" };
/* strings array that represent all the legal opcodes commands by there opcode */
char* opcodes[16] = { "mov","cmp","add","sub","not","clr","lea","inc","dec","jmp","bne","get","prn","jsr","rts","hlt" };

int check_equals_strings(char str1[], int a, char str2[])
{
    int b = 0;
    while (str1[a] && str2[b] && (isspace(str1[a]) == 0) && str1[a] == str2[b]) {
        a++;
        b++;
    }
    if ((isspace(str1[a]) != 0 || str1[a] == '\0' )&& str2[b] == '\0')
        /*
         * strings equals
         */
        return 1;
    else
        return 0;
}

char* getWord(char line[], int* i)
{
    char* word;
    int start, end;
    word = (char*)malloc(50 * sizeof(char));
    start = pass_spaces(line, *i);
    if (*i > MAX_LINE_LENGTH)
        return NULL;
    end = pass_not_spaces(line, start);
    *i = end;

    strncpy(word, line + start, end - start);
    word[end - start] = '\0';
    return word;
}

int pass_spaces(char a[], int i)
{
    while (a[i] && isspace(a[i]) != 0 && i < 80 && a[i]!='\n')
        i++;
    return i;
}

int pass_not_spaces(char a[], int i)
{
    while (a[i] && isspace(a[i]) == 0 && i < 80 && a[i]!=',')
        i++;
    return i;
}

void pass_comma(char *buff_line,int *index)
{
    while (buff_line[*index]!=',' && buff_line[*index]!='\n')
        (*index)++;
    if (buff_line[*index]==',')
        (*index)++;

}
int is_blank_line(char *buff_line)
{
    int p=0;
    while(buff_line[p]==' '||buff_line[p]=='\t')
        p++;
    if(buff_line[p]=='\n')
        return 1;
    return 0;

}
/*
 * this function take string and check if it's number argument,if it's it send the number as int if not return -1
 *
 */
int check_string_is_num(char *string) {
    int i = 0;
    if (string[i] == '+' || string[i] == '-')
        i++;
    while (string[i] != '\0' && isdigit(string[i]))
        i++;
    if (string[i] == '\0')
        return 1;
    return 0;

}

int checkOpcode(char* word)
{
    int i = 0;
    int flag = 0;
    while (flag == 0 && i < 16)
    {
        if (strcmp(word, opcodes[i]) == 0)
        {
            flag = 1;
        }
        i++;
    }
    if (flag == 0)
    {
        return -1;

    }
    return i - 1;
}

int find_address(char* arg)
{
    if (arg[0] == '#')
        return 0;
    else if (compare_reg(arg) == 1 || compare_reg(arg) == -1)
        return 3;
    else if (look_point(arg) == 1)
        return 2;
    else return 1;

}
int compare_reg(char* arg)
{
    int i=0, flag = 0;
    if (arg[0]=='r'){
        while (i<8)
        {
            if (strcmp(arg, registers[i]) == 0)
                flag =1;
            i++;
        }
        if (flag==0 && (arg[1]>=48 && arg[1]<=57 ))
            flag=-1;                        /* not legal register */
    }
    return flag;
}

int look_point(char* word)
{
    int i = 0, flag = 0;
    while (word[i] != '\0')
    {
        if (word[i]=='.')
        {
            flag = 1;
        }
        i++;
    }
    return flag;
}


int check_prompt_type(char str[], int a)
{
    char temp[9];
    int j = 0;

    if (str[a] == '.')
    {
        temp[j] = str[a];
        a++;
        j++;
        while (str[a] && (isspace(str[a]) == 0))
        {
            temp[j] = str[a];
            a++;
            j++;
        }
        temp[j]='\0';
        if (strcmp(temp, ".data") == 0)
            return 0;
        else if (strcmp(temp, ".string") == 0)
            return 1;
        else if (strcmp(temp, ".struct") == 0)
            return 2;
        else if (strcmp(temp, ".entry") == 0)
            return 3;
        else if (strcmp(temp, ".extern") == 0)
            return 4;
        else
            return -2;

    }
    else
        return -1;

}

/*
 * take the 5 firsts bits of num if location 0 ,or the 5 finals bits of num if location 1 .
 * return : the repression int of the 5 chosen bits;
 */
int take_5_bits(int location,unsigned int num)
{
    unsigned int checker=31;
    int result;


    if (location == 0)
    {
        checker = checker << 5;
        result=(int)((num&checker)>>5);
    }
    else
        result=(int)(num&checker);

    return result;
}

char base32_convert(int a)
{
        return base32[a];
}