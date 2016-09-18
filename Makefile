
include sources.mk

CC= gcc
BBB= rm-linux-gnueabihf-gcc
CFLAGS= -O0 -Wall -g -std=c99
EXEC= project
PROG= main.c hw1.c
DPFLAG= -Map,-M

.PHONY: all
all: compile

.PHONY: compile
compile: $(EXE)

.PHONY: preprocess
preprocess:$(PRE) 


.PHONY: asm-file
asm-file : $(ASM)

.PHONY: %.o
%.o: %.c 
	mkdir -p object
	$(CC) $(CFLAGS) -c $< -O object/$@

%.s: %.c
	mkdir -p assembly
	$(CC) $(CFLAGS) -S $< -o assembly/$@ 

%.asm:%.c 
	mkdir -p assembly
	$(CC) $(CFLAGS) -S $< -o assembly/$@

%.i: %.c
	mkdir -p preprocess
	touch preprocess/$@
	$(CC) $(CFLAGS) -E  $< preprocess/$@
	cpp $< >preprocess/$@

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
	rm -r object
	rm -r assembly
	rm -r preprocess
	rm -f $(EXE)
	rm -f $(EXE).map

$(EXE) : $(OBJ)
	$(CC) $(CFLAGS) $(DPFLAG) -o $@ $^
	
	size $(EXE)	

.PHONY: build-lib
build-lib: 
	ar rcs libproject1.a $@
