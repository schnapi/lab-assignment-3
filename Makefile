FOLDER = lexyacc-code/
all:
	# y.tab.c, y.tab.h && #lex.yy.c
	cd $(FOLDER) && bison -y -d calc3.y && flex calc3.l
	#object files, lex.yy.o, y.tab.o
	cd $(FOLDER) && gcc -c y.tab.c lex.yy.c
	cd $(FOLDER) && gcc y.tab.o lex.yy.o calc3i.c -o ../bin/calc3i # i386
	cd $(FOLDER) && gcc y.tab.o lex.yy.o calc3c.c -o ../bin/calc3c # c
	cd $(FOLDER) && mv -t buildCode y.tab.c y.tab.h lex.yy.c lex.yy.o y.tab.o
	
clean:
	cd $(FOLDER)buildCode && rm -f y.tab.c y.tab.h lex.yy.c lex.yy.o y.tab.o
	rm -f bin/calc3i
	rm -f bin/calc3c