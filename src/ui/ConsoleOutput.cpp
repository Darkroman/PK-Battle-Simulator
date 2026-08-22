#include "ConsoleOutput.h"

#include <print>
#include <string>

void ConsoleOutput::Emit(std::string&& text)
{
	std::println("{}", text);
}