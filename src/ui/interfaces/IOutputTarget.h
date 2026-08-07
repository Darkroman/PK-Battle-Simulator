#pragma once

#include <string>

class IOutputTarget
{
public:
	virtual ~IOutputTarget() = default;
	virtual void Emit(std::string&& text) = 0;
};