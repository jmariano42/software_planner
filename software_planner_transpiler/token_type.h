#ifndef TOKEN_TYPE_H
#define TOKEN_TYPE_H

enum TokenType {
	NONE = 1,
	Class = 2,
	Constructor = 3,
	Directory = 4,
	Field = 5,
	File = 6,
	Include = 7,
	Method = 8,
	Property = 9,
	Reference = 10,
	Using = 11,
	CSharpSolution = 12,
	CSharpProject = 13
};

#endif