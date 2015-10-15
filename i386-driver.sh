#!/bin/sh

# if num of arg. is equal 2
if [ "$#" -ne 1 ]; then
  echo "Only one argument is acceptable."
  echo "Example: ./i386-driver.sh bcd.calc"
  exit 1
fi

if [ "$1" != *.calc ]; then
  echo "Error: File shall contain .calc extension"
  exit 1
fi

runableObjectFile=`echo $1 | sed 's/.calc$//'`
#run program, input is text from $1
assemblyCode=`cat "$1" | bin/calc3i`
# assemblyFile
SRC="$runableObjectFile.s"

assemblyHeader=".code32\n.data\n.bss\n"

# write assembly code to assembly file
printf "%s" "$assemblyCode" > $SRC
echo '\nexit:\n\tmovl $0,%ebx # first argument: exit code\n\tmovl $1,%eax # system call number (sys_exit)\n\tint $0x80 # call kernel\n' >> $SRC

OBJ="$runableObjectFile.o"

#After that your driver should call ’gcc’ (or ’as’ and ’ld’ separately) to assemble and link the assembly file to produce runnable code

#runs the compiler
make
as --32 -gstabs $SRC -o $OBJ
# linker
ld -m elf_i386 $OBJ -o $runableObjectFile
