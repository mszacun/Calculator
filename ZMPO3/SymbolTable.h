#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <map>
#include "ErrorCode.h"

class SymbolTable
{
	public:
		typedef void  (*variable_changed) (const std::string& var_name, double old_value,
			double new_value, void* private_data);

		SymbolTable();
		~SymbolTable();

		ErrorCode GetValue(const std::string& var_name, double& result_placeholder);
		void SetValue(const std::string& var_name, double new_value);

		void EraseAll();
		ErrorCode EraseVariable(const std::string& var_name);

		bool IsDefined(const std::string& var_name) const;

		void ConnectOnVariableChangedCallback(variable_changed callback, void* private_data);

	private:
		std::map<std::string, double> _symbols;

		variable_changed on_variable_changed;
		void* on_variable_changed_private_data;

		void FireOnVariableChanged(const std::string& var_name, double old_value,
			double new_value);
};

#endif