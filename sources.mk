#include different source files in makefile and list their path
OBJ =   \
  main.o\
  project_1.o\
  memory.o

SRC =  \
 main.c\
 project_1.c\
  memory.c

ASM = 	\
  main.s\
  project_1.s\
  memory.s\
  main.asm\
  project_1.asm\
  memory.asm

PRE  = \
	main.i\
    project_1.i\
    memory.i   


VPATH: memory project_1 

vpath %.o object 
vpath %.h Headers 
vpath %.i preprocess
vpath %.s assembly
vpath %.asm assembly
