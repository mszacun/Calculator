#include "ErrorCode.h"

// static members initialization
const int ErrorCode::ERROR_CODE_SUCCESS = 0;
const int ErrorCode::ERROR_CODE_TEST = -1;
const int ErrorCode::ERROR_CODE_TOO_MUCH_ARGUMENTS = 1;
const int ErrorCode::ERROR_CODE_TOO_FEW_ARGUMENTS = 2;
const int ErrorCode::ERROR_CODE_SYMBOL_UNDEFINED = 3;
const int ErrorCode::ERROR_CODE_DIVIDE_BY_0 = 4;
const int ErrorCode::ERROR_CODE_LOG_ARGUMENT_LESS_THEN_0 = 5;
const int ErrorCode::ERROR_CODE_PARENTHESE_NOT_CLOSED = 6;
const int ErrorCode::ERROR_CODE_PARENTHESE_NOT_OPENED = 7;
const int ErrorCode::ERROR_CODE_TOO_MUCH_OPERANDS_TOO_FEW_OPERATORS = 8;
const int ErrorCode::ERROR_CODE_INVALID_LEFT_SIDE_ARGUMENT = 9;
const int ErrorCode::ERROR_CODE_FORBIDDEN_CHARACTER_MET = 10;
const int ErrorCode::ERROR_CODE_0_TO_0 = 11;
const int ErrorCode::ERROR_CODE_EMPTY_EXPRESSION_ENTERED = 12;
const int ErrorCode::ERROR_CODE_EXPRESSION_NOT_ENTERED = 13;

const std::string ErrorCode::ERROR_MSG_SUCCESS = "OK";
const std::string ErrorCode::ERROR_MSG_TEST = "Test Error";
const std::string ErrorCode::ERROR_MSG_TOO_MUCH_ARGUMENTS = "Too much arguments for operator: ";
const std::string ErrorCode::ERROR_MSG_TOO_FEW_ARGUMENTS = "Too few arguments for operator: ";
const std::string ErrorCode::ERROR_MSG_SYMBOL_UNDEFINED = "Symbol undefined: ";
const std::string ErrorCode::ERROR_MSG_DIVIDE_BY_0 = "Can't divide by 0";
const std::string ErrorCode::ERROR_MSG_LOG_ARGUMENT_LESS_THAN_0 = "Log argument less than 0";
const std::string ErrorCode::ERROR_MSG_PARENTHESE_NOT_CLOSED = "Couldn't find closing parenthese";
const std::string ErrorCode::ERROR_MSG_PARENTHESE_NOT_OPENED = "Couldn't find opening parenthese";
const std::string ErrorCode::ERROR_MSG_TOO_MUCH_OPERANDS_TOO_FEW_OPERATORS = "Too much operands, too few operators in expression";
const std::string ErrorCode::ERROR_MSG_INVALID_LEFT_SIDE_ARGUMENT = "Invali left hand side argument od '='";
const std::string ErrorCode::ERROR_MSG_FORBIDDEN_CHARACTER_MET = "Forbidden character met: ";
const std::string ErrorCode::ERROR_MSG_0_TO_0 = "Can't calculate 0^0";
const std::string ErrorCode::ERROR_MSG_EMPTY_EXPRESSION_ENTERED = "Empty expression entered";
const std::string ErrorCode::ERROR_MSG_EXPRESSION_NOT_ENTERED = "Expression not entered";

ErrorCode::ErrorCode(int error_code, const std::string& error_msg):
	_error_code(error_code), _error_msg(error_msg)
{
}

ErrorCode::~ErrorCode()
{
}

int ErrorCode::GetErrorCode() const
{
	return _error_code;
}
const std::string& ErrorCode::GetErrorMsg() const
{
	return _error_msg;
}

// for easy use in "if" statements
ErrorCode::operator bool() const
{
	return _error_code == ERROR_CODE_SUCCESS;
}