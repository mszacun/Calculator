#ifndef OPERATOR_H
#define OPERATOR_H

#include <vector>
#include <cmath>

#include "ErrorCode.h"
#include "ExpressionNode.h"

class Operator : public Node
{
	public:
		Operator(int number_of_arguments_required, const std::string& operator_name, int priority);
		virtual ~Operator();

		virtual ErrorCode Load_argument(Node* arg);
		int GetNumberOfArgumentsRequired() const;

		virtual void FindUndefinedVariables(const SymbolTable& symbol_table, std::vector<std::string>& result_placeholder);

	protected:
		std::vector<Node*> _provided_arguments;
		unsigned int       _number_of_arguments_required;
		std::string        _operator_name;
};

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

class OneArgumentOperator : public Operator
{
	public:
		const static int arguments_required = 1;

		OneArgumentOperator(const std::string& operator_name, int priority);
		virtual ~OneArgumentOperator();

		virtual ErrorCode Evaluate(SymbolTable& symbol_table, double& result_placeholder);

		virtual ErrorCode Calculate(double arg, double& result_placeholder) = 0;

		virtual std::string ToPostfix() { return _provided_arguments[0]->ToPostfix() + " " + _operator_name; }
		virtual std::string ToInfix();
};

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

class TwoArgumentOperator : public Operator
{
	public:
		const static int arguments_required = 2;

		TwoArgumentOperator(const std::string& operator_name, int priority);
		virtual ~TwoArgumentOperator();

		virtual ErrorCode Evaluate(SymbolTable& symbol_table, double& result_placeholder);

		virtual ErrorCode Calculate(double arg1, double arg2, double& result_placeholder) = 0;

		virtual std::string ToPostfix() { return _provided_arguments[0]->ToPostfix() + " " + _provided_arguments[1]->ToPostfix() + " " +_operator_name; }
		virtual std::string ToInfix();
};

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

class PlusOperator : public TwoArgumentOperator
{
	public:
		static const int operator_priority = 1;
		static const std::string operator_name;

		PlusOperator();
		virtual ~PlusOperator();

		virtual ErrorCode Calculate(double arg1, double arg2, double& result_placeholder);
};

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

class MinusOperator : public TwoArgumentOperator
{
	public:
		static const int operator_priority = 1;
		static const std::string operator_name;

		MinusOperator();
		virtual ~MinusOperator();

		virtual ErrorCode Calculate(double arg1, double arg2, double& result_placeholder);
};

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

class MultiplyOperator : public TwoArgumentOperator
{
	public:
		static const int operator_priority = 2;
		static const std::string operator_name;

		MultiplyOperator();
		virtual ~MultiplyOperator();

		virtual ErrorCode Calculate(double arg1, double arg2, double& result_placeholder);
};

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

class DivideOperator : public TwoArgumentOperator
{
	public:
		static const int operator_priority = 2;
		static const std::string operator_name;

		DivideOperator();
		virtual ~DivideOperator();

		virtual ErrorCode Calculate(double arg1, double arg2, double& result_placeholder);
};

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

class AssignOperator : public TwoArgumentOperator
{
	public:
		static const int operator_priority = 0;
		static const std::string operator_name;

		AssignOperator();
		virtual ~AssignOperator();

		virtual ErrorCode Evaluate(SymbolTable& symbol_table, double& result_placeholder);
		virtual ErrorCode Calculate(double arg1, double arg2, double& result_placeholder);
};

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

class PowerOperator : public TwoArgumentOperator
{
	public:
		static const int operator_priority = 4;
		static const std::string operator_name;

		PowerOperator();
		virtual ~PowerOperator();

		virtual ErrorCode Calculate(double arg1, double arg2, double& result_placeholder);
};

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

class NegateOperator : public OneArgumentOperator
{
	public:
		static const int operator_priority = 3;
		static const std::string operator_name;

		NegateOperator();
		virtual ~NegateOperator();

		virtual ErrorCode Calculate(double arg, double& result_placeholder);

		virtual std::string ToInfix();
};

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

class LogOperator : public OneArgumentOperator
{
	public:
		static const int operator_priority = 5;
		static const std::string operator_name;
		LogOperator();
		virtual ~LogOperator();

		virtual ErrorCode Calculate(double arg, double& result_placeholder);
};

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

class SinOperator : public OneArgumentOperator
{
	public:
		static const int operator_priority = 5;
		static const std::string operator_name;

		SinOperator();
		virtual ~SinOperator();

		virtual ErrorCode Calculate(double arg, double& result_placeholder);
};

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

class CosOperator : public OneArgumentOperator
{
	public:
		static const int operator_priority = 5;
		static const std::string operator_name;

		CosOperator();
		virtual ~CosOperator();

		virtual ErrorCode Calculate(double arg, double& result_placeholder);
};

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

class TgOperator : public OneArgumentOperator
{
	public:
		static const int operator_priority = 5;
		static const std::string operator_name;

		TgOperator();
		virtual ~TgOperator();

		virtual ErrorCode Calculate(double arg, double& result_placeholder);
};

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

class CtgOperator : public OneArgumentOperator
{
	public:
		static const int operator_priority = 5;
		static const std::string operator_name;

		CtgOperator();
		virtual ~CtgOperator();

		virtual ErrorCode Calculate(double arg, double& result_placeholder);
};

#endif