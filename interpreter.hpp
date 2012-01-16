#ifndef INCLUDE_INTERPRETER_HPP
#define INCLUDE_INTERPRETER_HPP

#include <string>
#include <map>
#include <boost/optional.hpp>
#include "iremocon_client.hpp"

class Interpreter
{
private:
	std::map<std::string, int> str_ir_map_;
public:
	Interpreter();
	bool learn_commands_from_xml(const std::string& file_name);
	boost::optional<int> interpret(const std::string& sentence);
};

#endif // INCLUDE_INTERPRETER_HPP
