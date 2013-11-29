#ifndef ERROR_CODE_H
#define ERROR_CODE_H

#include <iostream>

class ErrorCode
{
	public:
		// error codes
		static const int ERROR_CODE_SUCCESS;
		static const int ERROR_CODE_TEST;
		static const int ERROR_CODE_TOO_MUCH_ARGUMENTS;
		static const int ERROR_CODE_TOO_FEW_ARGUMENTS;
		static const int ERROR_CODE_SYMBOL_UNDEFINED;
		static const int ERROR_CODE_DIVIDE_BY_0;
		static const int ERROR_CODE_LOG_ARGUMENT_LESS_THEN_0;
		static const int ERROR_CODE_PARENTHESE_NOT_CLOSED;
		static const int ERROR_CODE_PARENTHESE_NOT_OPENED;
		static const int ERROR_CODE_TOO_MUCH_OPERANDS_TOO_FEW_OPERATORS;
		static const int ERROR_CODE_INVALID_LEFT_SIDE_ARGUMENT;
		static const int ERROR_CODE_FORBIDDEN_CHARACTER_MET;
		static const int ERROR_CODE_0_TO_0;
		static const int ERROR_CODE_EMPTY_EXPRESSION_ENTERED;
		static const int ERROR_CODE_EXPRESSION_NOT_ENTERED;

		// error messages
		static const std::string ERROR_MSG_SUCCESS;
		static const std::string ERROR_MSG_TEST;
		static const std::string ERROR_MSG_TOO_MUCH_ARGUMENTS;
		static const std::string ERROR_MSG_TOO_FEW_ARGUMENTS;
		static const std::string ERROR_MSG_SYMBOL_UNDEFINED;
		static const std::string ERROR_MSG_DIVIDE_BY_0;
		static const std::string ERROR_MSG_LOG_ARGUMENT_LESS_THAN_0;
		static const std::string ERROR_MSG_PARENTHESE_NOT_CLOSED;
		static const std::string ERROR_MSG_PARENTHESE_NOT_OPENED;
		static const std::string ERROR_MSG_TOO_MUCH_OPERANDS_TOO_FEW_OPERATORS;
		static const std::string ERROR_MSG_INVALID_LEFT_SIDE_ARGUMENT;
		static const std::string ERROR_MSG_FORBIDDEN_CHARACTER_MET;
		static const std::string ERROR_MSG_0_TO_0;
		static const std::string ERROR_MSG_EMPTY_EXPRESSION_ENTERED;
		static const std::string ERROR_MSG_EXPRESSION_NOT_ENTERED;

		// default parameters for succesfull operations
		ErrorCode(int error_code = ERROR_CODE_SUCCESS, 
			const std::string& error_msg = ERROR_MSG_SUCCESS);
		~ErrorCode();

		int GetErrorCode() const;
		const std::string& GetErrorMsg() const;

		// for easy use in "if" statements
		operator bool() const;

	private:
		int _error_code;
		std::string _error_msg;
};

#endif