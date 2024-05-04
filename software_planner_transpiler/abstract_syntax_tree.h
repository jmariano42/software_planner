#ifndef ASTNODE_H
#define ASTNODE_H

#include <string>
#include <vector>
#include "token_type.h"
#include "token.h"

class ASTNode {
public:
	ASTNode(TokenType type, Token token) : type(type), token(token) {}

	void addChild(ASTNode* child) {
		children.push_back(child);
	}

	TokenType type;
	Token token;
	std::vector<ASTNode*> children;
};

#endif