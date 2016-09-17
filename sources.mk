OBJ =   \
        main.o\
        Project1.o\
        memory.o

SRC =  \
        main.c\
		project.c\
        memory.c

ASM = 	\
		main.s\
		Project.s\
		memory.s\
		main.asm\
		Project.asm\
		memory.asm

PREP = \

		main.i\
		Project.i\
		memory.i                   

vpath %.o
vpath %.h
vpath %.i
vpath %.s

