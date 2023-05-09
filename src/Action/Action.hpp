#pragma once

class Action {
public:
	Action();
	Action(const std::string& naame, const std::string& type);

	const std::string& getName() const;
	const std::string& getType() const;
	std::string toString() const;
private:
	std::string m_name = "NONE";
	std::string m_type = "NONE";
};