#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <string>
#include "types.h"

/**
 * @brief Enum representing different battle environments
 */
enum class BattleEnvironment {
    NORMAL,
    GRASS_FIELD,
    WATER_SURFACE,
    CAVE,
    VOLCANO,
    ELECTRIC_TERRAIN,
    PSYCHIC_TERRAIN
};

/**
 * @brief Class representing a battle environment
 */
class Environment {
public:
    /**
     * @brief Constructor for Environment
     * @param type The type of environment
     */
    Environment(BattleEnvironment type);
    
    /**
     * @brief Get the name of the environment
     * @return String name of the environment
     */
    std::string getName() const;
    
    /**
     * @brief Get the type boost for this environment
     * @return The PokemonType that gets boosted in this environment
     */
    PokemonType getBoostedType() const;
    
    /**
     * @brief Get the boost multiplier for the environment
     * @return The damage multiplier for the boosted type
     */
    float getBoostMultiplier() const;
    
    /**
     * @brief Get a description of the environment
     * @return String describing the environment and its effects
     */
    std::string getDescription() const;

private:
    BattleEnvironment envType;
    PokemonType boostedType;
    float boostMultiplier;
};

#endif // ENVIRONMENT_H