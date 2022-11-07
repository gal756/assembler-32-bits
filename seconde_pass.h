#ifndef _SECONDEPASS_H
#define _SECONDEPASS_H
#include "globals.h"

/**
 * this function make tha seconde pass algorhitm on the filename file and fill the
 * mchinnes word that not completed
 * @param filename the name of the file that we reading
 * @param fptr pointer to the file.
 * @param IC pointer to the IC counter.
 * @param label_matrix matrix array of the pointer to the labels struct that we saved.
 * @param code_img the array of the machine words of code.
 * @returns 1 for read without errors ,otherwise 0.
 */
int seconde_pass(char *filename,FILE* fptr, int* IC, label** label_matrix, machine_word* code_img);
/**
 * fill the missing adresses
 * @param filename the name of the file that we reading
 * @param temp pointer to opcode
 * @param buff_line pointer to the line we are coding
 * @param index pointer the the end of the las word we extract
 * @param counter is an index for code_img.
 * @param label_matrix matrix array of the pointer to the labels struct that we saved.
 * @param code_img the array of the machine words storage for code usage
 * returns 0 if all missing words were filled successfully
 */
int address_completion(char *filename,char *filename_ext,int num_line,char *temp,char *buff_line,int *index,int *counter,label** label_matrix, machine_word* code_img);
/**
* translate all external label addressed to 32 base
* @param output_filename the file of adress in 32 base
* @param  label_matrix matrix array of the pointer to the labels struct that we saved.
* @param op is the labal name
* @param code_img the array of the machine words storage for code usage
* @param counter is an a pointer to a index for code_img.
* returns 0 for successful translate,otherwise -1.
 */
int update_miss_op(char *output_filename,label** label_matrix,char *op,machine_word* code_img,int *counter);
/**
 * extract the label name without the number
 * @param word full operand name
 */
void process_addressing_method(char* word);


#endif