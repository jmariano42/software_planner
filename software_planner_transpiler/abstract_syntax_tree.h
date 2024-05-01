#ifndef ASTNODE_H
#define ASTNODE_H

#include <string>
#include <vector>

class ASTNode {
public:
	ASTNode(const std::string& type) : type(type) {}

	void addChild(ASTNode* child) {
		children.push_back(child);
	}

	std::string type;
	std::vector<ASTNode*> children;
};

#endif