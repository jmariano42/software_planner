#ifndef CODE_GENERATOR_H
#define CODE_GENERATOR_H

#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <unordered_map>
#include "abstract_syntax_tree.h"

class CodeGenerator {
public:
	CodeGenerator(ASTNode* root) : root(root) {}

	void generateCode() {
		std::unordered_map<uint8_t, ASTNode*>* lastNodes = new std::unordered_map<uint8_t, ASTNode*>();
		processNode(root, lastNodes);
	}

	void processNode(ASTNode* node, std::unordered_map<uint8_t, ASTNode*>* lastNodes) {
		lastNodes->insert_or_assign(node->token.tabs, node);

		if (node->type == Directory || node->type == File || node->type == CSharpSolution || node->type == CSharpProject) {
			createDirectoryOrFile(node, lastNodes);
		}
		else {
			return;
		}

		for (ASTNode* child : node->children)
		{
			processNode(child, lastNodes);
		}
	}

	void createDirectoryOrFile(ASTNode* node, std::unordered_map<uint8_t, ASTNode*>* lastNodes) {
		if (node->type == Directory) {
			std::filesystem::path path = createPath(node, lastNodes);
			std::filesystem::create_directory(path);
		}
		else {
			std::filesystem::path path = createPath(node, lastNodes);

			if (isSpecialFile(node)) {
				createSpecialFile(path, node, lastNodes);
			}
			else {
				createFile(path, node, lastNodes);
			}
		}
	}

	std::filesystem::path createPath(ASTNode* node, std::unordered_map<uint8_t, ASTNode*>* lastNodes, bool addFilename = true) {
		//todo: make this configurable or a param in cli
		std::filesystem::path basePath = "C:\\Development\\software_planner\\test\\out";
		std::filesystem::path path = basePath;

		for (auto it = lastNodes->begin(); it != lastNodes->end(); it++) {
			if (it->second == node || it->first > node->token.tabs) {
				continue;
			}

			std::filesystem::path lastNodePath = it->second->token.value;

			path = path / lastNodePath;
		}

		std::filesystem::path currentNodePath;

		if (addFilename) {
			if (isSpecialFile(node))
			{
				if (node->type == CSharpSolution) {
					currentNodePath = node->token.value + ".sln";
				}
				else if (node->type == CSharpProject) {
					currentNodePath = node->token.value + ".csproj";
				}
			}
			else {
				currentNodePath = node->token.value;
			}
		}
		
		path = path / currentNodePath;

		return path;
	}

	bool isSpecialFile(ASTNode* node) {
		bool isSpecialFile = false;

		if (node->type == CSharpSolution || node->type == CSharpProject) {
			isSpecialFile = true;
		}

		return isSpecialFile;
	}

	void createSpecialFile(std::filesystem::path path, ASTNode* node, std::unordered_map<uint8_t, ASTNode*>* lastNodes) {
		if (node->type == CSharpSolution) {

			std::filesystem::path path = createPath(node, lastNodes, false);
			std::string stringPath = path.string();
			std::string command = "dotnet new sln -n " + node->token.value + " -o " + stringPath;
			system(command.c_str());
		}
		else if (node->type == CSharpProject) {
			std::filesystem::path path = createPath(node, lastNodes, false);
			std::string stringPath = path.string();
			std::string cdCommand = "cd " + stringPath + "&&";

			std::string createCommand = "dotnet new console -n " + node->token.value + "&&";

			std::string fileName = node->token.value + ".csproj";
			std::string addCommand = "dotnet sln add ./" + node->token.value + "/" + fileName;

			std::string combindedCommands = cdCommand + createCommand + addCommand;

			system(combindedCommands.c_str());
		}
	}

	char randomHexChar() {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(0, 25);
		char base = 'A';
		char result = dis(gen) < 10 ? dis(gen) + '0' : dis(gen) + base;

		while (result == '?' || result == '=' || result == ';' || result == ':' || result == '<' || result == '>' || result == '@') {
			result = dis(gen) < 10 ? dis(gen) + '0' : dis(gen) + base;
		}

		return result;
	}

	std::string generateGuid() {
		std::string guid;

		for (int i = 0; i < 36; ++i) {
			if (i == 8 || i == 13 || i == 18 || i == 23) {
				guid += '-';
			} else {
				guid += randomHexChar();
			}
		}

		return guid;
	}

	void createFile(std::filesystem::path path, ASTNode* node, std::unordered_map<uint8_t, ASTNode*>* lastNodes) {
		std::ofstream file(path);

		if (file.is_open()) {
			for (ASTNode* child : node->children) {
				writeFile(file, child, lastNodes);
			}

			file.close();
		}
	}

