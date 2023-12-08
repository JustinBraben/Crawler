#ifndef ACTION_HPP
#define ACTION_HPP

#include <string>
#include <sstream>

class Action {

	std::string m_name = "NONE";	// Name of Action, eg. "MOVE_LEFT"
	std::string m_type = "NONE";	// Start or end of Action, eg. "START", "END"

public:

	Action();
	Action(const std::string& name, const std::string& type);

	const std::string& name() const;
	const std::string& type() const;
	std::string toString() const;
};

#endif // !ACTION_HPP