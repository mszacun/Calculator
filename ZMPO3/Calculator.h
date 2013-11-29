#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "Expression.h"
#include "SymbolTable.h"

class Calculator
{
	public:
		Calculator();
		~Calculator();

		ErrorCode ToPostfix(std::string& result_placeholder);
		ErrorCode ToInfix(std::string& result_placeholder);

		ErrorCode SetExpression(const std::string& input);
		ErrorCode Calculate(double& result_placeholder);
		void ClearVariables();

		ErrorCode SetVariable(const std::string& input);
		void SetVariable(const std::string& var_name, double value);

	private:
		SymbolTable _symbol_table;
		Expression _expression;
};

#endif