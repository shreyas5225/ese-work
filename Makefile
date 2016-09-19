
include sources.mk

CC= gcc
BBB= rm-linux-gnueabihf-gcc
CFLAGS= -O0 -Wall -g -std=c99 -I./Headers
EXE= project
EXEBB= project_B
DPFLAG= -Wl,-Map,$@.map

.PHONY: all
all: compile

.PHONY:build
build:compile

.PHONY: compile
compile: $(EXE)

.PHONY: preprocess
preprocess:$(PRE) 


.PHONY: asm-file
asm-file : $(ASM)

.PHONY: %.o
%.o: %.c 
	mkdir -p object
	$(CC) $(CFLAGS) -c $< -o object/$@

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
	cp -R ./object/* .
	objdump -s $(EXE)
	size $(EXE)	

.PHONY: build-lib
build-lib: main.c hw1.c 
	ar ru libproject1.a 
	ranlib libproject1.a
