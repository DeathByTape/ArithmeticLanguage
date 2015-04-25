all:
	lex arithlang.l
	yacc -d arithlang.y
	cc lex.yy.c y.tab.c helpers.c -o arithlang

clean:
	rm -rf lex.yy.* y.tab.* arithlang
