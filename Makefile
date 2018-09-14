CXX = g++

CFLAGS += -g -Wall -Wpedantic -std=c++11

# Header files contained in the lexer directory
LEXER_HEADERS = lexer/lexer.h lexer/lexer_static_data.h

# Header files contained in the parser directory
PARSER_HEADERS  =  

# Header files contained in the AST directory
AST_HEADERS = AST/alter.h AST/ast.h AST/ast_public.h \
	AST/create.h AST/delete.h AST/drop.h AST/identfier.h \
	AST/insert.h ASTselect.h AST/update.h AST/visitor.h


#
HEADERS = $(LEXER_HEADERS) $(PARSER_HEADERS) $(AST_HEADERS)

lexer:
	$(CXX) $(CFLAGS)


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
