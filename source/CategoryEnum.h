#pragma once

#include <string>
#include <map>

enum class Category // Used in Moves
{
    Physical,
    Special,
    Status
};

using mapOfStringsToCategories = std::map<std::string_view, Category>;

Category ConvertStringToCategory(std::string_view);