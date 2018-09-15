CXX = g++

CFLAGS += -g -Wall -Wpedantic -std=c++11

# Header files contained in the lexer directory
__LEXER_HEADERS = lexer/lexer.h lexer/lexer_static_data.h

# Header files contained in the parser directory
__PARSER_HEADERS  =  

# Header files contained in the AST directory
__AST_HEADERS = AST/alter.h AST/ast.h AST/ast_public.h \
	AST/create.h AST/delete.h AST/drop.h AST/identfier.h \
	AST/insert.h ASTselect.h AST/update.h AST/visitor.h

# A convenience variable containing all the header files
HEADERS = $(__LEXER_HEADERS) $(__PARSER_HEADERS) $(__AST_HEADERS)

# All the AST object files
__AST_OBJECT_FILES = ast.o create.o drop.o insert.o

# Convenience variable for all object files
OBJECT_FILES = simple.o lexer/lexer.o parser/parser.o $(__AST_OBJECT_FILES)

# Makes the SimpleSQL executable
all: lexer/lexer.o parser/parser.o simplesql.o
	$(CXX) $(CFLAGS) -o simple $(OBJECT_FILES)

# A target that compiles object files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CFLAGS) -c $<


# A target for removing editor backups, executables, and object files
clean:
	find . -name "#*#" -delete
	find . -name ".#*" -delete
	find . -name '*~' -delete
	find . -name '*.o' -delete
	find . -name '*.out' -delete
	rm -f simple
