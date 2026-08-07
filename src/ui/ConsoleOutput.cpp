#include <print>
#include <string>

#include "ConsoleOutput.h"

void ConsoleOutput::Emit(std::string&& text)
{
	std::println("{}", text);
}