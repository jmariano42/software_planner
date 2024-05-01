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
		if (tokens.empty()) {
			return nullptr;
		}

		ASTNode* root = ASTNode(tokens[0].type);

		for (const auto& token : tokens) {
			ASTNode* node = new ASTNode(token.type);

			//remove 1st node because that will be your root node
			//loop through tokens and split tokens vector when token count decreases
			//each split will contain tokens that belong to the tree under one of the children of the root node
			//may have to recursively process tokens going 1 tab deeper each recursion

			root->addChild(node);
		}

		return new ASTNode(root);
	}

private:
	std::vector<Token> tokens;
};

#endif