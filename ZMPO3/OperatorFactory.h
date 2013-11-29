#ifndef OPERATOR_FACTORY
#define OPERATOR_FACTORY

#include <iostream>

#include "OperatorNodes.h"

class OperatorFactory
{
	public:
		static const std::string aviable_operators[];

		static Operator* CreateOperator(const std::string& operator_name);
		static int OperatorPriority(const std::string& opearator_name);

	private:
};

#endif