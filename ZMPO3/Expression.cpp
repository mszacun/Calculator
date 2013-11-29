#include "Expression.h"

Expression::Expression() : root(NULL)
{
}

Expression::~Expression()
{
	delete root;
}

ErrorCode Expression::Evaluate(SymbolTable& table, double& result_placeholder)
{
	if (root != NULL)
		return root->Evaluate(table, result_placeholder);	
	else return ErrorCode(ErrorCode::ERROR_CODE_EXPRESSION_NOT_ENTERED, ErrorCode::ERROR_MSG_EXPRESSION_NOT_ENTERED);
}

ErrorCode Expression::ToInfix(std::string& result_placeholder)
{
	if (root != NULL)
	{
		result_placeholder = root->ToInfix();
		return ErrorCode();
	}
	else
		return ErrorCode(ErrorCode::ERROR_CODE_EXPRESSION_NOT_ENTERED, ErrorCode::ERROR_MSG_EXPRESSION_NOT_ENTERED);
}

ErrorCode Expression::ToPostfix(std::string& result_placeholder)
{
	if (root != NULL)
	{
		result_placeholder = root->ToInfix();
		return ErrorCode();
	}
	else
		return ErrorCode(ErrorCode::ERROR_CODE_EXPRESSION_NOT_ENTERED, ErrorCode::ERROR_MSG_EXPRESSION_NOT_ENTERED);
}

void Expression::FindUndefinedVariables(const SymbolTable& table, std::vector<std::string>& result_placeholder)
{
	return root->FindUndefinedVariables(table, result_placeholder);
}

ErrorCode Expression::SetInfixInput(const std::string& input)
{
	ExpressionParser parser;
	std::string token_value;
	ExpressionParser::TOKEN token;
	std::string postfix_result;
	std::stack<std::string> operators_stack;
	
	parser.SetInputString(input);

	while ((token = parser.GetNextToken(token_value)) != ExpressionParser::TOKEN::END)
	{
		if (token == ExpressionParser::TOKEN::FORBIDDEN_CHARACTER)
			return ErrorCode(ErrorCode::ERROR_CODE_FORBIDDEN_CHARACTER_MET, ErrorCode::ERROR_MSG_FORBIDDEN_CHARACTER_MET + token_value);
		if (token == ExpressionParser::TOKEN::NUMBER || token == ExpressionParser::TOKEN::VARIABLE)
			postfix_result += token_value + " ";
		if (token == ExpressionParser::TOKEN::LEFT_PARENTHESE)
			operators_stack.push(token_value);
		if (token == ExpressionParser::TOKEN::RIGHT_PARENTHESE)
		{
			// if the token is closing parenthese and stack is empty, that means, that there was no opening parenthese
			if (operators_stack.empty())
				return ErrorCode(ErrorCode::ERROR_CODE_PARENTHESE_NOT_OPENED, ErrorCode::ERROR_MSG_PARENTHESE_NOT_OPENED);

			while (operators_stack.top() != ExpressionParser::GetOpeningParenthese(token_value))
			{
				postfix_result += operators_stack.top() + " ";
				operators_stack.pop();

				if (operators_stack.empty())
					return ErrorCode(ErrorCode::ERROR_CODE_PARENTHESE_NOT_OPENED, ErrorCode::ERROR_MSG_PARENTHESE_NOT_OPENED);
			}
			operators_stack.pop(); // pop opening parenthese
		}
		if (token == ExpressionParser::TOKEN::OPERATOR)
		{
			while (!operators_stack.empty() &&
				OperatorFactory::OperatorPriority(operators_stack.top()) > OperatorFactory::OperatorPriority(token_value))
			{
				postfix_result += operators_stack.top() + " ";
				operators_stack.pop();
			}
			operators_stack.push(token_value);
		}
	}

	while (!operators_stack.empty())
	{
		if (operators_stack.top() != "(")
		{
			postfix_result += operators_stack.top() + " ";
			operators_stack.pop();
		}
		else
			// if after processing whole input we find '(' on stack, that means it was not closed
			return ErrorCode(ErrorCode::ERROR_CODE_PARENTHESE_NOT_CLOSED, ErrorCode::ERROR_MSG_PARENTHESE_NOT_CLOSED);
	}

	return SetPostfixInput(postfix_result);
}

ErrorCode Expression::SetPostfixInput(const std::string& input)
{
	std::stack<Node*> trees_stack;
	ExpressionParser parser;
	ExpressionParser::TOKEN token;
	std::string token_value;

	parser.SetInputString(input);

	while ((token = parser.GetNextToken(token_value)) != ExpressionParser::TOKEN::END)
	{
		if (token == ExpressionParser::TOKEN::FORBIDDEN_CHARACTER)
			return ErrorCode(ErrorCode::ERROR_CODE_FORBIDDEN_CHARACTER_MET, ErrorCode::ERROR_MSG_FORBIDDEN_CHARACTER_MET + token_value);
		if (token == ExpressionParser::TOKEN::NUMBER)
			trees_stack.push(new NumberNode(StringToDouble(token_value)));
		if (token == ExpressionParser::TOKEN::VARIABLE)
			trees_stack.push(new VariableNode(token_value));
		if (token == ExpressionParser::TOKEN::OPERATOR)
		{
			Operator* operator_node = NULL;
			if (ErrorCode error = CreateOperatorNodeAndLoadArguments(token_value, trees_stack, operator_node))
				trees_stack.push(operator_node);
			else
			{
				// in case of error remeber to free alocated memory
				delete operator_node;
				CleanUp(trees_stack);

				return error;
			}
		}
	}
	if (trees_stack.size() == 1)
	{
		delete root;
		root = trees_stack.top();
	}
	else
	{
		CleanUp(trees_stack);
		return ErrorCode(ErrorCode::ERROR_CODE_TOO_MUCH_OPERANDS_TOO_FEW_OPERATORS, ErrorCode::ERROR_MSG_TOO_MUCH_OPERANDS_TOO_FEW_OPERATORS);
	}
	return ErrorCode();
}

bool Expression::IsPostfix(const std::string& input)
{
	int space_pos = input.find_last_of(' ');
	if (space_pos != std::string::npos)
	{
		std::string last_token = input.substr(space_pos + 1);

		return OperatorFactory::OperatorPriority(last_token) != -1; // if last token is operator, expression is in postfix format
	}
	else
		return false;
}

ErrorCode Expression::CreateOperatorNodeAndLoadArguments(const std::string& op_name,
	std::stack<Node*>& operands, Operator*& result_placeholder)
{
	result_placeholder = OperatorFactory::CreateOperator(op_name);

	for (int i = 0; i < result_placeholder->GetNumberOfArgumentsRequired(); i++)
	{
		if (operands.empty())
			return ErrorCode(ErrorCode::ERROR_CODE_TOO_FEW_ARGUMENTS, ErrorCode::ERROR_MSG_TOO_FEW_ARGUMENTS + op_name);
		else
		{
			result_placeholder->Load_argument(operands.top());
			operands.pop();
		}
	}
	return ErrorCode();
}

double Expression::StringToDouble(const std::string& str) const
{
	return atof(str.c_str());
}

void Expression::CleanUp(std::stack<Node*> trees_stack)
{
	while (!trees_stack.empty())
	{
		delete trees_stack.top();
		trees_stack.pop();
	}
}