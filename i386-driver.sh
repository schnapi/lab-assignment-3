#!/bin/sh

# if num of arg. is equal 2
if [ "$#" -ne 1 ]; then
  echo "Only one argument is acceptable."
  echo "Example: ./i386-driver.sh bcd.calc"
  exit 1
fi

case "$1" in
*.calc ) 
        ;;
*)
  echo "Error: File shall contain .calc extension"
  exit 1
        ;;
esac

#remove path
fileName=$(echo $1 | awk -F/ '{print $(NF)}')

#runs the compiler
make

runableObjectFile=`echo $fileName | sed 's/.calc$//'`
#run program, input is text from $1
assemblyCode=`cat "$1" | bin/calc3i`
# assemblyFile
sourceFolder="src"
SRC="$sourceFolder/$runableObjectFile.s"

# write assembly code to assembly file
printf "%s" "$assemblyCode" > $SRC
#we print code for exit here, I could not include this code in calc3i.c
printf '\nexit:\n\tmovl $0,%%ebx # first argument: exit code\n\tmovl $1,%%eax # system call number (sys_exit)\n\tint $0x80 # call kernel\n' >> $SRC

libFolder="lib"
OBJ="$libFolder/$runableObjectFile.o"

gcdOBJ=$libFolder/gcd.lib
gcdSRC=$sourceFolder/gcd.s

factOBJ=$libFolder/fact.lib
factSRC=$sourceFolder/fact.s

lntwoOBJ=$libFolder/lntwo.lib
lntwoSRC=$sourceFolder/lntwo.s

#After that your driver should call ’gcc’ (or ’as’ and ’ld’ separately) to assemble and link the assembly file to produce runnable code
# create and link object files
as --32 -gstabs $SRC -o $OBJ
as --32 -gstabs $gcdSRC -o $gcdOBJ
as --32 -gstabs $lntwoSRC -o $lntwoOBJ
as --32 -gstabs $factSRC -o $factOBJ

# linker, link all object files 
ld -m elf_i386 -nostdlib $OBJ $gcdOBJ $factOBJ $lntwoOBJ -o bin/$runableObjectFile
