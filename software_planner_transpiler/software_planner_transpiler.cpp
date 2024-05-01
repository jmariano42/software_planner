// software_planner_transpiler.cpp : Defines the entry point for the application.
//

#include "abstract_syntax_tree.h"
#include "code_generator.h"
#include "lexer.h"
#include "parser.h"
#include "token.h"
#include "software_planner_transpiler.h"

using namespace std;

int main(int argc, char *argv[])
{
	std::string filepath = "";

	//Check if file path was provided
	if (argc < 2) {
		bool debug = true;
		
		if (debug)
		{
			filepath = "C:\\Development\\software_planner\\test\\dsl_test.txt";
		}
		else
		{
			std::cerr << "Usage: " << argv[0] << " <filepath>\n";
			return 1; //Exit with error code
		}
	}
	else
	{
		filepath = argv[1];
	}

	//Open file
	std::ifstream inputFile(filepath);

	//Check if open was successful
	if (!inputFile.is_open()) {
		std::cerr << "Error opening the file: " << argv[1] << std::endl;
		return 1; //Exit with error code
	}

	//Read file content into string
	std::string fileContent((std::istreambuf_iterator<char>(inputFile)), (std::istreambuf_iterator<char>()));

	//Close file
	inputFile.close();

	//Tokenize file content
	Lexer lexer(fileContent);
	std::vector<Token> tokens = lexer.tokenize();

	//Parse tokens
	Parser parser(tokens);
	ASTNode* astRoot = parser.parse();

	//Generate code based on AST
	CodeGenerator generator(astRoot);
	generator.generateCode();

	std::cout << "File content:\n" << fileContent;

	//Exit successfully
	return 0;
}
