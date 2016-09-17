
include sources.mk

CC= gcc
BBB= rm-linux-gnueabihf-gcc
CFLAGS= -O0 -Wall -g -std=c99
EXEC= project
PROG= main.c hw1.c
DPFLAG= -Map,-M

.PHONY: all
all: 

.PHONY: preprocess
preprocess:$(PRE) 


.PHONY: asm-file
asm-file : $(ASM)

.PHONY: %.o
%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

%.s: %.c
	$(CC) $(CFLAGS) -S $< -o $@ 

%.asm:%.c 
	$(CC) $(CFLAGS) -S $< -o $@

%.i: %.c
	$(CC) $(CFLAGS)  $< $@ 

.PHONY: compile-all
compile-all: $(OBJ)
	

.PHONY: build
build:
	$(CC) $(CFLAGS) $(SRC)
	

.PHONY: upload
upload:
	scp  root@192.168.7.2:/home/debian/bin

.PHONY: clean
clean: 
	-rm -rf *.o *.s hw1 hw2 

#.PHONY: build-lib
#build-lib:

