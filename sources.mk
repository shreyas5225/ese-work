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

vpath %.o object 
vpath %.h header 
vpath %.i preprocessed 
vpath %.s assembly 
