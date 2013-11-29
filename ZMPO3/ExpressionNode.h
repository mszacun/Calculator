#ifndef NODE_H
#define NODE_H

#include <sstream>
#include <vector>
#include <climits>

#include "ErrorCode.h"
#include "SymbolTable.h"

class Node
{
	public:
		Node(int priority) { _priority = priority; }
		virtual ~Node() {}

		virtual ErrorCode  Evaluate(SymbolTable& symbol_table, double& result) = 0;

		virtual std::string ToInfix() = 0;
		virtual std::string ToPostfix() = 0;

		virtual void FindUndefinedVariables(const SymbolTable& symbol_table, std::vector<std::string>& result_placeholder) = 0;
		int GetPriority() { return _priority; }
		
	private: 
		int _priority;
};

class NumberNode : public Node
{
	public:
		NumberNode(double value) : Node(INT_MAX), _value(value) {};
		virtual ~NumberNode() {};

		virtual ErrorCode Evaluate(SymbolTable& symbol_table, double& result_placeholder) { result_placeholder = _value; return ErrorCode(); }

		virtual std::string ToInfix() { std::ostringstream strs; strs << _value; return strs.str(); }
		virtual std::string ToPostfix() { return ToInfix(); }
		
		virtual void FindUndefinedVariables(const SymbolTable& symbol_table, std::vector<std::string>& result_placeholder) {}

	private:
		double _value;
};

class VariableNode : public Node
{
	public:
		VariableNode(const std::string& var_name) : Node(INT_MAX), _var_name(var_name) {}
		virtual ~VariableNode() {}

		virtual ErrorCode Evaluate(SymbolTable& symbol_table, double& result_placeholder) { return symbol_table.GetValue(_var_name, result_placeholder); }

		virtual std::string ToInfix() { return _var_name; }
		virtual std::string ToPostfix() { return _var_name; }

		virtual void FindUndefinedVariables(const SymbolTable& symbol_table, std::vector<std::string>& result_placeholder)
		{
			if (!symbol_table.IsDefined(_var_name)) result_placeholder.push_back(_var_name);
		}

	private:
		std::string _var_name;
};

#endif