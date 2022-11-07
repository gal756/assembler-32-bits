#ifndef _LABELS_H
#define _LABELS_H
#include "globals.h"

/**
 * Update the array of lables.
 * If a sybmol already exist it returns error.
 *
 * @param {label_matrix} array The array to process.
 * @param {word} label name that need to be inserts.
 * @param {index} DC value.
 * @param {type} type of word
 * @returns 0 if the symbol was insert and -1 if the symbol already exist.
 * 
 */
int insertLabel(label**, char*, int, enum line_type);
/**
 * look for if the symbol already exist or it is a new symbol.
 * If a sybmol already exist it returns error.
 *
 * @param {label_matrix} array The array to process.
 * @param {name} the labal name the function is looking for.
 * @returns -1 if the symbol already exist ,otherwise return i ,the symbol's index in the table.
 *
 */

int searchLabel(label**, char*);
/**
 * Checks if it is a valid label name.
 *
 * @param {name} the labal name.
 * @returns 1 for a valid label name and 0 for invalid
 *
 */
int checkForLabel(char *);
int searchLabel(label**, char*);
/**
 * this function update the symbol of data in label matrix with the update ic
 *
 * @param {label_matrix} the labal name.
 * @param {ic} instruction counter.
 *
 */

void update_label_matrix(label** ,int);
/**
 * @returns the number of labels were insert
 *
 */
int get_counter_label();
void set_counter_label(int i);
#endif