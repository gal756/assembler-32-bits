# Basic compilation macros
CC = gcc # GCC Compiler
CFLAGS = -ansi -Wall -pedantic # Flags
GLOBAL_DEPS = globals.h # Dependencies for everything
EXE_DEPS = assembler.o preassembler.o tools.o first_pass.o seconde_pass.o labels.o output.o # Deps for exe

## Executable
assembler: $(EXE_DEPS) $(GLOBAL_DEPS)
	$(CC) -g $(EXE_DEPS) $(CFLAGS) -o $@

## Main:
assembler.o: assembler.c assembler.h $(GLOBAL_DEPS)
	$(CC) -c assembler.c  $(CFLAGS) -o $@

## Preassembler:
preassembler.o: preassembler.c  preassembler.h $(GLOBAL_DEPS)
	$(CC) -c preassembler.c $(CFLAGS) -o $@
	
## Code tools functions:
tools.o: tools.c tools.h $(GLOBAL_DEPS)
	$(CC) -c tools.c $(CFLAGS) -o $@

## First Pass:
first_pass.o: first_pass.c first_pass.h $(GLOBAL_DEPS)
	$(CC) -c first_pass.c $(CFLAGS) -o $@

## Second Pass:
seconde_pass.o: seconde_pass.c seconde_pass.h $(GLOBAL_DEPS)
	$(CC) -c seconde_pass.c $(CFLAGS) -o $@


## labels functions:
labels.o: labels.c labels.h $(GLOBAL_DEPS)
	$(CC) -c labels.c $(CFLAGS) -o $@

## Output Files:
output.o: output.c output.h $(GLOBAL_DEPS)
	$(CC) -c output.c $(CFLAGS) -o $@

# Clean Target (remove leftovers)
clean:
	rm -rf *.o
