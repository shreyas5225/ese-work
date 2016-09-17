CC= gcc
BBB= rm-linux-gnueabihf-gcc
CFLAGS= -O0 -Wall -g -std=c99
EXEC= project

.PHONY: all
all: native Cross_Arm

.PHONY: preprocess
preprocess: 
	$(CC) -E main.c -o file.i

.PHONY: asm-file
asm file : $(ASM)
	$(CC) -S main.c -o file.s

.PHONY: %.o
%.o: %.c $(DEP)
	$(CC) $@ $< $(CFLAGS)

%.s: %.c
	$(CC) -S $< -o $@ $(CFLAGS)

%.asm: %.c
	$(CC) -E $< -o $@ $(CFLAGS)

%.e: %.c
	$(CC) -c $< $@ $(CFLAGS)

.PHONY: compile-all2
compile-all2: %.o
	$(CC) -c $< -o $@ $(CFLAGS)

.PHONY: build
build: %.c
	

.PHONY: upload
upload:
	scp root@192.168.7.2

.PHONY: clean
clean: 
	-rm -rf *.o 
