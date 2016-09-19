
Sources.mk file contains the paths defined for the files and the list of different files

Makefile details can be listed as follows: 
 
1) CC flag is used to define gcc compiler for the host machine and arm-linux-gnueabihf-gcc has been used to cross compile on BeagleBone

 
2)The use of the differnet CFLAGS used in compilation can be defined as follows:

     -O0- used to define optimization levels
   -Wall- used to display all Warnings 
      -g- used to enable debugging options
-std=c99- used to define c99 standard

3) DPFLAG used in the compilation statement can be defined as follows:
           
   -Wl,-Map,file.map- used to generate the mapfile for linker operations

4) All the targets used in the makefile have been phony protection

5)  The different targets used in the makefile are

	all-: generate the executable file for native compiler
	build-:generate the executable file for native compiler
	compile-all-: generate the object files in the list without linking
	preprocess-: generate the preprocessed files from the source files
	asm-file-: generate the assembly files from the source files
	clean-: remove the different types of generated files and directories by makefile
	upload-: move the cross-compiler generated executable file to the Beaglebone Board
	
6) The directory object is used to store the object files generated   

7) The directory preprocess is used to store the preprocessed files generated   

8) The directory assembly is used to store the assembly files generated 

9) Different targets such as %.i,%.s,%.asm,%.o are defined to have generic functionality.

10) The executable file is made available in the terminal itself.
