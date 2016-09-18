OBJ =   \
        main.o\
       # Project1.o\
       # memory.o

SRC =  \
        main.c\
		project.c\
        memory.c

ASM = 	\
		main.s\
		main.asm
		#Project.s\
		#memory.s\
		#Project.asm\
		#memory.asm

PRE  = \
		main.i\
		#Project.i\
	    #memory.i    

VPATH: memory Project1

vpath %.o object 
vpath %.h header 
vpath %.i preprocess
vpath %.s assembly 
