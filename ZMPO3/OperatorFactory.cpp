#include "OperatorFactory.h"

/*const std::string OperatorFactory::aviable_operators [] = { 
	PlusOperator::operator_name,
	MinusOperator::operator_name,
	MultiplyOperator::operator_name,
	DivideOperator::operator_name,
	NegateOperator::operator_name,
	LogOperator::operator_name,
	SinOperator::operator_name,
	CosOperator::operator_name,
	TgOperator::operator_name,
	CtgOperator::operator_name,
	"" };*/

const std::string OperatorFactory::aviable_operators [] = { "+", "-", "*", "/", "=", "^", "~", "log", "sin", "cos", "tg", "ctg", "" };

Operator* OperatorFactory::CreateOperator(const std::string& op_name)
{
	if (op_name == PlusOperator::operator_name)
		return new PlusOperator();

	if (op_name == MinusOperator::operator_name)
		return new MinusOperator();

	if (op_name == MultiplyOperator::operator_name)
		return new MultiplyOperator();

	if (op_name == DivideOperator::operator_name)
		return new DivideOperator();

	if (op_name == AssignOperator::operator_name)
		return new AssignOperator();

	if (op_name == PowerOperator::operator_name)
		return new PowerOperator();

	if (op_name == NegateOperator::operator_name)
		return new NegateOperator();

	if (op_name == LogOperator::operator_name)
		return new LogOperator();

	if (op_name == SinOperator::operator_name)
		return new SinOperator();

	if (op_name == CosOperator::operator_name)
		return new CosOperator();

	if (op_name == TgOperator::operator_name)
		return new TgOperator();

	if (op_name == CtgOperator::operator_name)
		return new CtgOperator();

	// unknown operator
	return NULL;
}

int OperatorFactory::OperatorPriority(const std::string& op_name)
{
	if (op_name == PlusOperator::operator_name)
		return PlusOperator::operator_priority;

	if (op_name == MinusOperator::operator_name)
		return MinusOperator::operator_priority;

	if (op_name == MultiplyOperator::operator_name)
		return MultiplyOperator::operator_priority;

	if (op_name == DivideOperator::operator_name)
		return DivideOperator::operator_priority;

	if (op_name == AssignOperator::operator_name)
		return AssignOperator::operator_priority;

	if (op_name == PowerOperator::operator_name)
		return PowerOperator::operator_priority;

	if (op_name == NegateOperator::operator_name)
		return NegateOperator::operator_priority;

	if (op_name == LogOperator::operator_name)
		return LogOperator::operator_priority;

	if (op_name == SinOperator::operator_name)
		return SinOperator::operator_priority;

	if (op_name == CosOperator::operator_name)
		return CosOperator::operator_priority;

	if (op_name == TgOperator::operator_name)
		return TgOperator::operator_priority;

	if (op_name == CtgOperator::operator_name)
		return CtgOperator::operator_priority;

	// unknown operator
	return -1;
}