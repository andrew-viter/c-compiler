OBJS = main.o lexer.o

lexer: $(OBJS)
	gcc -o lexer $(OBJS)

main.o: main.c lexer.h
	gcc -c main.c

lexer.o: lexer.c lexer.h
	gcc -c lexer.c

.PHONY: clean
clean: 
	rm $(OBJS)