	void writeFile(std::ofstream& file, ASTNode* node, std::unordered_map<uint8_t, ASTNode*>* lastNodes) {
		lastNodes->insert_or_assign(node->token.tabs, node);

		if (node->type == Class) {
			if (node->token.modifier == CS) {
				uint8_t grandParentTabCount = node->token.tabs - 2;
				ASTNode* grandParentNode = lastNodes->at(grandParentTabCount);

				std::string fileNamespace = createNamespace(grandParentNode, lastNodes);
				file << "namespace " + fileNamespace + " {\n";

				if (node->token.scope == Private) {
					file << "\tprivate class " + node->token.value + "\n";
				} else if (node->token.scope == Protected) {
					file << "\tprotected class " + node->token.value + "\n";
				} else if (node->token.scope == Public) {
					file << "\tpublic class " + node->token.value + "\n";
				}
				file << "\t{\n";

				for (ASTNode* child : node->children) {
					writeFile(file, child, lastNodes);
				}

				file << "\t}\n";
				file << "}\n";
			}
		} else if (node->type == Field) {
			if (node->token.modifier == CS) {
				std::string dataType = dataTypeToCSharpString(node);

				if (node->token.scope == Private) {
					file << "\t\tprivate " + dataType + ' ' + node->token.value + ";\n";
				} else if (node->token.scope == Protected) {
					file << "\t\tprotected " + dataType + ' ' + node->token.value + ";\n";
				} else if (node->token.scope == Public) {
					file << "\t\tpublic " + dataType + ' ' + node->token.value + ";\n";
				}
			}
		} else if (node->type == Property) {
			if (node->token.modifier == CS) {
				std::string dataType = dataTypeToCSharpString(node);

				if (node->token.scope == Private) {
					file << "\t\tprivate " + dataType + ' ' + node->token.value + " { get => " + node->token.field + "; set => " + node->token.field + " = value; }\n";
				}
				else if (node->token.scope == Protected) {
					file << "\t\tprotected " + dataType + ' ' + node->token.value + " { get => " + node->token.field + "; set => " + node->token.field + " = value; }\n";
				}
				else if (node->token.scope == Public) {
					file << "\t\tpublic " + dataType + ' ' + node->token.value + " { get => " + node->token.field + "; set => " + node->token.field + " = value; }\n";
				}
			}
		} else if (node->type == Constructor) {
			if (node->token.modifier == CS) {
				uint8_t parentTabCount = node->token.tabs - 1;
				ASTNode* parentNode = lastNodes->at(parentTabCount);

				std::string dataType = dataTypeToCSharpString(node);

				if (node->token.scope == Private) {
					file << "\t\tprivate " + parentNode->token.value + "(" + dataType + ' ' + node->token.value + ") {}\n";
				}
				else if (node->token.scope == Protected) {
					file << "\t\tprotected " + parentNode->token.value + "(" + dataType + ' ' + node->token.value + ") {}\n";
				}
				else if (node->token.scope == Public) {
					file << "\t\tpublic " + parentNode->token.value + "(" + dataType + ' ' + node->token.value + ") {}\n";
				}
			}
		} else if (node->type == Method) {
			if (node->token.modifier == CS) {
				std::string dataType = dataTypeToCSharpString(node);

				if (node->token.scope == Private) {
					file << "\t\tprivate " + dataType + ' ' + node->token.value + "() {}\n";
				}
				else if (node->token.scope == Protected) {
					file << "\t\tprotected " + dataType + ' ' + node->token.value + "() {}\n";
				}
				else if (node->token.scope == Public) {
					file << "\t\tpublic " + dataType + ' ' + node->token.value + "() {}\n";
				}
			}
		}
	}

	std::string dataTypeToCSharpString(ASTNode* node) {
		std::string ret;

		if (node->token.dataType == DateTime) {
			ret = "DateTime";
		} else if (node->token.dataType == Int) {
			ret = "int";
		} else if (node->token.dataType == String) {
			ret = "string";
		} else if (node->token.dataType == Void) {
			ret = "void";
		}

		return ret;
	}

	std::string createNamespace(ASTNode* node, std::unordered_map<uint8_t, ASTNode*>* lastNodes) {
		std::string fileNamespace;

		uint8_t counter = node->token.tabs;

		while (counter > 0) {
			if (lastNodes->at(counter)->type == CSharpProject) {
				fileNamespace = lastNodes->at(counter)->token.value;
				break;
			}

			counter--;
		}

		return fileNamespace;
	}

private:
	ASTNode* root;
};

#endif