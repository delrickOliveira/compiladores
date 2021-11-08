htmlEval: htmlEval.y htmlEval.l
	bison -d htmlEval.y
	flex -o htmlEval.l.c htmlEval.l
	gcc -o htmlEval htmlEval.l.c htmlEval.tab.c -ll -lm 

clean:
	rm -f *.c *.h htmlEval

