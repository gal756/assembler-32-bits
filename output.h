#ifndef _OUTPUT_H
#define _OUTPUT_H

/**
 * this function process the files ".ob" and ".ent" by send the params to another functions.
 * @param filename the name of the file that we want to create files
 * @param label_matrix the array of pointers to labels that we saved.
 * @param code_img the array of the machine word as code.
 * @param data_img the array of the machine word as data.
 * @param IC the IC counter.
 * @param DC the DC counter.
 */
void process_output_files(char *filename,label** label_matrix, machine_word* code_img,machine_word* data_img,int IC,int DC);

/**
 * this function responsible to create the ".ob" output file.
 * @param filename the name of the file that we want to create files
 * @param code_img the array of the machine word as code.
 * @param data_img the array of the machine word as data.
 * @param IC the IC counter.
 * @param DC the DC counter.
 */
void process_ob_file(char *filename ,machine_word* code_img,machine_word* data_img,int IC,int DC);

/**
 * this function responsible to create the ".ent" output file.
 * @param filename the name of the file that we want to create files
 * @param label_matrix the array of pointers to labels that we saved.
 */
void process_ent_file(char *filename,label** label_matrix);

#endif