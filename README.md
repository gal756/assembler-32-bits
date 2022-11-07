# assembler-32-bits-
Project Assembler 32 bits 


## About
This project is an assignment in a C programming course. The purpose of this project is to build an assembler for 16-instruction asssembly language, for an imaginary computer that has a 8 registers with amemory of 256 cells of 10 bits with support only of integers numbers.
This project was done by @Gal Evgi and @Misael rosetsky.

### Directory structure (Modules)
1. `assembler` - main function with argv & argc processing, single file processing.
2. `preassembler` - contains the functions that in charge of pre-assembler process that responsible the macros transplantaion.
3. `first_pass` - contains functions that processing the first pass algorhitm .
4. `second_pass` - contains functions that processing the seconde pass algorhitm .
5. `labels` - contains useful function for processing labels table.
6. `tools` - contains useful function for all the process in the assembler.
7. `globals.h` - contains type and constant definitions.
8. `output` -  contains methods for writing output files: ".ob",".ent" .

