#include the paths of different source files
include sources.mk

#different types of flags for different functionalities
CC= gcc
BBB= arm-linux-gnueabihf-gcc
CFLAGS= -O0 -Wall -g -std=c99 
EXE= project
EXEBB= project_B
DPFLAG= -Wl,-Map,$@.map

#phony protection for all targets
#native and cross compiler
.PHONY: all
all: compile Cross_arm

.PHONY: build
build: compile Cross_arm

#generates the executable file
.PHONY: compile
compile: $(EXE)

#generates the preprocessed file
.PHONY: preprocess
preprocess:$(PRE) 

#generates the assembly files
.PHONY: asm-file
asm-file : $(ASM)

#cross compiler for Beaglebone
.PHONY: Cross_arm
Cross_arm : $(EXEBB)

#individual files compilation
.PHONY: %.o
%.o: %.c 
	mkdir -p object
	$(CC) $(CFLAGS) -c $< -o object/$@

%.i: %.c 
	mkdir -p preprocess
	touch preprocess/$@
	$(CC) $(CFLAGS) -E $< -o preprocess/$@
	cpp $< >preprocess/$@

%.s: %.c
	mkdir -p assembly
	$(CC) $(CFLAGS) -S $< -o assembly/$@ 

%.asm:%.c 
	mkdir -p assembly
	$(CC) $(CFLAGS) -S $< -o assembly/$@

#compile object files
.PHONY: compile-all
compile-all: $(OBJ)
			
#scp command for Beaglebone			
.PHONY: upload
upload: Cross_arm
	scp $(EXEBB) root@192.168.7.2:/home/debian/bin

#clean the files
.PHONY: clean
clean: 
	rm -r object
	rm -r assembly
	rm -r preprocess
	rm -f $(EXE)
	rm -f $(EXE).map
	rm -f $(EXEBB)
	rm -f $(EXEBB).map

#executable file for native compiler
$(EXE) : $(OBJ)
	$(CC) $(CFLAGS) $(DPFLAG) -o $@ $^
	cp -R ./object/* .
	objdump -s $(EXE)
	size $(EXE)	

#executable file for Beaglebone
$(EXEBB) : $(SRC)
	$(BBB) $(CFLAGS) $(DPFLAG) -o $(EXEBB) $^
	size $(EXEBB)

#generate the archive library
.PHONY: build-lib
build-lib: $(SRC) 
	ar ru libproject1.a 
	ranlib libproject1.a
