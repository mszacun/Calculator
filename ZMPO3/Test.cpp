#include "Test.h"

bool TestSuccessErrorCode();
bool TestFailErrorCode();
void TestAddOperatorSuccess();
void TestAddOperatorWithTooFewArguments();
void TestVariableAbsentInSymbolTable();
void TestVariablePresentInTableAndRemovingVariable();
void TestSmallTreeWithVariablesPresentInTable();
void TestTreeWithVariablesAbsentInTable();
void TestTreeWithDivBy0();
void TestExpressionParserSimpleInfix();
void TestExpressionParserAdvancedInfix();
void TestInfixToPostfixConversion();
void TestMismatchedParenthesesErrors();
void TestVariableWithNameOfOperator();
void TestTreeBuildingFromPostfix();
void TestArgumentsOrderFromInfix();
void TestAssignOperator();

void TestAll()
{
	assert(TestSuccessErrorCode());
	assert(TestFailErrorCode() == false);
	TestAddOperatorSuccess();
	TestAddOperatorWithTooFewArguments();
	TestVariableAbsentInSymbolTable();
	TestVariablePresentInTableAndRemovingVariable();
	TestSmallTreeWithVariablesPresentInTable();
	TestTreeWithVariablesAbsentInTable();
	TestTreeWithDivBy0();
	TestExpressionParserSimpleInfix();
	TestExpressionParserAdvancedInfix();
	TestInfixToPostfixConversion();
	TestMismatchedParenthesesErrors();
	TestVariableWithNameOfOperator();
	TestTreeBuildingFromPostfix();
	TestArgumentsOrderFromInfix();
	TestAssignOperator(); 

	ExpressionParser::TestPrivateFunctions();
}

bool TestSuccessErrorCode()
{
	ErrorCode success;

	return success;
}

bool TestFailErrorCode()
{
	ErrorCode fail(ErrorCode::ERROR_CODE_TEST, ErrorCode::ERROR_MSG_TEST);

	return fail;
}

void TestAddOperatorSuccess()
{
	Node* arg1 = new NumberNode(2);
	Node* arg2 = new NumberNode(2);

	Operator* plus = new PlusOperator();
	SymbolTable table;
	
	assert(plus->Load_argument(arg1));
	assert(plus->Load_argument(arg2));

	double result = 0.0;
	assert(plus->Evaluate(table, result));
	assert(result == 4.0);
	
	delete plus;
}

void TestAddOperatorWithTooFewArguments()
{
	Node* arg1 = new NumberNode(2);
	Operator* plus = new PlusOperator();
	SymbolTable symbol_table;
	double result = 10.0;

	assert(plus->Load_argument(arg1));
	ErrorCode error = plus->Evaluate(symbol_table, result);
	
	assert(error == false);
	assert(error.GetErrorCode() == ErrorCode::ERROR_CODE_TOO_FEW_ARGUMENTS);
	assert(result == 10.0);

	delete plus;
}

void TestVariableAbsentInSymbolTable()
{
	SymbolTable table;
	double placeholder;

	table.SetValue("length", 34.4);

	assert(table.GetValue("width", placeholder) == false);
}

void TestVariablePresentInTableAndRemovingVariable()
{
	SymbolTable table;
	double placeholder;

	table.SetValue("length", 2.30);
	
	assert(table.GetValue("length", placeholder));
	assert(placeholder = 2.30);

	assert(table.EraseVariable("length"));
	assert(table.GetValue("length", placeholder) == false);
}

void TestSmallTreeWithVariablesPresentInTable()
{
	SymbolTable table;
	VariableNode* width1 = new VariableNode("width");
	VariableNode* width2 = new VariableNode("width");
	VariableNode* height1 = new VariableNode("height");
	VariableNode* height2 = new VariableNode("height");
	Operator* width2Times = new PlusOperator();
	Operator* height2Times = new PlusOperator();
	Operator* ambit = new PlusOperator();
	double result;

	assert(width2Times->Load_argument(width1));
	assert(width2Times->Load_argument(width2));

	assert(height2Times->Load_argument(height1));
	assert(height2Times->Load_argument(height2));

	assert(ambit->Load_argument(width2Times));
	assert(ambit->Load_argument(height2Times));

	table.SetValue("width", 5.0);
	table.SetValue("height", 10.0);
	
	assert(ambit->Evaluate(table, result));
	assert(result == 30);

	assert(ambit->ToPostfix() == "width width + height height + +");

	delete ambit;
}

void TestTreeWithVariablesAbsentInTable()
{
	SymbolTable table;
	VariableNode* width = new VariableNode("width");
	VariableNode* height = new VariableNode("height");
	Operator* area = new MultiplyOperator();
	double result;
	std::vector<std::string> undefined_variables;

	table.SetValue("height", 3.5);
	assert(area->Load_argument(width));
	assert(area->Load_argument(height));
	ErrorCode error = area->Evaluate(table, result);

	assert(error == false);
	assert(error.GetErrorCode() == ErrorCode::ERROR_CODE_SYMBOL_UNDEFINED);

	area->FindUndefinedVariables(table, undefined_variables);
	assert(undefined_variables[0] == "width");

	delete area;
}

