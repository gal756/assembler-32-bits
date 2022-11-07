#ifndef _ASSEMBLER_H
#define _ASSEMBLER_H
/**
 * this function is the control function that send that build all the main data and function of the
 * assembler,it's sent the file to the pre-assembler ,first_pass and second pass process.
 * @param filename the name of the file that will make the assembler process.
 * @return 1 if all the assembler process work fluent ,otherwise 0.
 */
int process_file(char *filename);

#endif