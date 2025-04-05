#ifndef TYPES_H
#define TYPES_H

#include <string>
#include <map>
#include <vector>

/**
 * @brief Enum representing different Pokemon types
 */
enum class PokemonType {
    NORMAL,
    FIRE,
    WATER,
    GRASS,
    ELECTRIC,
    ICE,
    FIGHTING,
    POISON,
    GROUND,
    FLYING,
    PSYCHIC,
    BUG,
    ROCK,
    GHOST,
    DRAGON,
    DARK,
    STEEL,
    FAIRY,
    NONE
};

/**
 * @brief Converts PokemonType enum to string
 * @param type The PokemonType to convert
 * @return String representation of the type
 */
std::string typeToString(PokemonType type);

/**
 * @brief Converts string to PokemonType enum
 * @param typeStr The string to convert
 * @return PokemonType corresponding to the string
 */
PokemonType stringToType(const std::string& typeStr);

/**
 * @brief Gets the type effectiveness multiplier
 * @param attackType The attacking move's type
 * @param defenderType The defending Pokemon's type
 * @return Damage multiplier (0.5 = not effective, 1.0 = normal, 2.0 = super effective)
 */
float getTypeEffectiveness(PokemonType attackType, PokemonType defenderType);

/**
 * @brief Gets a color code for console output based on Pokemon type
 * @param type The Pokemon type
 * @return ANSI color code string
 */
std::string getTypeColor(PokemonType type);

#endif // TYPES_H