void TestTreeWithDivBy0()
{
	SymbolTable table;
	NumberNode* arg1 = new NumberNode(2);
	NumberNode* arg2 = new NumberNode(2);
	Operator* minus = new MinusOperator();
	VariableNode* var = new VariableNode("tmp");
	Operator* div = new DivideOperator();
	double result;

	table.SetValue("tmp", 1.0);
	assert(minus->Load_argument(arg1));
	assert(minus->Load_argument(arg2));

	assert(div->Load_argument(minus));
	assert(div->Load_argument(var));

	ErrorCode error = div->Evaluate(table, result);
	assert(error == false);
	assert(error.GetErrorCode() == ErrorCode::ERROR_CODE_DIVIDE_BY_0);

	delete div;
}

void TestExpressionParserSimpleInfix()
{
	const std::string testString = "1+2.54*2";
	ExpressionParser parser(testString);
	std::string token;

	assert(parser.GetNextToken(token) == ExpressionParser::TOKEN::NUMBER);
	assert(parser.GetNextToken(token) == ExpressionParser::TOKEN::OPERATOR);
	assert(parser.GetNextToken(token) == ExpressionParser::TOKEN::NUMBER);
	assert(parser.GetNextToken(token) == ExpressionParser::TOKEN::OPERATOR);
	assert(parser.GetNextToken(token) == ExpressionParser::TOKEN::NUMBER);
	assert(parser.GetNextToken(token) == ExpressionParser::TOKEN::END);
}

void TestExpressionParserAdvancedInfix()
{
	const std::string testString = "1+sin(90)+cos(katalfa)";
	ExpressionParser parser(testString);
	std::string token;

	assert(parser.GetNextToken(token) == ExpressionParser::TOKEN::NUMBER);
	assert(parser.GetNextToken(token) == ExpressionParser::TOKEN::OPERATOR);
	assert(parser.GetNextToken(token) == ExpressionParser::TOKEN::OPERATOR);
	assert(parser.GetNextToken(token) == ExpressionParser::TOKEN::LEFT_PARENTHESE);
	assert(parser.GetNextToken(token) == ExpressionParser::TOKEN::NUMBER);
	assert(parser.GetNextToken(token) == ExpressionParser::TOKEN::RIGHT_PARENTHESE);
	assert(parser.GetNextToken(token) == ExpressionParser::TOKEN::OPERATOR);
	assert(parser.GetNextToken(token) == ExpressionParser::TOKEN::OPERATOR);
	assert(parser.GetNextToken(token) == ExpressionParser::TOKEN::LEFT_PARENTHESE);
	assert(parser.GetNextToken(token) == ExpressionParser::TOKEN::VARIABLE);
	assert(parser.GetNextToken(token) == ExpressionParser::TOKEN::RIGHT_PARENTHESE);
	assert(parser.GetNextToken(token) == ExpressionParser::TOKEN::END);
}

void TestInfixToPostfixConversion()
{
	Expression expression;

	expression.SetInfixInput("2+2");
	expression.SetInfixInput("2+2*2+2");
	expression.SetInfixInput("2*(2+2*2)");
	expression.SetInfixInput("cos(2+sin(2+8*2)*2)");
	expression.SetInfixInput("2+sin(30+30+15*2)*2");
}

void TestMismatchedParenthesesErrors()
{
	Expression expr;
	ErrorCode error;
	
	error = expr.SetInfixInput("(2+4*(5+6)*2");
	assert(error == false);
	assert(error.GetErrorCode() == ErrorCode::ERROR_CODE_PARENTHESE_NOT_CLOSED);

	error = expr.SetInfixInput("3+8-(3*4)+2)-23+2*log(23)");
	assert(error == false);
	assert(error.GetErrorCode() == ErrorCode::ERROR_CODE_PARENTHESE_NOT_OPENED);

	error = expr.SetInfixInput("log(3*4+5*cos(2+8)*2");
	assert(error == false);
	assert(error.GetErrorCode() == ErrorCode::ERROR_CODE_PARENTHESE_NOT_CLOSED);
}

void TestVariableWithNameOfOperator()
{
	Expression expr;
	ErrorCode error;

	error = expr.SetInfixInput("1+log+2*2");

	assert(error == false);
}

void TestTreeBuildingFromPostfix()
{
	Expression expr;
	ErrorCode error;
	
	error = expr.SetPostfixInput("2 +");
	assert(error == false);
	assert(error.GetErrorCode() == ErrorCode::ERROR_CODE_TOO_FEW_ARGUMENTS);

	error = expr.SetPostfixInput("2 3 4 + * 9");
	assert(error == false);
	assert(error.GetErrorCode() == ErrorCode::ERROR_CODE_TOO_MUCH_OPERANDS_TOO_FEW_OPERATORS);
}

void TestArgumentsOrderFromInfix()
{
	Expression expr;
	SymbolTable table;
	double result;

	expr.SetInfixInput("(2+2)-(1+1)");
	assert(expr.Evaluate(table, result));
	assert(result == 2);
}

void TestAssignOperator()
{
	Expression exp;
	SymbolTable table;
	double result;

	assert(exp.SetInfixInput("testVar = 20+5"));
	assert(exp.Evaluate(table, result));
	assert(table.GetValue("testVar", result));
	assert(result == 25);
}