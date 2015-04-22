all:
	lex src/try1.l
	yacc -d --debug --verbose src/try4.y 
	gcc lex.yy.c y.tab.c -o bin/codegen

clean:
	rm lex.yy.c
	rm y.tab.c
	rm y.tab.h
	rm y.output
	rm bin/codegen
	rm ans.s
	rm ans.o
	rm ans
	rm code.s
	rm data.s


