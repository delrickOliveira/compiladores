sqlEval: sqlEval.y sqlEval.l
	bison -d sqlEval.y
	flex -o sqlEval.l.c sqlEval.l
	gcc -o sqlEval sqlEval.l.c sqlEval.tab.c -ll -lm 

clean:
	rm -f *.c *.h sqlEval

