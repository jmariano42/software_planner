#ifndef LEXER_H
#define LEXER_H

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "token.h"

class Lexer {
public:
	Lexer(const std::string& input) : input(input) {}

	std::vector<Token> tokenize() {
		std::vector<Token> tokens;

		std::vector<std::string> src = splitStringOnNewLine(input);

		while (!src.empty()) {
			std::string line = src.front();
			src.erase(src.begin());

			uint8_t tabCount = 0;

			for (char c : line) {
				if (c != '\t') {
					break;
				}

				tabCount++;
			}

			std::vector<std::string> src2 = splitStringOnSpace(line);

			Token token = Token();
			token.tabs = tabCount;

			while (!src2.empty()) {
				std::string word = src2.front();
				src2.erase(src2.begin());

				if (isModifier(word)) {
					token.modifier = toModifier(word);
				} else if (isScope(word)) {
					token.scope = toScope(word);
				} else if (isType(word)) {
					token.type = toType(word);
				} else if (isDataType(word)) {
					token.dataType = toDataType(word);
				} else {
					if (token.value.empty()) {
						token.value = word;
					} else {
						token.additionValue = word;
					}
				}
			}

			tokens.push_back(token);
		}

		return tokens;
	}

	bool isDataType(std::string& input) {
		bool ret = false;
		
		std::string str = input;

		std::transform(str.begin(), str.end(), str.begin(), ::toupper);

		if (str == "DATETIME" || str == "INT" || str == "STRING" || str == "VOID")
		{
			ret = true;
		}

		return ret;
	}

	bool isModifier(std::string& input) {
		bool ret = false;

		std::string str = input;

		std::transform(str.begin(), str.end(), str.begin(), ::toupper);

		if (str == "C" || str == "CPP" || str == "CS" || str == "GO" || str == "JS" || str == "RUST" || str == "PYTHON") {
			ret = true;
		}

		return ret;
	}

	bool isScope(std::string& input) {
		bool ret = false;

		std::string str = input;

		std::transform(str.begin(), str.end(), str.begin(), ::toupper);

		if (str == "PRIVATE" || str == "PROTECTED" || str == "PUBLIC") {
			ret = true;
		}

		return ret;
	}

	bool isType(std::string& input) {
		bool ret = false;

		std::string str = input;

		std::transform(str.begin(), str.end(), str.begin(), ::toupper);

		if (str == "CLASS" || str == "COTR" || str == "DIR" || str == "FIELD" || str == "FILE" || str == "INC" || str == "METD" || str == "PROP" || str == "REF" || str == "USE" || str == "CSSLN" || str == "CSPROJ") {
			ret = true;
		}

		return ret;
	}

	std::vector<std::string> splitStringOnNewLine(const std::string& input) {
		std::vector<std::string> lines;
		std::istringstream iss(input);
		std::string line;

		while (std::getline(iss, line)) {
			lines.push_back(line);
		}

		return lines;
	}

	std::vector<std::string> splitStringOnSpace(const std::string& input) {
		std::vector<std::string> words;
		std::istringstream iss(input);
		std::string word;

		while (iss >> word) {
			words.push_back(word);
		}

		return words;
	}

	TokenDataType toDataType(std::string& input) {
		TokenDataType tokenDataType = NADT;

		std::string str = input;

		std::transform(str.begin(), str.end(), str.begin(), ::toupper);

		if (str == "DATETIME") {
			tokenDataType = DateTime;
		} else if (str == "INT") {
			tokenDataType = Int;
		} else if (str == "STRING") {
			tokenDataType = String;
		} else if (str == "VOID") {
			tokenDataType = Void;
		}

		return tokenDataType;
	}

	TokenModifier toModifier(std::string& input) {
		TokenModifier tokenModifier = NAM;

		std::string str = input;

		std::transform(str.begin(), str.end(), str.begin(), ::toupper);

		if (str == "C") {
			tokenModifier = C;
		} else if (str == "CPP") {
			tokenModifier = CPP;
		} else if (str == "CS") {
			tokenModifier = CS;
		} else if (str == "GO") {
			tokenModifier = GO;
		} else if (str == "JS") {
			tokenModifier = JS;
		} else if (str == "RUST") {
			tokenModifier = Rust;
		} else if (str == "PYTHON") {
			tokenModifier = Python;
		}
		
		return tokenModifier;
	}

	TokenScope toScope(std::string& input) {
		TokenScope tokenScope = NAS;

		std::string str = input;

		std::transform(str.begin(), str.end(), str.begin(), ::toupper);

		if (str == "PRIVATE") {
			tokenScope = Private;
		} else if (str == "PROTECTED") {
			tokenScope = Protected;
		} else if (str == "PUBLIC") {
			tokenScope = Public;
		}

		return tokenScope;
	}

	TokenType toType(std::string& input) {
		TokenType tokenType = NONE;

		std::string str = input;

		std::transform(str.begin(), str.end(), str.begin(), ::toupper);

		if (str == "CLASS") {
			tokenType = Class;
		} else if (str == "COTR") {
			tokenType = Constructor;
		} else if (str == "DIR") {
			tokenType = Directory;
		} else if (str == "FIELD") {
			tokenType = Field;
		} else if (str == "FILE") {
			tokenType = File;
		} else if (str == "INC") {
			tokenType = Include;
		} else if (str == "METD") {
			tokenType = Method;
		} else if (str == "PROP") {
			tokenType = Property;
		} else if (str == "REF") {
			tokenType = Reference;
		} else if (str == "USE") {
			tokenType = Using;
		} else if (str == "CSSLN") {
			tokenType = CSharpSolution;
		} else if (str == "CSPROJ") {
			tokenType = CSharpProject;
		}

		return tokenType;
	}

private:
	std::string input;
};

#endif