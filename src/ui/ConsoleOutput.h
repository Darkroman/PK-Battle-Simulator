#pragma once

#include <string>

#include "interfaces/IOutputTarget.h"

class ConsoleOutput final : public IOutputTarget
{
public:
	void Emit(std::string&& text) override;
};