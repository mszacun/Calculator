#include "OperatorNodes.h"

Operator::Operator(int number_of_arguments_required, const std::string& operator_name, int priority)
	: Node(priority), _number_of_arguments_required(number_of_arguments_required), 
	_operator_name(operator_name)
{
	_provided_arguments.reserve(number_of_arguments_required);
}

Operator::~Operator()
{
	for (unsigned int i = 0; i < _provided_arguments.size(); i++)
		delete _provided_arguments[i];
}

ErrorCode Operator::Load_argument(Node* arg)
{
	if (_provided_arguments.size() < _number_of_arguments_required)
	{
		_provided_arguments.push_back(arg);
		return ErrorCode();
	}
	else
		return ErrorCode(ErrorCode::ERROR_CODE_TOO_MUCH_ARGUMENTS,
			ErrorCode::ERROR_MSG_TOO_MUCH_ARGUMENTS + _operator_name);
}

int Operator::GetNumberOfArgumentsRequired() const
{
	return _number_of_arguments_required;
}

void Operator::FindUndefinedVariables(const SymbolTable& symbol_table, std::vector<std::string>& result_placeholder)
{
	for (unsigned int i = 0; i < _provided_arguments.size(); i++)
		_provided_arguments[i]->FindUndefinedVariables(symbol_table, result_placeholder);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

OneArgumentOperator::OneArgumentOperator(const std::string& operator_name, int priority) :
	Operator(arguments_required, operator_name, priority)
{
}

OneArgumentOperator::~OneArgumentOperator()
{
}

ErrorCode OneArgumentOperator::Evaluate(SymbolTable& symbol_table, double& result_placeholder)
{
	if (_provided_arguments.size() == _number_of_arguments_required)
	{
		double argument;
		if (ErrorCode argumentResult = _provided_arguments[0]->Evaluate(symbol_table, argument))
		{
			ErrorCode result = Calculate(argument, result_placeholder);
			return result;
		}
		else
			return argumentResult;
	}
	else
		return ErrorCode(ErrorCode::ERROR_CODE_TOO_FEW_ARGUMENTS,
			ErrorCode::ERROR_MSG_TOO_FEW_ARGUMENTS + _operator_name);
}

std::string OneArgumentOperator::ToInfix()
{
	return _operator_name + "(" + _provided_arguments[0]->ToInfix() + ")";
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

TwoArgumentOperator::TwoArgumentOperator(const std::string& operator_name, int priority) 
	: Operator(arguments_required, operator_name, priority)
{

}

TwoArgumentOperator::~TwoArgumentOperator()
{
}

ErrorCode TwoArgumentOperator::Evaluate(SymbolTable& symbol_table, double& result_placeholder)
{
	if (_provided_arguments.size() == _number_of_arguments_required)
	{
		double arg1;
		if (ErrorCode arg1Result = _provided_arguments[0]->Evaluate(symbol_table, arg1))
		{
			double arg2;
			if (ErrorCode arg2Result = _provided_arguments[1]->Evaluate(symbol_table, arg2))
				return Calculate(arg2, arg1, result_placeholder);
			else
				return arg2Result;
		}
		else
			return arg1Result;
	}
	else
		return ErrorCode(ErrorCode::ERROR_CODE_TOO_FEW_ARGUMENTS,
			ErrorCode::ERROR_MSG_TOO_FEW_ARGUMENTS + _operator_name);
}

std::string TwoArgumentOperator::ToInfix()
{
	std::string arg1 = _provided_arguments[0]->ToInfix();
	std::string arg2 = _provided_arguments[1]->ToInfix();

	if (_provided_arguments[0]->GetPriority() < GetPriority())
		arg1 = "(" + arg1 + ")";
	if (_provided_arguments[1]->GetPriority() < GetPriority())
		arg2 = "(" + arg2 + ")";
	return arg2 + _operator_name + arg1;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

const std::string PlusOperator::operator_name = "+";

PlusOperator::PlusOperator() : TwoArgumentOperator(operator_name, operator_priority)
{
}

PlusOperator::~PlusOperator()
{
}

ErrorCode PlusOperator::Calculate(double arg1, double arg2, double& result_placeholder)
{
	result_placeholder = arg1 + arg2;
	return ErrorCode();
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

const std::string MinusOperator::operator_name = "-";

MinusOperator::MinusOperator() : TwoArgumentOperator(operator_name, operator_priority)
{
}

MinusOperator::~MinusOperator()
{
}

ErrorCode MinusOperator::Calculate(double arg1, double arg2, double& result_placeholder)
{
	result_placeholder = arg1 - arg2;
	return ErrorCode();
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

const std::string MultiplyOperator::operator_name = "*";

MultiplyOperator::MultiplyOperator() : TwoArgumentOperator(operator_name, operator_priority)
{
}

MultiplyOperator::~MultiplyOperator()
{
}

ErrorCode MultiplyOperator::Calculate(double arg1, double arg2, double& result_placeholder)
{
	result_placeholder = arg1 * arg2;
	return ErrorCode();
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

const std::string DivideOperator::operator_name = "/";

DivideOperator::DivideOperator() : TwoArgumentOperator(operator_name, operator_priority)
{
}

DivideOperator::~DivideOperator()
{
}

ErrorCode DivideOperator::Calculate(double arg1, double arg2, double& result_placeholder)
{
	if (arg2 != 0)
	{
		result_placeholder = arg1 / arg2;
		return ErrorCode();
	}
	else
		return ErrorCode(ErrorCode::ERROR_CODE_DIVIDE_BY_0, ErrorCode::ERROR_MSG_DIVIDE_BY_0);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

const std::string AssignOperator::operator_name = "=";

AssignOperator::AssignOperator() : TwoArgumentOperator(operator_name, operator_priority)
{
}

AssignOperator::~AssignOperator()
{
}

ErrorCode AssignOperator::Evaluate(SymbolTable& symbol_table, double& result_placeholder)
{
	if (_provided_arguments.size() == _number_of_arguments_required)
	{
		double value;
		if (ErrorCode arg1Result = _provided_arguments[0]->Evaluate(symbol_table, value))
		{
			VariableNode* var_node = dynamic_cast<VariableNode*>(_provided_arguments[1]);
			if (var_node != NULL)
				symbol_table.SetValue(var_node->ToInfix(), value);
			else
				ErrorCode(ErrorCode::ERROR_CODE_INVALID_LEFT_SIDE_ARGUMENT, ErrorCode::ERROR_MSG_INVALID_LEFT_SIDE_ARGUMENT);
		}
		else
			return arg1Result;
	}
	else
		return ErrorCode(ErrorCode::ERROR_CODE_TOO_FEW_ARGUMENTS,
		ErrorCode::ERROR_MSG_TOO_FEW_ARGUMENTS + _operator_name);

	return ErrorCode();
}

ErrorCode AssignOperator::Calculate(double arg1, double arg2, double& result_placeholder)
{
	return ErrorCode();
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

const std::string PowerOperator::operator_name = "^";

PowerOperator::PowerOperator() : TwoArgumentOperator(operator_name, operator_priority)
{
}

PowerOperator::~PowerOperator()
{
}

ErrorCode PowerOperator::Calculate(double arg1, double arg2, double& result_placeholder)
{
	if (arg1 == 0 && arg2 == 0)
		return ErrorCode(ErrorCode::ERROR_CODE_0_TO_0, ErrorCode::ERROR_MSG_0_TO_0);
	result_placeholder = pow(arg1, arg2);
	return ErrorCode();
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

const std::string NegateOperator::operator_name = "~";

NegateOperator::NegateOperator() : OneArgumentOperator(operator_name, operator_priority)
{
}

NegateOperator::~NegateOperator()
{
}

ErrorCode NegateOperator::Calculate(double arg, double& result_placeholder)
{
	result_placeholder = -arg;
	return ErrorCode();
}

std::string NegateOperator::ToInfix()
{
	std::string arg = _provided_arguments[0]->ToInfix();
	if (_provided_arguments[0]->GetPriority() < GetPriority())
		arg = "(" + arg + ")";
	return _operator_name + arg;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

const std::string LogOperator::operator_name = "log";

LogOperator::LogOperator() : OneArgumentOperator(operator_name, operator_priority)
{
}

LogOperator::~LogOperator()
{
}

ErrorCode LogOperator::Calculate(double arg, double& result_placeholder)
{
	if (arg > 0)
	{
		result_placeholder = log(arg);
		return ErrorCode();
	}
	else
		return ErrorCode(ErrorCode::ERROR_CODE_LOG_ARGUMENT_LESS_THEN_0, ErrorCode::ERROR_MSG_LOG_ARGUMENT_LESS_THAN_0);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

const std::string SinOperator::operator_name = "sin";

SinOperator::SinOperator() : OneArgumentOperator(operator_name, operator_priority)
{
}

SinOperator::~SinOperator()
{
}

ErrorCode SinOperator::Calculate(double arg, double& result_placeholder)
{
	result_placeholder = sin(arg);
	return ErrorCode();
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

const std::string CosOperator::operator_name = "cos";

CosOperator::CosOperator() : OneArgumentOperator(operator_name, operator_priority)
{
}

CosOperator::~CosOperator()
{
}

ErrorCode CosOperator::Calculate(double arg, double& result_placeholder)
{
	result_placeholder = cos(arg);
	return ErrorCode();
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

const std::string TgOperator::operator_name = "tg";

TgOperator::TgOperator() : OneArgumentOperator(operator_name, operator_priority)
{
}

TgOperator::~TgOperator()
{
}

ErrorCode TgOperator::Calculate(double arg, double& result_placeholder)
{
	result_placeholder = tan(arg);
	return ErrorCode();
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

const std::string CtgOperator::operator_name = "ctg";

CtgOperator::CtgOperator() : OneArgumentOperator(operator_name, operator_priority)
{
}

CtgOperator::~CtgOperator()
{
}

ErrorCode CtgOperator::Calculate(double arg, double& result_placeholder)
{
	result_placeholder = 1 / tan(arg);
	return ErrorCode();
}
