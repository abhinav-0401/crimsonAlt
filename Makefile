CFLAG = -Wall
CC = g++
INCLUDE = -I src/

.PHONY: clean clean-leftover run

crimson: build/main.o build/token.o build/lexer.o build/ast.o build/parser.o build/typechecker.o
	@echo "Creating build directory"
	mkdir -p build
	@echo "Linking object files"
	mv *.o build/
	$(CC) build/*.o -o build/crimson
	rm build/*.o

build/main.o: src/main.cpp
	@echo "Compiling main.cpp"
	$(CC) $(CFLAG) $(INCLUDE) -c src/main.cpp -o main.o

build/token.o: src/lexer/token.cpp
	@echo "Compiling token.cpp"
	$(CC) $(CFLAG) $(INCLUDE) -c src/lexer/token.cpp -o token.o

build/lexer.o: src/lexer/lexer.cpp
	@echo "Compiling lexer.cpp"
	$(CC) $(CFLAG) $(INCLUDE) -c src/lexer/lexer.cpp -o lexer.o

build/ast.o: src/parser/ast.cpp
	@echo "Compiling ast.cpp"
	$(CC) $(CFLAG) $(INCLUDE) -c src/parser/ast.cpp -o ast.o

build/parser.o: src/parser/parser.cpp
	@echo "Compiling parser.cpp"
	$(CC) $(CFLAG) $(INCLUDE) -c src/parser/parser.cpp -o parser.o

build/typechecker.o: src/typechecker/typechecker.cpp
	@echo "Compiling typechecker.cpp"
	$(CC) $(CFLAG) $(INCLUDE) -c src/typechecker/typechecker.cpp -o typechecker.o

clean:
	@echo "Cleaning build dir"
	rm -rf build

clean-leftover:
	rm *.o

run:
	make clean
	make
	clear
	build/crimson
