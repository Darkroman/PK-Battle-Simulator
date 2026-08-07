#pragma once

#include <type_traits>
#include <random>
#include <utility>
#include <concepts>

#include "../data/PokemonID.h"
#include "../data/MoveID.h"

template <typename E>
concept DatabaseID =
std::same_as<E, PokemonID> ||
std::same_as<E, MoveID>;

template <typename E>
requires std::is_enum_v<E>
constexpr auto EnumIndex(E value) noexcept
{
	return std::to_underlying(value);
}

template <typename E, typename T>
requires std::is_enum_v<E>
constexpr E ToEnum(T value) noexcept
{
	return static_cast<E>(value);
}

template <DatabaseID E>
constexpr auto IDToIndex(E value) noexcept
{
	return std::to_underlying(value) - 1;
}

template <typename Generator, typename Enum>
Enum RandomEnum(Generator& rng, Enum first, Enum last) noexcept
{
	using Underlying = std::underlying_type_t<Enum>;

	std::uniform_int_distribution<Underlying> dist(
		std::to_underlying(first),
		std::to_underlying(last));

	return static_cast<Enum>(dist(rng));
}