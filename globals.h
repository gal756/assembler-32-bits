#ifndef GLOBALS_H
#define GLOBALS_H

#define MAX_WORD_LENGTH 15
#define MAX_LINE_LENGTH 81
#define IC_INITIAL_VALUE 100
#define MAX_MEMORY_PLACE 156
#define MAX_TABLE_LABLE_SIZE 100
#define MAX_TABLE_MACROS_SIZE 10
#define MAX_MACRO_LENGTH 240
#define MAX_MACRO_NAME 10

typedef struct macro{
    char macroname[MAX_MACRO_NAME];
    char *macrobuff;
}macro;

enum line_type { code, data, external,entry };

typedef struct label {
    char* labal_name;
    int index;
    enum line_type type;
}label;


/*
 * type of instuction word coding
 */
typedef struct code_word {
    unsigned int ARE : 2;
    unsigned int dest_op : 2;
    unsigned int src_op : 2;
    unsigned int opcode : 4;
} code_word;

/*
 * type of addres word coding
 */
typedef struct add_word {
    unsigned int ARE : 2;
    unsigned int data : 8;
} add_word;

/*
 * type of registers word coding
 */
typedef struct reg_word {
    unsigned int ARE : 2;
    unsigned int des_reg : 4;
    unsigned int source_reg : 4;
}reg_word;

/*
 * type of address data coding
 */
typedef struct data {
    unsigned int data : 10;
}data_word;

typedef struct machine_word {
    int type;
    /*
     *  this field contains the type of word of machine word,if 0 it's code ,if 1 it's address word ,if it's register word 2 and 3 if it's data word
     */
    union word {
        code_word code;
        add_word add;
        reg_word reg;
        data_word dataWord;
    } word;
} machine_word;




#endif