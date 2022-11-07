#ifndef _FIRSTPASS_H
#define _FIRSTPASS_H

/**
 * make the process of first_pass by the given algorhitm
 * 
 * @param fptr the file that we read from
 * @param filename The name of file that we make the  pass
 * @param DC the pointer to the dc counter
 * @param IC the pointer to the dc counter
 * @param label_matrix the array of pointer of label struct that storage the labels
 * @param code_img the array of the machine words storage for code usage
 * @param data_img the array of the machine words storage for data usage
 * @returns 1 if the first_pass read was complete without errors, else it returns 0
 */
int first_pass(FILE* fptr,char *filename, int* DC, int* IC, label** label_matrix, machine_word* code_img,machine_word* data_img);

/**
 * codes the sentence and insert the word of code to code_img table
 *
 * @param {buffline} the line need to be coded
 * @param {index} the index of the pointer to place in the line that need to be codec
 * @param {code_img} code img table
 *  @param {IC} the pointer to the IC counter
 * @returns 0 if the sentence was coded and inserted to the table correct, else it returns -1
 */
int insert_code(char *filename,int num_line,int opcode, char* buffline, int *index, int* IC, machine_word* code_img);

/**
 * codes the sentence and insert the a word data to data_img table
 *
 * @param {buffline} the line need to be coded
 * @param {index} pointes the a word inside the sentence
 * @param {code_img} code table
 *  @param {DC} the pointer to the DC counter
 * @returns 0,1 if the sentence was coded and inserted to the table correct, else it returns -1
 */
int insert_data(char *buffline, int *index, machine_word *data_img, int *dc);

/**
 * codes a two operand sentence
 *
 * @param {buffline} the line need to be coded
 * @param {index} pointes the a word inside the sentence
 * @param {code_img} code table
 * @param {IC} the pointer to the ic counter
 * @param {opcode} opcode num
 * @returns 0 if the sentence was coded and inserted to the table, else it returns -1
 */
int twooperand(char *filename,int num_line,char* buffline, int *index, machine_word* code_img, int* IC,int opcode);
/**
 * codes a one operand sentence
 *
 * @param {buffline} the line need to be coded
 * @param {index} pointes the a word inside the sentence
 * @param {code_img} code table
 * @param {IC} the pointer to the ic counter
 * @param {opcode} opcode num
 * @returns 0 if the sentence was coded and inserted to the table, else it returns -1
 */
int oneoperand(char *filename,int num_line,char* buffline, int *index, machine_word* code_img, int* IC, int opcode);
/**
 * codes a zero operand sentence
 *
 * @param {word} the line need to be coded
 * @param {index} pointes the a word inside the sentence
 * @param {code_img} code table
 * @param {IC} the pointer to the ic counter
 * @param {opcode} opcode num
 * @returns 0 if the sentence was coded and inserted to the table, else it returns -1
 */
int zerooperand(char* word, int *index, machine_word* code_img, int* IC ,int opcode);
/**
 * codes the sentence by the type of adress and update the IC
 *
 * @param {sd} sign of source operand
 * @param {op} opcode name
 * @param {miun} addressing method
 * @param {code_img} code table
 * @param {IC} the pointer to the ic counter
 * @return 0 if no errors,otherwise -1
 */
int process_argument(int sd,char* op,int miun,machine_word *code_img,int *IC);


#endif