CC= gcc
BBB= rm-linux-gnueabihf-gcc
CFLAGS= -O0 -Wall -g -std=c99
EXEC= project
PROG= main.c hw1.c
DPFLAG= -Map,-M

.PHONY: all
all: native Cross_Arm

.PHONY: preprocess
preprocess: 
	$(CC) $(PROG) -E  file.i

.PHONY: asm-file
asm- file : $(ASM)
	$(CC) $(PROG) -S  file.s

.PHONY: %.o
%.o: %.c 
	$(CC) $(CFLAGS) -c file.o

%.s: %.c
	$(CC) -S $< -o $@ $(CFLAGSi)

%.asm-file:$(PROG)
	$(CC) $(PROG) -S $^

%.e: %.c
	$(CC) -c $< $@ $(CFLAGS)

.PHONY: compile-all
compile-all: %.o
	$(CC) $(CFLAGS) -c $(OBJ)

.PHONY: build
build:
	$(CC) $(CFLAGS) main.c hw1.c
	

.PHONY: upload
upload:
	scp  root@192.168.7.2:/home/debian/bin

.PHONY: clean
clean: 
	-rm -rf *.o *.s hw1 hw2 
