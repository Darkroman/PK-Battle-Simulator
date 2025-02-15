#pragma once

#include <string>
#include <algorithm>

static bool IsDigits(const std::string& str)
{
	return std::all_of(str.begin(), str.end(), ::isdigit);
}

static void CheckUserInput(std::string& input)
{
	std::string first_word = input.substr(0, input.find(' '));
	std::string second_word = input.substr(input.find(' ') + 1, input.size());
	std::string first_word_with_dash = input.substr(0, input.find('-'));
	std::string second_word_with_dash = input.substr(input.find('-') + 1, input.size());

	first_word[0] = std::toupper(first_word[0]);
	std::transform(first_word.begin() + 1, first_word.end(), first_word.begin() + 1,
		[](unsigned char c) { return std::tolower(c); });

	second_word[0] = std::toupper(second_word[0]);
	std::transform(second_word.begin() + 1, second_word.end(), second_word.begin() + 1,
		[](unsigned char c) { return std::tolower(c); });

	first_word_with_dash[0] = std::toupper(first_word_with_dash[0]);
	std::transform(first_word_with_dash.begin() + 1, first_word_with_dash.end(), first_word_with_dash.begin() + 1,
		[](unsigned char c) { return std::tolower(c); });

	second_word_with_dash[0] = std::toupper(second_word_with_dash[0]);
	std::transform(second_word_with_dash.begin() + 1, second_word_with_dash.end(), second_word_with_dash.begin() + 1,
		[](unsigned char c) { return std::tolower(c); });

	if ((first_word == second_word) && (first_word_with_dash == second_word_with_dash))
	{
		input = first_word;
	}

	else if (first_word_with_dash != second_word_with_dash)
	{
		input = first_word_with_dash + '-' + second_word_with_dash;
	}

	else
	{
		input = first_word + ' ' + second_word;
	}
}