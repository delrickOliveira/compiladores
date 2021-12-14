paku: paku.y paku.l
	make clean 
	bison -d paku.y --debug -Wcounterexamples
	flex -o paku.l.c paku.l
	gcc -o paku  paku.l.c paku.tab.c -ll -lm 

clean:
	rm -f paku.l.c paku.tab.c paku.tab.h paku

debug: paku.y paku.l
	bison --debug -d paku.y 
	flex -o paku.l.c paku.l
	gcc -o paku paku.l.c paku.tab.c -ll -lm 