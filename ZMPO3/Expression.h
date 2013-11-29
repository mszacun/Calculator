#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <vector>
#include <stack>

#include "SymbolTable.h"
#include "ErrorCode.h"
#include "ExpressionNode.h"
#include "OperatorFactory.h"
#include "ExpressionParser.h"

class Expression
{
	public:
		Expression();
		~Expression();

		ErrorCode Evaluate(SymbolTable& symbol_table, double& result_placeholder);

		ErrorCode ToInfix(std::string& result_placeholder);
		ErrorCode ToPostfix(std::string& result_placeholder);

		void FindUndefinedVariables(const SymbolTable& table, std::vector<std::string>& result_placeholder);

		ErrorCode SetInfixInput(const std::string& input);
		ErrorCode SetPostfixInput(const std::string& input);

		static bool IsPostfix(const std::string& input);

	protected:
		Node* root;

		ErrorCode CreateOperatorNodeAndLoadArguments(const std::string& op_name,
			std::stack<Node*>& operands, Operator*& result_placeholder);

		double StringToDouble(const std::string& str) const;
		void CleanUp(std::stack<Node*> stack);
	
};

#endif