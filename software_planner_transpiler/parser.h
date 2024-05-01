#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <vector>
#include "abstract_syntax_tree.h"
#include "token.h"

class Parser {
public:
	Parser(const std::vector<Token>& tokens) : tokens(tokens) {}

	ASTNode* parse() {
		//Parser logic here
		return new ASTNode("test");
	}

private:
	std::vector<Token> tokens;
};

#endif