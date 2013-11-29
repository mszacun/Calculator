#ifndef EXPRESSION_PARSER
#define EXPRESSION_PARSER

#include <iostream>
#include <cassert>

#include "OperatorFactory.h"

class ExpressionParser
{
	public:
		enum TOKEN { OPERATOR, NUMBER, VARIABLE, LEFT_PARENTHESE, RIGHT_PARENTHESE,
			WHITESPACE, AMBIGUOUS, FORBIDDEN_CHARACTER, END };
		static const int  NUMBER_OF_TYPES_OF_TOKENS = 6;

		ExpressionParser();
		ExpressionParser(const std::string& input);
		~ExpressionParser();

		TOKEN GetNextToken(std::string& result_placeholder);
		
		void SetInputString(const std::string& input);

		static void TestPrivateFunctions();
		static std::string GetOpeningParenthese(const std::string& closing_parenthese);

		static bool IsOperatorPrefix(const std::string& str);
		static bool IsOperator(const std::string& str);

		static bool IsNumberPrefix(const std::string& str);
		static bool IsNumber(const std::string& str);

		static bool IsVariablePrefix(const std::string& str);
		static bool IsVariable(const std::string& str);

		static bool IsLeftParenthese(const std::string& str);
		static bool IsRightParenthese(const std::string& str);

		static bool IsWhiteSpacePrefix(const std::string& str);
		static bool IsWhiteSpace(const std::string& str);

		static bool IsForbiddenCharacter(char str);

	private:
		std::string   _input;
		unsigned int  _position;

		int CountTrue(std::vector<bool> arg, int& last_true);
		void CheckPossibilities(std::vector<bool>& result_placeholder, const std::string& token);
		void CheckMatches(std::vector<bool>& result_placeholder, const std::string& token);
};

#endif
