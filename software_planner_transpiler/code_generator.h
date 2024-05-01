#ifndef CODE_GENERATOR_H
#define CODE_GENERATOR_H

#include <iostream>
#include <string>
#include "abstract_syntax_tree.h"

class CodeGenerator {
public:
	CodeGenerator(ASTNode* root) : root(root) {}

	void generateCode() {
		//Code generation logic here
	}

private:
	ASTNode* root;
};

#endif