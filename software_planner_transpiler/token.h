#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include "token_data_type.h"
#include "token_modifier.h"
#include "token_scope.h"
#include "token_type.h"

struct Token {
	TokenDataType dataType;
	TokenModifier modifier;
	TokenScope scope;
	std::uint8_t tabs;
	TokenType type;
	std::string value;
};

#endif