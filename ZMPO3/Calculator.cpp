#include "Calculator.h"

Calculator::Calculator()
{
}

Calculator::~Calculator()
{
}

ErrorCode Calculator::ToPostfix(std::string& result_placeholder)
{
	return _expression.ToPostfix(result_placeholder);
}

ErrorCode Calculator::ToInfix(std::string& result_placeholder)
{
	return _expression.ToInfix(result_placeholder);
}

ErrorCode Calculator::SetExpression(const std::string& input)
{
	if (input.empty())
		return ErrorCode(ErrorCode::ERROR_CODE_EMPTY_EXPRESSION_ENTERED, ErrorCode::ERROR_MSG_EMPTY_EXPRESSION_ENTERED);
	if (Expression::IsPostfix(input))
		return _expression.SetPostfixInput(input);
	else
		return _expression.SetInfixInput(input);
}

ErrorCode Calculator::SetVariable(const std::string& input)
{
	Expression tmp;
	ErrorCode error;
	double result;
	
	if (Expression::IsPostfix(input))
	{
		if (error = tmp.SetPostfixInput(input))
			return tmp.Evaluate(_symbol_table, result);
		else
			return error;
	}
	else
	{
		if (error = tmp.SetInfixInput(input))
			return tmp.Evaluate(_symbol_table, result);
		else
			return error;
	}
}

void Calculator::SetVariable(const std::string& var_name, double value)
{
	_symbol_table.SetValue(var_name, value);
}

ErrorCode Calculator::Calculate(double& result_placeholder)
{
	return _expression.Evaluate(_symbol_table, result_placeholder);
}

void Calculator::ClearVariables()
{
	_symbol_table.EraseAll();
}