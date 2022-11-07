#ifndef _TOOLS_H
#define _TOOLS_H

/**
 * Checks if the next word in str1 from index a is equal to the word in str2
 * @param str1 the first string that have index(most of time the buff line use).
 * @param a the index for read word in str1.
 * @param str2 the second string that have index(most of time the buff line use).
 * @returns 1 for string equals ,otherwise 0.
 */
int check_equals_strings(char str1[], int a, char str2[]);

/**
 * the function take a word from the index i of the line ,and update the i to the index after word taken.
 * @param line the line that reading
 * @param i the index for read word in line.
 * @returns a pointer to array of string that the function allocate and put the word.
 */
char* getWord(char* line, int* i);

/**
 * the function move the index while the place is a space.
 * @param a the line that reading
 * @param i the index in line.
 * @returns the index after move all white spaces.
 */
int pass_spaces(char* a, int i);

/**
 * the function move the index while the place is not aspace.
 * @param a the line that reading
 * @param i the index in line.
 * @returns the index after move all not white spaces.
 */
int pass_not_spaces(char* a, int i);

/**
 * the function move the index to pass the comma.
 * @param buff_line the line that reading
 * @param i the pointer to index in line.
 */
void pass_comma(char *buff_line,int *index);

/**
 * the function check if the line is blank .
 * @param buff_line the line that reading
 * @return 1 if it's blank line, otherwise 0.
 */
int is_blank_line(char *buff_line);

/**
 * this function take string and check if it's number argument.
 * @param string pointer to the word
 * @return 1 if it's number word, otherwise 0.
 */
int check_string_is_num(char *string);

/**
 * this function check if the word is a saved word of opcode command.
 * @param word pointer to the string
 * @return the index of the number of the opcode command, otherwise -1.
 */
int checkOpcode(char* word);

/**
 * this function check whats the address type of the argument given.
 * @param arg pointer to the string
 * @return the number of the address type.
 */
int find_address(char* arg);

/**
 * this function check if the argument is register argument.
 * @param arg pointer to the string
 * @return 1 if it's legal register argument,-1 if not legal register,otherwise 0 .
 */
int compare_reg(char* arg);

/**
 * this function check if there is a point (.) inside the word given.
 * @param word pointer to the string
 * @return 1 if the word include point char(.),0 otherwise.
 */
int look_point(char* word);

/**
 * this function check if the word in str from index i is aprompt type command.
 * @param str pointer to the string.
 * @param a the index of the first char of the word.
 * @return 0 if it's ".data" ,1 for ".string",2 for ".struct" ,3 for ".entry"
 * 4 for ".extern" and -1 if it's not ,-2 if it word not legal that start with point.
 */
int check_prompt_type(char *str, int a);

/**
 * this function take 5 bits from acode word that have 10 bits .
 * @param location 0 for 5 firsts bits , 1 for 5 end bits of the num.
 * @param num the code word that we want extract the 5 bits
 * @return the 5 bits of the num that chosen as a int.
 */
int take_5_bits(int ,unsigned int);

/**
 * take take the number a that we want to change from base 10 to 32.
 * @param a the int number in base 10.
 * @return the char that present the number in base 32.
 */
char base32_convert(int a);

#endif