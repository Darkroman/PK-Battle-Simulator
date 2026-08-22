#pragma once

#include "interfaces/IOutputTarget.h"

#include <string>

class ConsoleOutput final : public IOutputTarget
{
public:
	void Emit(std::string&& text) override;
};