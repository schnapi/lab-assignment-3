#!/bin/sh

# if num of arg. is equal 2
if [ "$#" -ne 1 ]; then
  echo "Only one argument is acceptable."
  echo "Example: ./c-driver.sh bcd.calc"
  exit 1
fi

#runs the compiler
make

runableObjectFile=`echo $1 | sed 's/.calc$//'`
#run program, input is text from $1
cCode=`cat "$1" | bin/calc3c`


SRC="src/$runableObjectFile.c"

# write code to c file

cat src/c-stack-machine/head.c > $SRC
printf "%s" "$cCode" >> $SRC
cat src/c-stack-machine/tail.c >> $SRC

gcc $SRC src/c-stack-machine/functions.c src/c-stack-machine/stack.c -o bin/$runableObjectFile