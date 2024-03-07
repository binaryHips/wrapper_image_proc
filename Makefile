CC = gcc
OPT = -O3 -std=c11
wrapper: ./out/lexer.c ./out/parser.c 
	$(CC) $(OPT) $^ -o $@

./out/lexer.h ./out/lexer.c: ./src/lexer.l
	flex --header-file=./out/lexer.h -o ./out/lexer.c ./src/lexer.l 

./out/parser.h ./out/parser.c: ./src/parser.y
	bison -d -v -o ./out/parser.c ./src/parser.y