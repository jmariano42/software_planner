#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include "abstract_syntax_tree.h"
#include "token.h"

class Parser {
public:
	Parser(const std::vector<Token>& tokens) : tokens(tokens) {}

	ASTNode* parse() {
		ASTNode* root = new ASTNode(tokens[0].type, tokens[0]);
		tokens.erase(tokens.begin());

		std::unordered_map<uint8_t, ASTNode*>* lastNodes = new std::unordered_map<uint8_t, ASTNode*>();
		lastNodes->insert_or_assign(root->token.tabs, root);

		determineTokenGroups(lastNodes, tokens, 1);

		return root;
	}

	void determineTokenGroups(std::unordered_map<uint8_t, ASTNode*>* lastNodes, std::vector<Token> tokens, std::uint8_t count) {
		std::vector<Token> carryTokens = tokens;

		for (Token token : tokens) {
			if (token.tabs == count) {
				ASTNode* node = new ASTNode(token.type, token);
				uint8_t parentCount = count - 1;
				lastNodes->at(parentCount)->addChild(node);
				carryTokens.erase(carryTokens.begin());
				lastNodes->insert_or_assign(count, node);
			}
			else {
				count = token.tabs;
				determineTokenGroups(lastNodes, carryTokens, count);
				return;
			}
		}
	}

private:
	std::vector<Token> tokens;
};

#endif