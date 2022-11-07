#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "labels.h"
int counter_label = 0;

int checkForLabel(char *str)
{
    int a = 0;
    while (str[a] && (isspace(str[a]) == 0) && (isalpha(str[a]) || isxdigit(str[a]))) {
        a++;
    }
    if (str[a] == ':' && str[a + 1] == '\0')
        return 1;
    else
        return 0;

}

int insertLabel(label** label_matrix, char* word, int index, enum line_type type)
{
    int len;
    if (counter_label == 0)
    {
        label_matrix[counter_label] = (label*)malloc(sizeof(label));
        len = strlen(word);
        label_matrix[counter_label]->labal_name = (char*)malloc((len + 1) * sizeof(char));
        strcpy(label_matrix[counter_label]->labal_name, word);
        label_matrix[counter_label]->index = index;
        label_matrix[counter_label]->type = type;
        counter_label++;

    }
    else
    {
        if (searchLabel(label_matrix, word) == -1)
        {
            len = strlen(word);
            label_matrix[counter_label] = (label*)malloc(sizeof(label));
            label_matrix[counter_label]->labal_name = (char*)malloc(len * sizeof(char));
            label_matrix[counter_label]->labal_name = word;
            label_matrix[counter_label]->index = index;
            label_matrix[counter_label]->type = type;
            (counter_label)++;
        }
        else
            return -1;     /* only if the label exist already */

    }
    return 0;
}
int searchLabel(label** matrix, char* name)
{
    int i = 0;
    int flag = 0;
    while (i < (counter_label) && flag == 0)
    {
        if (strcmp(matrix[i]->labal_name, name) == 0)
            flag = 1;
        i++;
    }
    if (flag == 0 && i >= (counter_label))
    {
        return -1;
    }
    else return i-1;
}

/*
 * this function update the symbol of data in label matrix with the update ic
 */

void update_label_matrix(label** label_matrix,int ic)
{
    int i=0;
    enum line_type type_line=data;
    while(i<counter_label)
    {
        if(label_matrix[i]->type==type_line)
        {
            label_matrix[i]->index+=(ic+1);
        }
        i++;
    }
}

int get_counter_label()
{
    return counter_label;
}

void set_counter_label(int i)
{
    counter_label=i;
}