#ifndef _PREASSEMBLER_H
#define _PREASSEMBLER_H

#include "globals.h"
/**
 * the function take the file and make th epre-assembler process that put instead all the macro names
 * in file ,the macro buff that we save in last iteration.the fuction write all the line that unchanged to a new .am
 * file and all the line that have macro name,it's put there the spisific macros lines.
 * @param fptr the file that we want to convert to file with macros set.
 * @param filename the name of the file that we want to write with ".am".
 * @param str2 the second string that have index(most of time the buff line use).
 * @returns if the pre-assembler flow correctly it's will back pointer to the new file ,otherwise return NULL.
 */
FILE* preassembler(FILE *fptr,char *filename);

/**
 * the function check if the macro name in the file is amacro anme that we saved bafore in the
 * macros array
 * @param macroarr the array of the saved macro with name and buffs.
 * @param buffline the correct line in file.
 * @param i the pointer as int of the place word that's wanted to be check.
 * @macro_counter the number of macros that are saved in macroarr
 * @returns if the macro was found in the macroarr it return the place of the macro,otherwise return -1.
 */
int isMacro(macro **macroarr,char buff_line[],int i,int macro_counter);

#endif