#include "ExpressionParser.h"

ExpressionParser::ExpressionParser()
{
}

ExpressionParser::ExpressionParser(const std::string& input)
{
	SetInputString(input);
}

ExpressionParser::~ExpressionParser()
{
}

ExpressionParser::TOKEN ExpressionParser::GetNextToken(std::string& result_placeholder)
{
	if (_position >= _input.length())
		return TOKEN::END;

	int token_length = 0;
	std::string token;
	std::vector<bool> possibilities(NUMBER_OF_TYPES_OF_TOKENS, true);
	int last_true;

	do
	{
		token_length++;
		token = _input.substr(_position, token_length);

		CheckPossibilities(possibilities, token);
	}
	while (CountTrue(possibilities, last_true) > 0 && _position + token_length < _input.length());

	// check if we quit loop because of forbidden character
	if (IsForbiddenCharacter(_input[_position + token_length]))
	{
		result_placeholder = _input.substr(_position + token_length, 1);
		return TOKEN::FORBIDDEN_CHARACTER;
	}

	// if we quit loop because of no possibilities we have to go back one character
	if (CountTrue(possibilities, last_true) == 0)
		token_length--;

	token = _input.substr(_position, token_length);
	_position += token_length;

	CheckMatches(possibilities, token);

	result_placeholder = token;
	if (CountTrue(possibilities, last_true) == 1)
		return static_cast<TOKEN>(last_true);
	else
		return TOKEN::AMBIGUOUS;

}

void ExpressionParser::SetInputString(const std::string& input)
{
	_input = input;
	_position = 0;
}

void ExpressionParser::TestPrivateFunctions()
{
	ExpressionParser parser;

	assert(parser.IsNumber("342.45"));
	assert(parser.IsNumber("324"));

	assert(parser.IsNumber("32423.23sad213") == false);

	assert(parser.IsOperatorPrefix("lo"));
	assert(parser.IsOperator("sin"));
	assert(parser.IsOperator("lo") == false);

	assert(parser.IsVariablePrefix("log"));
	assert(parser.IsVariable("log") == false);
}

std::string ExpressionParser::GetOpeningParenthese(const std::string& closing_parenthese)
{
	if (closing_parenthese == ")")
		return "(";
	return 0x00;
}

bool ExpressionParser::IsOperatorPrefix(const std::string& str)
{
	int i = 0;

	while (OperatorFactory::aviable_operators[i] != "" &&
		OperatorFactory::aviable_operators[i].find(str) == std::string::npos)
		i++;

	return OperatorFactory::aviable_operators[i] != "";
}

bool ExpressionParser::IsOperator(const std::string& str)
{
	int i = 0;

	while (OperatorFactory::aviable_operators[i] != "" &&
		OperatorFactory::aviable_operators[i] != str)
		i++;

	return OperatorFactory::aviable_operators[i] != "";
}

bool ExpressionParser::IsNumberPrefix(const std::string& str)
{
	unsigned int i = 0;

	// integer part
	while (i < str.length() && isdigit(str[i])) i++;

	// dot
	if (i < str.length() && str[i] == '.') i++;

	// fractional part
	while (i < str.length() && isdigit(str[i])) i++;

	return i == str.length();
}

bool ExpressionParser::IsNumber(const std::string& str)
{
	return IsNumberPrefix(str) && str[str.length() - 1] != '.';
}


bool ExpressionParser::IsVariablePrefix(const std::string& str)
{
	unsigned int i = 0;

	if (isalpha(str[0]))
	{
		i++;

		while (i < str.length() && (isalpha(str[i]) || isdigit(str[i]) || str[i] == '_'))
			i++;
	}

	return i == str.length();
}

bool ExpressionParser::IsVariable(const std::string& str)
{
	return !IsOperator(str) && IsVariablePrefix(str);
}

bool ExpressionParser::IsLeftParenthese(const std::string& str)
{
	return str.length() == 1 && str[0] == '(';
}

bool ExpressionParser::IsRightParenthese(const std::string& str)
{
	return str.length() == 1 && str[0] == ')';
}

bool ExpressionParser::IsWhiteSpacePrefix(const std::string& str)
{
	int i = 0;

	while (isspace(str[i]))
		i++;

	return i == str.length();
}

bool ExpressionParser::IsWhiteSpace(const std::string& str)
{
	return IsWhiteSpacePrefix(str);
}

bool ExpressionParser::IsForbiddenCharacter(char chr)
{
	return chr == ',' || chr == '<' || chr == '|' || chr == '?' || chr == '>' || chr == '[' || chr == ']' || chr == '{' || chr == '}' || chr == '\'' ||
		chr == '&' || chr == '%' || chr == '$' || chr == '#' || chr == '@' || chr == '!' || chr == '`' || chr == '"' || chr == '\'';
}

int ExpressionParser::CountTrue(std::vector<bool> arg, int& last_true)
{
	unsigned int count = 0;
	last_true = -1;
	
	for (unsigned int i = 0; i < arg.size(); i++)
	{
		if (arg[i])
		{
			count++;
			last_true = i;
		}
	}

	return count;
}

void ExpressionParser::CheckPossibilities(std::vector<bool>& result_placeholder,
	const std::string& token)
{
	result_placeholder[TOKEN::OPERATOR] = IsOperatorPrefix(token);
	result_placeholder[TOKEN::NUMBER] = IsNumberPrefix(token);
	result_placeholder[TOKEN::VARIABLE] = IsVariablePrefix(token);
	result_placeholder[TOKEN::LEFT_PARENTHESE] = IsLeftParenthese(token);
	result_placeholder[TOKEN::RIGHT_PARENTHESE] = IsRightParenthese(token);
	result_placeholder[TOKEN::WHITESPACE] = IsWhiteSpacePrefix(token);
}

void ExpressionParser::CheckMatches(std::vector<bool>& result_placeholder,
	const std::string& token)
{
	result_placeholder[TOKEN::OPERATOR] = IsOperator(token);
	result_placeholder[TOKEN::NUMBER] = IsNumber(token);
	result_placeholder[TOKEN::VARIABLE] = IsVariable(token);
	result_placeholder[TOKEN::LEFT_PARENTHESE] = IsLeftParenthese(token);
	result_placeholder[TOKEN::RIGHT_PARENTHESE] = IsRightParenthese(token);
	result_placeholder[TOKEN::WHITESPACE] = IsWhiteSpace(token);
}
