#ifndef ASTNODE_H
#define ASTNODE_H

#include <string>
#include <vector>

class ASTNode {
public:
	ASTNode(const TokenType& type) : type(type) {}

	void addChild(ASTNode* child) {
		children.push_back(child);
	}

	TokenType type;
	Token token;
	std::vector<ASTNode*> children;
};

#endif