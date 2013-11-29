#include "Test.h"
#include "Calculator.h"
#define _USE_MATH_DEFINES
#include <cmath>

const std::string EXIT_COMMAND = "exit";
const std::string ASSIGN_COMMAND = "let";
const std::string CLEAR_VARIABLES_COMMAND = "clearall";
const std::string CALCULATE_COMMAND = "calc";
const std::string POSTFIX_COMMAND = "postfix";
const std::string INFIX_COMMAND = "infix";

const double PI = 3.141592653589793238462;
const double E = 2.7182818;

void RunInteractive();
void ClearScreen();
void Help();

int main(int argc, char** argv)
{
	TestAll();
	RunInteractive();

	return 0;
}

void RunInteractive()
{
	Calculator calc;
	std::string input = "";
	ErrorCode error;
	double result;
	std::string string_result;

	Help();

	// add some usefull constants to calculator
	calc.SetVariable("pi", PI);
	calc.SetVariable("e", E);
	
	while (input != EXIT_COMMAND)
	{
		std::cout << "> ";
		std::getline(std::cin, input);

		if (input.find(ASSIGN_COMMAND + " ") == 0)
			error = calc.SetVariable(input.substr(ASSIGN_COMMAND.length() + 1));

		else if (input == CLEAR_VARIABLES_COMMAND)
			calc.ClearVariables();

		else if (input == CALCULATE_COMMAND)
		{
			if (error = calc.Calculate(result))
				std::cout << "Result = " << result << std::endl;
		}

		else if (input == INFIX_COMMAND)
		{
			if (error = calc.ToInfix(string_result))
				std::cout << string_result << std::endl;
		}

		else if (input == POSTFIX_COMMAND)
		{
			if (error = calc.ToPostfix(string_result))
				std::cout << string_result << std::endl;
		}


		else if (input != EXIT_COMMAND)
			error = calc.SetExpression(input);

		if (!error)
			std::cout << "ERROR: " << error.GetErrorMsg() << std::endl;
	}
}

void Help()
{
	std::cout << "* * * * * * * * * * * * * * * * * * * * * * * *" << std::endl;
	std::cout << "Calculator by Marcin Szachun" << std::endl;
	std::cout << "Manual: " << std::endl;
	std::cout << "Setting variables: 'let x = 20*2+4'" << std::endl;
	std::cout << "Entering expression: just enter expression you want e.g:" << std::endl;
	std::cout << "'2*(y+log(10)) or '4 x sin 45 + *'" << std::endl;
	std::cout << "Evaluating previously entered expression: 'calc'" << std::endl;
	std::cout << "Exit program: 'exit'" << std::endl;
	std::cout << "Print expression in infix format: 'infix'" << std::endl;
	std::cout << "Print expression in postfix format: 'postfix'" << std::endl;
	std::cout << "Aviable operators: ";

	for (int i = 0; OperatorFactory::aviable_operators[i] != ""; i++)
		std::cout << OperatorFactory::aviable_operators[i] << " ";
	std::cout << std::endl;

	std::cout << "* * * * * * * * * * * * * * * * * * * * * * * *" << std::endl;
}