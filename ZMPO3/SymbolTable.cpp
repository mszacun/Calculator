#include "SymbolTable.h"

SymbolTable::SymbolTable() : on_variable_changed(NULL)
{
}

SymbolTable::~SymbolTable()
{
}

ErrorCode SymbolTable::GetValue(const std::string& var_name, double& result_placeholder)
{
	if (_symbols.find(var_name) != _symbols.end())
	{
		result_placeholder = _symbols[var_name];
		return ErrorCode();
	}
	else
		return ErrorCode(ErrorCode::ERROR_CODE_SYMBOL_UNDEFINED, ErrorCode::ERROR_MSG_SYMBOL_UNDEFINED + var_name);
}

void SymbolTable::SetValue(const std::string& var_name, double new_value)
{
	double old_value;

	if (_symbols.find(var_name) != _symbols.end())
		old_value = _symbols[var_name];
	else
		old_value = NAN;

	_symbols[var_name] = new_value;

	FireOnVariableChanged(var_name, old_value, new_value);
}

void SymbolTable::EraseAll()
{
	_symbols.clear();
}

ErrorCode SymbolTable::EraseVariable(const std::string& var_name)
{
	std::map<std::string, double>::iterator iter = _symbols.find(var_name);

	if (iter != _symbols.end())
	{
		FireOnVariableChanged(var_name, _symbols[var_name], NAN);

		_symbols.erase(iter);
		return ErrorCode();
	}
	else
		return ErrorCode(ErrorCode::ERROR_CODE_SYMBOL_UNDEFINED, ErrorCode::ERROR_MSG_SYMBOL_UNDEFINED + var_name);
}

bool SymbolTable::IsDefined(const std::string& var_name) const
{
	std::map<std::string, double>::const_iterator it = _symbols.find(var_name);

	return it != _symbols.end();
}

void SymbolTable::ConnectOnVariableChangedCallback(variable_changed callback, void* private_data)
{
	on_variable_changed = callback;
	on_variable_changed_private_data = private_data;
}

void SymbolTable::FireOnVariableChanged(const std::string& var_name, double old_value,
	double new_value)
{
	if (on_variable_changed != NULL)
		on_variable_changed(var_name, old_value, new_value, on_variable_changed_private_data);
}