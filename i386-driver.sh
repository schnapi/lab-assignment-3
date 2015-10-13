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

#runs the compiler
make

runableObjectFile=`echo $1 | sed 's/.calc$//'`
assemblyCode=`cat "$1" | bin/calc3i`
# assemblyFile
SRC="$runableObjectFile.s"
echo "$SRC"
# write assembly code to assembly file
echo "$assemblyCode" > $SRC

OBJ="$runableObjectFile.o"

#After that your driver should call ’gcc’ (or ’as’ and ’ld’ separately) to assemble and link the assembly file to produce runnable code

#as -gstabs $SRC -o $OBJ
## linker
#ld $OBJ -o $runableObjectFile
